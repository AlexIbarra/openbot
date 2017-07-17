#include <unistd.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "moduloCamara.h"
#include <stdio.h>
#include <vector>
#include <list>

using namespace cv;
using namespace std;


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

int trackObject(t_Coordenada &object) {
	
	VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() ) { // if not success, exit program
        cout << "Cannot open the web cam" << endl;
        return -1;
    }
    
    Mat imgOriginal, imgGray, imgThresholded, imgNormalized;
	
	vector<Mat> channels;
	
	// TODO: Comprobar que funciona con un solo frame
	
	bool bSuccess = cap.read(imgOriginal);

	if (!bSuccess) {
		cout << "Cannot read a frame from video stream" << endl;
		return -1;
	}                                              	
						  
	/* 
	 * Realizamos el filtrado de la imagen
	 * para detectar los objetos 
	 */
	 
	vector<float> values(3, 0.0);
	values[0] = 0.0; // Blue channel value
	values[1] = -1.0; // Green channel value
	values[2] = 1.44; // Red channel value
	 
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
	if (area > MIN_OBJECT_AREA && area < MAX_OBJECT_AREA) {
		//calculate the position of the ball
		object.x = dM10 / area;
		object.y = dM01 / area;	
	}
}

void detectMultiObject(Object theObject,Mat threshold, Mat &cameraFeed, list<Object> &objects) {

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
    Object object;
    
    if (hierarchy.size() > 0) {
        
        int numObjects = hierarchy.size();
        
        if(numObjects < MAX_NUM_OBJECTS){//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);//use moments method to find our filtered object
                double area = moment.m00;

                //if the area is less than 20 px by 20px then it is probably just noise
                //if the area is the same as the 3/2 of the image size, probably just a bad filter
                //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                if(area > MIN_OBJECT_AREA && area < MAX_OBJECT_AREA){

                    object.setXPos(moment.m10/area);
                    object.setYPos(moment.m01/area);

					if(objects.size() > numObjects) {
						objects.pop_front();
					}
					
                    objects.push_back(object);

                    objectFound = true;
                    circle(cameraFeed, Point(object.getXPos(), object.getYPos()), 10, Scalar(255, 0, 0));
                }
                else {
                    objectFound = false;
                }
            }            
        }
        else {
            putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
        }
    }
    else {
		objects.clear();
	}
}

void excessOfColourThreshold(Mat cameraFeed, Mat &imgThresholded, const vector<float> &values) {
	Mat M = Mat(1, 3, CV_32F); // 1x3 Matrix

	M.at<float>(0, 0) = values[0];//0.0;
	M.at<float>(0, 1) = values[1];//-1.0;
	M.at<float>(0, 2) = values[2];//1.44;

	transform(cameraFeed, imgThresholded, M);
}


//Las inicializamos en el punto medio de la pantalla, para que no se muevan los motores de inicio
int captura(list<Object> &objects) {
	
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
	
	bool bSuccess = cap.read(imgOriginal);

	if (!bSuccess) {
		cout << "Cannot read a frame from video stream" << endl;
		return -1;
	}                                              	
						  
	/* 
	 * Realizamos el filtrado de la imagen
	 * para detectar los objetos 
	 */
	 
	vector<float> values(3, 0.0);
	values[0] = 0.0; // Blue channel value
	values[1] = -1.0; // Green channel value
	values[2] = 1.44; // Red channel value
	 
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
	Object object;
	detectMultiObject(object, imgThresholded, imgOriginal, objects);

	return 0;
}
