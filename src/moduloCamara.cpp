#include <unistd.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "moduloCamara.h"
#include <stdio.h>
#include <vector>

using namespace cv;
using namespace std;

#define ExG 1
#define ExR 2
#define FRAME_WIDTH         640
#define FRAME_HEIGHT        480
#define MAX_NUM_OBJECTS     10
#define MIN_OBJECT_AREA     10000
#define MAX_OBJECT_AREA     1500000
#define THRESHOLD_LIMIT     180
#define ExG_VALUES          {-1.0, 2.0, -1.0}
#define ExR_VALUES          {0.0, -1.0, 1.44}
#define ExB_VALUES          {1.44, -1.0, 0.0}


/* 
 * ########################################################################
 * ####  Declaracion de las funciones estaticas al modulo de la camara ####
 * ########################################################################
 */


/*! \brief Permite generar el histograma de una imagen de tres canales (RGB)
 *  \param image Imagen de entrada
 *  \param histoImage Imagen con el histograma de cada uno de los canales
 * 
 *  Calcula el histograma para cada uno de los canales de una imagen RGB.
 */
void histogramCalculation(Mat image, Mat &histoImage) {
    int histSize = 255;
    /* Rango de valores para cada uno de los canales */
    float range[] = { 0, 256 } ;
    const float* histRange = { range };
    bool uniform = true; bool accumulate = false;
    Mat b_hist, g_hist, r_hist;
    
    vector<Mat> bgr_planes;
    split(image, bgr_planes );
    
    /* Calculo del histograma de cada uno de los canales */
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
    
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    
    /* Normalizacion del histograma de cada canal */
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    
    /* Se pintan las lineas que representan el histograma de cada canal */
    for( int i = 1; i < histSize; i++ ){
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) , 
            Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ), Scalar( 255, 0, 0), 2, 8, 0 );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) , 
            Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ), Scalar( 0, 255, 0), 2, 8, 0 );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) , 
            Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ), Scalar( 0, 0, 255), 2, 8, 0 );
    }
    
    histoImage = histImage;
}

/*! \brief Binarizacion de una imagen en escala de grises por el algoritmo de Otsu
 *  \param input_img Imagen de entrada
 *  \param output_img Imagen de salida, binarizada
 * 
 *  Permite calcular el valor de umbral para la binarizacion de forma automatica
 *  medinate el algoritmo de Otsu.
 */
static void thresholdOtsu(Mat input_img, Mat &output_img) {	
    threshold(input_img, output_img, 127, 255, THRESH_BINARY | THRESH_OTSU);
}

/*! \brief Binarizacion de una imagen en escala de grises mediante el metodo adaptativo
 *  \param input_img Imagen de entrada
 *  \param output_img Imagen de salida, binarizada
 * 
 *  Busca el valor del umbral para la binarizacion en diferentes regiones de
 *  la imagen. De esta forma consigue no verse tan afectada ante condiciones
 *  de iluminacion variable en diferentes zonas.
 */
static void thresoldAdaptative(Mat input_img, Mat &output_img) {
    adaptiveThreshold(input_img, output_img, 220, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 5, 8);
}

/*! \brief Binarizacion de una imagen en escala de grises mediante el metodo adaptativo
 *  \param input_img Imagen de entrada
 *  \param output_img Imagen de salida, binarizada
 * 
 *  El funcionamiento es igual al de la funcion "thresoldAdaptative" solo que en
 *  este caso se calcula el valor de umbral es la suma ponderada de los valores de
 *  cada region cuyos pesos corresponden con una ventana gausiana.
 */
static void thresoldAdaptativeGaussian(Mat input_img, Mat &output_img) {
    adaptiveThreshold(input_img, output_img, 127, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 11, 12);
}

/*! \brief Elimina los objetos pequeños dentro de la imagen (ruido)
 *  \param image Imagen a la que se le aplica el filtrado
 *  \param obj_radius Objeto erosionador/dilatador
 * 
 *  Hace uso de las funciones "erode y dilate" en este orden para conseguir el efecto 
 *  de apertura en la imagen. Permite eliminar el ruido provocado por la
 *  aparicion de objetos pequeños.
 */
static void openingThreshold(Mat &image, int obj_radius) {
    int obj_type = MORPH_ELLIPSE;

    Mat object = getStructuringElement( obj_type, Size(2*obj_radius + 1, 2*obj_radius+1), Point( obj_radius, obj_radius ) );

    erode(image, image, object, Point(-1, -1), 2 );
    dilate( image, image, object, Point(-1, -1), 2 );
}

/*! \brief Elimina los espacios intermedios que hay en un objeto (partes inconexas)
 *  \param image Imagen a la que se le aplica el filtrado
 *  \param obj_radius Objeto erosionador/dilatador
 * 
 *  Hace uso de las funciones "dilate y erode" en este orden para conseguir el efecto 
 *  de cierre en la imagen. Permite evitar que los objetos detectados aparezcan
 *  divididos.
 */
static void closingThreshold(Mat &image, int obj_radius) {
    int obj_type = MORPH_ELLIPSE;

    Mat object = getStructuringElement( obj_type, Size(2*obj_radius + 1, 2*obj_radius+1), Point( obj_radius, obj_radius ) );

    dilate( image, image, object, Point(-1, -1), 2 ); 
    erode( image, image, object, Point(-1, -1), 2  );
}

/*! \brief Calcula las coordenadas de los objetos que aparecen en una imagen
 *  \param input_img Imagen de entrada
 *  \param objects Lista con las coordenadas de cada uno de los objetos detectados
 * 
 *  Permite calcular las coordenadas de cada objeto que aparezca en la imagen
 *  mediante la deteccion de contornos y el calculo del centro de masas de cada
 *  objeto.
 */
static void getMultiCoordinates(Mat input_img, list<t_Coordenada> &objects) {

    Mat temp;
    double area = 0;    
    int numObjects;
    t_Coordenada object;
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    input_img.copyTo(temp);        
    
    /* 
     * Utilizamos esta funcion para encontrar los contornos
     * de los objetos que haya en la imagen
     */
    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);            
    
    /* Si se han detectado objetos en la imagen */
    if (hierarchy.size() > 0) {
        
        numObjects = hierarchy.size();
        
        /* Comprobamos que no haya ruido en la imagen */
        if(numObjects < MAX_NUM_OBJECTS) {
            
            /* Calculamos las coordenadas para todos los objetos detectados */
            for (int i = 0; i >= 0; i = hierarchy[i][0]) {

                Moments moment = moments((cv::Mat)contours[i]);//use moments method to find our filtered object
                area = moment.m00;

                /* Comprobamos que cada objeto cumple con las caracteristicas esperadas */
                if(area > MIN_OBJECT_AREA && area <= MAX_OBJECT_AREA) {

                    object.x = moment.m10/area;
                    object.y = moment.m01/area;

                    /* Si la lista esta llena, actualizamos los elementos mas antiguos */
                    if(objects.size() > numObjects) {
                        objects.pop_front();
                    }
					
                    objects.push_back(object);
                }
            }            
        }
    }
    else {
        objects.clear();
    }
}

/*! \brief Convierte una imagen de tres canales (RGB) a otra en escala de grises
 *  \param input_img Imagen de entrada
 *  \param output_img Imagen de salida, binarizada
 *  \param values Valores que corresponden a los pesos de cada canal RGB
 * 
 *  Transforma una imagen RGB a otra en escala de grises con exceso de color.
 *  Dependiendo de los valores del array "values" se aplicara un esceso de color
 *  a los canales R, G o B, lo que permitira realzar los objetos cuyo color
 *  se encuentre entre estos espectros.
 */
static void toGrayscaleWithExcessOfColour(Mat input_img, Mat &output_img, double values[]) {
    Mat M = Mat(1, 3, CV_32F); // 1x3 Matrix

    /* Asignamos los valores correspondientes a cada canal (BGR)*/
    M.at<float>(0, 0) = values[0]; // Blue channel
    M.at<float>(0, 1) = values[1]; // Green channel
    M.at<float>(0, 2) = values[2]; // Red channel

    /* 
     * Se realiza una combinacion lineal de la imagen original
     * con una matrix M para la obtencion de una imagen de
     * un solo canal (imagen en escala de grises) 
     */
    transform(input_img, output_img, M);
}


/* 
 * ###########################################
 * ####  Funciones propias de la interfaz ####
 * ###########################################
 */

void * trackMultiObjects(void * objects) {
	
    t_Lista *list = (t_Lista *)objects;
    bool bSuccess;
    double values[] = ExG_VALUES;
    Mat imgOriginal, imgGray, imgThresholded, imgNormalized;
    
    VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() ) { // if not success, exit program
        cout << "Cannot open the web cam" << endl;
    }                

    //~ while(1) {
        bSuccess = cap.read(imgOriginal);

        if (!bSuccess) {
            cout << "Cannot read a frame from video stream" << endl;
        }                                              	

        /* 
         * Generamos imagen en escala de grises con los 
         * objetos detectados 
         */
        toGrayscaleWithExcessOfColour(imgOriginal, imgGray, values);

        openingThreshold(imgGray, 2);
        closingThreshold(imgGray, 2);		

        /* Normalizamos histograma de la imagen en escala de grises */
        normalize(imgGray, imgNormalized, 0, 255, NORM_MINMAX);

        /* 
         * Generamos imagen binarizada (objetos en blanco y 
         * el resto de la imagenen negro)
         */
        threshold(imgNormalized, imgThresholded, 180, 255, THRESH_BINARY);        	

        /* Creamos una lista con todos los objetos detectados */
        getMultiCoordinates(imgThresholded, list->objects);
    //~ }
}

void * trackObject(void * obj) {
    
    t_Coordenada *object = (t_Coordenada *)obj;
    double values[] = ExG_VALUES;
    bool bSuccess;
    
    /* Captura de un frame */
    VideoCapture cap(0);

    if ( !cap.isOpened() ) { // if not success, exit program
        cout << "Cannot open the web cam" << endl;
    }
    
    Mat imgOriginal, imgGray, imgThresholded, imgNormalized;	

//    while(true) {

        bSuccess = cap.read(imgOriginal);

        if (!bSuccess) {
            cout << "Cannot read a frame from video stream" << endl;
        }                                              	

        /* Generamos imagen en escala de grises con los exceso de verde */
        toGrayscaleWithExcessOfColour(imgOriginal, imgGray, values);

        /* 
         * Realizamos filtrado de ruido en la imagen y union
         * de objetos inconexos
         */
        openingThreshold(imgGray, 2);
        closingThreshold(imgGray, 2);		

        /* Normalizamos histograma de la imagen en escala de grises */
        normalize(imgGray, imgNormalized, 0, 255, NORM_MINMAX);

        /* 
         * Generamos imagen binarizada (objetos en blanco y 
         * el resto de la imagenen negro)
         */
        threshold(imgNormalized, imgThresholded, THRESHOLD_LIMIT, 255, THRESH_BINARY);


        Moments momentos = moments(imgThresholded);

        double m01 = momentos.m01;
        double m10 = momentos.m10;
        double area = momentos.m00;

        if (area > MIN_OBJECT_AREA && area <= MAX_OBJECT_AREA) {
            // Calculamos las coordenadas del objeto
            object->x = m10 / area;
            object->y = m01 / area;
        }
//    }
}