#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include "moduloCamara.h"

// Para compilar (dentro del dir src): g++ ../obj/moduloCamara.o -o testMoments testMoments.cpp `pkg-config --libs opencv` -lpthread -I../include/

void detect(Mat threshold, Mat &cameraFeed, Mat &drawing, list<t_Coordenada> &objects, double n) {
    Mat cannyOut;
    RNG rng(12345);
    
    Canny(threshold, cannyOut, n, n * (1/2), 3, 1);    

    // Find contours
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(cannyOut, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    // Get the moments
    vector<Moments> mu(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        mu[i] = moments(contours[i], false);
    }

    //  Get the mass centers:
    vector<Point2f> mc(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
    }

    // Draw contours
    drawing = Mat::zeros(cannyOut.size(), CV_8UC3);
    for (int i = 0; i< contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
        circle(drawing, mc[i], 4, color, -1, 8, 0);
    }

    for (int i = 0; i < contours.size(); i++)
    {
        cout << "Contour: " << i << " Area: " << contourArea(contours[i]) << " Length: " << arcLength(contours[i], true) << "\n";
    }
}

void * test(void *objects) {
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
            
    Mat imgOriginal, imgGray, imgThresholded, imgNormalized, drawing;

    vector<Mat> channels;

    // TODO: Comprobar que funciona con un solo frame

    while(1) {
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
        values[0] = -1.0; // Blue channel value
        values[1] = 2.0; // Green channel value
        values[2] = -1.0; // Red channel value

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
        double binary = threshold(imgNormalized, imgThresholded, 180, 255, THRESH_BINARY);        	

        /* Creamos una lista con todos los objetos detectados */
//        detectMultiObject(imgThresholded, imgOriginal, list->objects);
        detect(imgThresholded, imgOriginal, drawing, list->objects, binary);

//        imshow("Thresholdede", imgThresholded);
        imshow("Original", imgOriginal);
        imwrite( "../img/MultiOri.jpg", imgOriginal );
        imshow("Shapes", drawing);
        imwrite( "../img/Shapes.jpg", drawing );
//        imshow("Excess of green", imgGray);
        waitKey(30);
    }
}

int main() {
    
    t_Coordenada obj;
    pthread_t t1;
    int rc = pthread_create(&t1, NULL, test, &obj);
    while(true);

    return 0;
}

