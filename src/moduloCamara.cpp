#include <unistd.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "moduloCamara.h"
#include <stdio.h>
#include <queue>

using namespace cv;
using namespace std;

#define DEBUG 0

Camara::Camara() {
    x = 0;
    y = 0;
}

Camara::Camara(int ilowh, int ihighh, int ilows, int isighs, int ilowv, int ihighv) {
    x = 0;
    y = 0;
    iLowH = ilowh;
    iHighH = ihighh;
    iLowS = ilows; 
    iHighS = isighs;
    iLowV = ilowv;
    iHighV = ihighv;
    
}

int Camara::getX() {
    return x;
}

int Camara::getY() {
    return y;
}

//Las inicializamos en el punto medio de la pantalla, para que no se muevan los motores de inicio
void *captura(void *thread_cola) {

	t_Coordenada *coordenada = (t_Coordenada *)thread_cola;
	
	int iLowH = 170;
    int iHighH = 179;

    int iLowS = 80; //50 si hay mucha luz de sol
    int iHighS = 255;

    int iLowV = 60;
    int iHighV = 255;
	
    VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() )  // if not success, exit program
    {
        cout << "Cannot open the web cam" << endl;
        //return -1;
    }

    //namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    int dimensFoto = 0;

    int iLastX = -1; 
    int iLastY = -1;

    //Capture a temporary image from the camera
    Mat imgTmp, dst;
    cap.read(imgTmp); 

    //Create a black image with the size as the camera output
    Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;
 
cout << "Antes de while" << endl;
  while (true) {
        Mat imgOriginal;
        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
			//break;
        }
		
//		equalizeHist(imgOriginal,dst);
		
        Mat imgHSV;
        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
        Mat imgThresholded;
        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
      
        //morphological opening (removes small objects from the foreground)
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

        //morphological closing (removes small holes from the foreground)
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

        //Calculate the moments of the thresholded image
        Moments oMoments = moments(imgThresholded);

        double dM01 = oMoments.m01;
        double dM10 = oMoments.m10;
        double dArea = oMoments.m00;

        int rows, cols;
        if(dimensFoto == 0) {
            rows = imgThresholded.rows;
            cols = imgThresholded.cols;
            line(imgLines, Point(cols/2, iLastY), Point(cols/2, rows), Scalar(0,0,255), 2);
            dimensFoto++;
        }
        
        if (DEBUG)
			cout << "dArea: " << dArea << endl;

        // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
        if (dArea > 10000) {
            //calculate the position of the ball
            int posX = dM10 / dArea;
            int posY = dM01 / dArea;
			
            /*if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
            {
                //Draw a red line from the previous point to the current point
                line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,255,0), 2);
            }*/

            iLastX = posX;
            iLastY = posY;

            coordenada->pos_x = posX;
            coordenada->pos_y = posY;
            
        }
        else{
			coordenada->pos_x = -1;
			coordenada->pos_y = -1;
		}

		//sleep(1);

        //imshow("Thresholded Image", imgThresholded); //show the thresholded image

        //imgOriginal = imgOriginal + imgLines;
        //imshow("Original", imgOriginal); //show the original image

	
  }// fin while
  pthread_exit(NULL);
}
