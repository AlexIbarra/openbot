#include <unistd.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "moduloCamara.h"
#include "Object.h"
#include <stdio.h>
#include <queue>
#include <vector>

using namespace cv;
using namespace std;

#define DEBUG 1

const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
const int MAX_NUM_OBJECTS=50;
const int MIN_OBJECT_AREA = 20*20;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;

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

void equalize() {
    namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
    namedWindow("Histogram Equalized", CV_WINDOW_AUTOSIZE);
    
    VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() ) { // if not success, exit program
        cout << "Cannot open the web cam" << endl;
    }
    
    Mat imgOri, imgEqu;
    vector<Mat> channels; 
    
    // Hacemos una captura
    cap.read(imgOri);
    
    // Cambiamos el formato de color (BGR a YCrCb)
    cvtColor(imgOri, imgEqu, CV_BGR2YCrCb);
    
    // Dividimos los canales de la imagen ecualizada en un vector
    split(imgEqu,channels);
    
    // Realizamos la ecualizacion del canal 0 (Y)
    equalizeHist(channels[0], channels[0]);
    
    // Volvemos a juntar los canales (ecualizado Y)
    merge(channels,imgEqu);
    
    // Volvemos a cambiar el formato de color para que se pueda mostrar correctamente (YCrCb a BGR)
    cvtColor(imgEqu, imgEqu, CV_YCrCb2BGR);
    
    imshow("Original Image", imgOri);
    imshow("Histogram Equalized", imgEqu);
    
    waitKey(0); //wait for key press

    destroyAllWindows(); //destroy all open windows
}

void detectMultiObject(Object theObject,Mat threshold,Mat HSV, Mat &cameraFeed) {

    vector <Object> objects;
    Mat temp;
    threshold.copyTo(temp);
    
    //these two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    //find contours of filtered image using openCV findContours function
    findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
        
    double refArea = 0;
    bool objectFound = false;
    
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
                if(area > MIN_OBJECT_AREA){

                    Object object;

                    object.setXPos(moment.m10/area);
                    object.setYPos(moment.m01/area);
                    object.setType(theObject.getType());
                    object.setColor(theObject.getColor());

                    objects.push_back(object);

                    objectFound = true;
                }
                else {
                    objectFound = false;
                }
            }
            
//            if(objectFound ==true){//let user know you found an object                
//                drawObject(objects,cameraFeed,temp,contours,hierarchy);//draw object location on screen
//            }

        }
        else {
            putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
        }
    }
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

    if ( !cap.isOpened() ) { // if not success, exit program
        cout << "Cannot open the web cam" << endl;
    }

    //namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    int dimensFoto = 0;

    int iLastX = -1; 
    int iLastY = -1;

    //Capture a temporary image from the camera
    Mat imgTmp, dst;
    cap.read(imgTmp); 

    //Create a black image with the size as the camera output
    Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );
 
    if (DEBUG)
        cout << "Antes de while" << endl;
    
    while (true) {
        Mat imgOriginal;
        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

         if (!bSuccess) { //if not success, break loop
            cout << "Cannot read a frame from video stream" << endl;
        }		
	
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
			

            iLastX = posX;
            iLastY = posY;

            coordenada->pos_x = posX;
            coordenada->pos_y = posY;
            
        }
        else {
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
