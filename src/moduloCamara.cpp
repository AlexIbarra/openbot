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

static void modifyChannels(vector<float> &channels, int excessType) {

    if (excessType == ExG) {
        channels[0] = -1.0; // Blue channel value
        channels[1] = 2.0; // Green channel value
        channels[2] = -1.0; // Red channel value
    }
    else if (excessType == ExR) {
        channels[0] = 0.0; // Blue channel value
        channels[1] = -1.0; // Green channel value
        channels[2] = 1.44; // Red channel value
    }
    else {
        channels[0] = 1.44; // Blue channel value
        channels[1] = -1.0; // Green channel value
        channels[2] = 0.0; // Red channel value
    }
}
// Funcion de Ecualizacion de histograma para imagenes a color
void equalizeHistogram(Mat threshold, Mat &equalized) {   
    /********* Ecualizacion de histograma *********/
    vector<Mat> channels;
	// Cambiamos el formato de color (BGR a YCrCb)
	cvtColor(threshold, equalized, CV_BGR2YCrCb);
	
	// Dividimos los canales de la imagen ecualizada en un vector
	split(equalized,channels);
	
	// Realizamos la ecualizacion del canal 0 (Y)
	equalizeHist(channels[0], channels[0]);
	
	// Volvemos a juntar los canales (ecualizado Y)
	merge(channels,equalized);
	
	// Volvemos a cambiar el formato de color para que se pueda mostrar correctamente (YCrCb a BGR)
	cvtColor(equalized, equalized, CV_YCrCb2BGR);
	/*********************************************/   
}

// Funcion para aplicar una binarizacion de la imagen con
// el algoritmo Otsu
void thresholdOtsu(Mat equalized, Mat &otsu) {
	
	threshold(equalized, otsu, 127, 255, THRESH_BINARY | THRESH_OTSU);
}

// Morphological opening (removes small objects from the foreground)
void applyOpening(Mat &threshold, int obj_radius) {
	int obj_type = MORPH_ELLIPSE;
	
	Mat object = getStructuringElement( obj_type, Size(2*obj_radius + 1, 2*obj_radius+1), Point( obj_radius, obj_radius ) );
	
	erode(threshold, threshold, object, Point(-1, -1), 2 );
	dilate( threshold, threshold, object, Point(-1, -1), 2 );
	//erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
	//dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
}

// Morphological closing (removes small holes from the foreground)
void applyClosing(Mat &threshold, int obj_radius) {
	int obj_type = MORPH_ELLIPSE;
	
	Mat object = getStructuringElement( obj_type, Size(2*obj_radius + 1, 2*obj_radius+1), Point( obj_radius, obj_radius ) );
	
	dilate( threshold, threshold, object, Point(-1, -1), 2 ); 
	erode( threshold, threshold, object, Point(-1, -1), 2  );
	//dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
	//erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
}
//void trackObject(t_Coordenada &object) {
void *trackObject(void * obj) {
    
    t_Coordenada *object = (t_Coordenada *)obj;
	
    cout << "CtrackObject Entramos" << endl;

    VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() ) { // if not success, exit program
        cout << "Cannot open the web cam" << endl;
    }
    
    Mat imgOriginal, imgGray, imgThresholded, imgNormalized;
	
    vector<Mat> channels;

    // TODO: Comprobar que funciona con un solo frame
    while(1) {

        bool bSuccess = cap.read(imgOriginal);

        if (!bSuccess) {
                cout << "Cannot read a frame from video stream" << endl;
        }                                              	

        /* 
         * Realizamos el filtrado de la imagen
         * para detectar los objetos 
         */
        vector<float> values(3, 0.0);
        modifyChannels(values, ExG);
        

        /* 
         * Generamos imagen en escala de grises con los 
         * objetos detectados 
         */
        excessOfColourThreshold(imgOriginal, imgGray, values);

        applyOpening(imgGray, 2);
        applyClosing(imgGray, 2);		

        /* Normalizamos histograma de la imagen en escala de grises */
        normalize(imgGray, imgNormalized, 0, 255, NORM_MINMAX);

        /* 
         * Generamos imagen binarizada (objetos en blanco y 
         * el resto de la imagenen negro)
         */
        threshold(imgNormalized, imgThresholded, 180, 255, THRESH_BINARY);


        Moments oMoments = moments(imgThresholded);

        double dM01 = oMoments.m01;
        double dM10 = oMoments.m10;
        double area = oMoments.m00;


        // if the area <= 10000, I consider that the there are no object 
        // in the image and it's because of the noise, the area is not zero 
        cout << "AREA: " << area << endl;
        if (area > 10000 && area <= 1500000) {
            //calculate the position of the ball
            object->x = dM10 / area;
            object->y = dM01 / area;

            //~ circle(imgOriginal, Point(object->x, object->y), 10, Scalar(255, 0, 0));
        }
        //~ imshow("Thresholdede", imgThresholded);
        //~ imshow("Original", imgOriginal);
        //~ imshow("Excess of red", imgGray);
        //~ waitKey(30);
    }
}

void detectMultiObject(Mat threshold, Mat &cameraFeed, list<t_Coordenada> &objects) {

    //~ vector <Object> objects;
    Mat temp;
    threshold.copyTo(temp);
    
    //these two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    //find contours of filtered image using openCV findContours function
    findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
        
    double refArea = 0;
    bool objectFound = false;
    t_Coordenada object;
    
    if (hierarchy.size() > 0) {
        
        int numObjects = hierarchy.size();
        
        if(numObjects < MAX_NUM_OBJECTS){//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
			//~ cout << "Objetos: " << numObjects << endl;
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);//use moments method to find our filtered object
                double area = moment.m00;

                //~ cout << "AREA: " << area << endl;
                if(area > MIN_OBJECT_AREA && area <= MAX_OBJECT_AREA){

                    object.x = moment.m10/area;
                    object.y = moment.m01/area;

                    if(objects.size() > numObjects) {
                        objects.pop_front();
                    }
					
                    objects.push_back(object);
                    objectFound = true;
                    
                    //~ circle(cameraFeed, Point(object.x, object.y), 10, Scalar(255, 0, 0));
                }
                else {
                    objectFound = false;
                }
            }            
        }
        //~ else {
            //~ putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
        //~ }
    }
    else {
        objects.clear();
    }
}

void excessOfColourThreshold(Mat cameraFeed, Mat &imgThresholded, vector<float> &values) {
	Mat M = Mat(1, 3, CV_32F); // 1x3 Matrix

	M.at<float>(0, 0) = values[0];//0.0;
	M.at<float>(0, 1) = values[1];//-1.0;
	M.at<float>(0, 2) = values[2];//1.44;

	transform(cameraFeed, imgThresholded, M);
}

//Las inicializamos en el punto medio de la pantalla, para que no se muevan los motores de inicio
//int captura(list<t_Coordenada> &objects) {
void *captura(void *objects) {
	
    t_List *list = (t_List *)objects;
    
    VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() ) { // if not success, exit program
        cout << "Cannot open the web cam" << endl;
    }

    //Capture a temporary image from the camera
    Mat imgTmp, dst;
    cap.read(imgTmp); 

    //Create a black image with the size as the camera output
    Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );
            
    Mat imgOriginal, imgGray, imgThresholded, imgNormalized;

    vector<Mat> channels;

    // TODO: Comprobar que funciona con un solo frame

    //~ while(1) {
        bool bSuccess = cap.read(imgOriginal);

        if (!bSuccess) {
                cout << "Cannot read a frame from video stream" << endl;
//                return -1;
        }                                              	

        /* 
         * Realizamos el filtrado de la imagen
         * para detectar los objetos 
         */

        vector<float> values(3, 0.0);
        modifyChannels(values, ExG);

        /* 
         * Generamos imagen en escala de grises con los 
         * objetos detectados 
         */
        excessOfColourThreshold(imgOriginal, imgGray, values);

        applyOpening(imgGray, 2);
        applyClosing(imgGray, 2);		

        /* Normalizamos histograma de la imagen en escala de grises */
        normalize(imgGray, imgNormalized, 0, 255, NORM_MINMAX);

        /* 
         * Generamos imagen binarizada (objetos en blanco y 
         * el resto de la imagenen negro)
         */
        threshold(imgNormalized, imgThresholded, 180, 255, THRESH_BINARY);        	

        /* Creamos una lista con todos los objetos detectados */
        detectMultiObject(imgThresholded, imgOriginal, list->objects);

        //~ imshow("Thresholdede", imgThresholded);
        //~ imshow("Original", imgOriginal);
        //~ imshow("Excess of green", imgGray);
        //~ waitKey(10);
    //~ }

//    return 0;
}
