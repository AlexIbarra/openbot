#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include "moduloCamara.h"

// Para compilar (dentro del dir src): g++ ../obj/moduloCamara.o -o testDetection testDetection.cpp `pkg-config --libs opencv` -lpthread -I../include/

const char* w_name_Adapta = "Adaptative";
const char* w_name_AdaptaGau = "TAdaptative Gaussian";
const char* w_name_Threshold = "Threshold";
Mat imgOriginal, imgGray, imgThresholded, imgNormalized, imgPlotter,
            imgOtsu, imgAdaptative, imgAdaptativeGau;
const char* threshold_trackball = "Treshold Value";
const char* blocksize_trackball = "Blocksize Value";
int threshold_value = 0, blocksize_value = 0;
int const max_threshold_value = 255, max_blocksize_value = 30;



void  adaptativeCallback(int, void *) {
    adaptiveThreshold(imgNormalized, imgAdaptative, threshold_value, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, blocksize_value, 12);
}

void  adaptativeGauCallback(int, void *) {
    adaptiveThreshold(imgNormalized, imgAdaptativeGau, threshold_value, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, blocksize_value, 12);
}

void * test(void *obj) {
    t_Coordenada *object = (t_Coordenada *)obj;
	
    cout << "CtrackObject Entramos" << endl;

    VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() ) { // if not success, exit program
        cout << "Cannot open the web cam" << endl;
    }
    
    namedWindow( w_name_Adapta, WINDOW_AUTOSIZE );
//    namedWindow( w_name_AdaptaGau, WINDOW_AUTOSIZE );
//    namedWindow( w_name_Threshold, WINDOW_AUTOSIZE );
        	

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
        threshold(imgNormalized, imgThresholded, 180, 255, THRESH_BINARY);
//        
//        thresholdOtsu(imgNormalized, imgOtsu);
//        thresoldAdaptative(imgNormalized, imgAdaptative);
//        thresoldAdaptativeGaussian(imgNormalized, imgAdaptativeGau);
        
        /* trackballs para calcular el valor del umbralizacion */
//        createTrackbar( threshold_trackball, w_name_Adapta, &threshold_value, max_threshold_value, adaptativeCallback );
//        createTrackbar( blocksize_trackball, w_name_Adapta, &blocksize_value, max_blocksize_value, adaptativeCallback );
         
//        createTrackbar( trackbar_value, w_name_AdaptaGau, &threshold_value, max_value, adaptativeGauCallback );                  
        
        imshow(w_name_Threshold, imgThresholded);
        imwrite( "../img/ThresholdedMulti.jpg", imgThresholded );
//        imshow("Otsu", imgOtsu);
//        imwrite( "../img/Otsu.jpg", imgOtsu );
//        imshow(w_name_Adapta, imgAdaptative);
//        imwrite( "../img/Adaptative.jpg", imgAdaptative );
//        imshow(w_name_AdaptaGau, imgAdaptativeGau);
//        imwrite( "../img/AdaptativeGau.jpg", imgAdaptativeGau );
        
        
        
        
//        imwrite( "../img/Thresholded.jpg", imgThresholded );
//        imshow("Original", imgOriginal);
//        imwrite( "../img/Original.jpg", imgOriginal );
//        imshow("Excess of red", imgGray);
//        imwrite( "../img/EOR.jpg", imgGray );
//        imshow("Normalized image", imgNormalized);
//        imwrite( "../img/Normalized.jpg", imgNormalized );
//        histogramcalculation(imgOriginal, imgPlotter);
//        imshow("Plotter", imgPlotter);
//        imwrite( "../img/Plotter.jpg", imgPlotter );
        waitKey(10);
    }
}

int main() {
    
    t_Coordenada obj;
    pthread_t t1;
    int rc = pthread_create(&t1, NULL, test, &obj);
    while(true);

    return 0;
}

