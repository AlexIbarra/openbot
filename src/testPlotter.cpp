#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include "moduloCamara.h"

// Para compilar: g++ ../obj/moduloCamara.o -o testPlotter testPlotter.cpp `pkg-config --libs opencv` -lpthread -I../include/

void * test(void *data) {
    t_Coordenada *object;

    VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() ) { // if not success, exit program
        cout << "Cannot open the web cam" << endl;
    }
    
    Mat imgOriginal, imgGray, imgThresholded, imgNormalized, imgPlotter;
	
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
//        modifyChannels(values, ExG);
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
 
//        cout << "AREA: " << area << endl;
        if (area > 10000 && area <= 1500000) {
            //calculate the position of the ball
            cout << "FLAG" << endl;
            object->x = dM10 / area;
            object->y = dM01 / area;
            cout << "FLAG2" << endl;

//            circle(imgOriginal, Point(object->x, object->y), 10, Scalar(255, 0, 0));
        }
        
        imshow("Thresholdede", imgThresholded);                 
        imshow("Original", imgOriginal);
        histogramCalculation(imgOriginal, imgPlotter);
        imshow("Plotter", imgPlotter);
        imwrite( "../img/Plotter.jpg", imgPlotter );
        waitKey(10);
    }
}

int main(void) {
    
    pthread_t t1;
    t_Coordenada object;
    int rc = pthread_create(&t1, NULL, trackObject, &object);
    while(true); 
    
    return 0;
}