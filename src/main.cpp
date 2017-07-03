#include <unistd.h>
#include <iostream>
#include <list>
#include <queue>
#include <pthread.h>
#include "moduloMotor.h"
#include "moduloCamara.h"
#include "moduloCentral.h"
#include "moduloBroker.h"
#include "Object.h"
#include "moduloEncoder.h"

using namespace std;


void testMultiObject() {
    
    //Matrix to store each frame of the webcam feed
    Mat cameraFeed;
    Mat threshold;
    Mat HSV;
    
    //video capture object to acquire webcam feed
    VideoCapture capture;
    //open capture object at location zero (default location for webcam)
    capture.open(0);
    
    while(true) {
        //store image to matrix
        capture.read(cameraFeed);

        //convert frame from BGR to HSV colorspace
        cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
        
        Object red("red");
        
        //first find red objects
        cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
        inRange(HSV,red.getHSVmin(),red.getHSVmax(),threshold);
        
        //morphological opening (removes small objects from the foreground)
        applyOpening(threshold, 2);

        //morphological closing (removes small holes from the foreground)
        applyClosing(threshold, 2);
        
        list<Object> objects;
        
        detectMultiObject(red,threshold,cameraFeed, objects);

        //delay 30ms so that screen can refresh.
        //image will not appear without this waitKey() command
        waitKey(30);
    }
}

void testRecordObjectColor() {
	Mat cameraFeed, imgHSV, threshold;
	Object object;
	
	VideoCapture cap(0);
	
	if ( !cap.isOpened() ) { // if not success, exit program
        cout << "Cannot open the web cam" << endl;
    }
    else {

		cap.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
		
		//~ namedWindow(windowName);
		
		t_Rectangle rectangle;
		
		//~ setMouseCallback(windowName, onMouse, &rectangle);
		
		while(true) {
			cap.read(cameraFeed);					
			
			cvtColor(cameraFeed, imgHSV, COLOR_BGR2HSV);
			
			recordObjectColor(&rectangle, object, cameraFeed, imgHSV);
			
			inRange(imgHSV, object.getHSVmin(), object.getHSVmax(), threshold);
			
			applyOpening(threshold, 2);
        
			applyClosing(threshold, 2);
			
			//equalizeHistogram(imgHSV, imgEqu);
			
			trackObject(object, threshold, cameraFeed);
        
			//~ imshow(windowName, cameraFeed);
			
			waitKey(30);		
		}
	}
}

void *testThresholding(void * cosas) {
	
	Mat cameraFeed, imgGray, imgThresholded, imgNormalized;
	Object object;	
	
	VideoCapture cap(0);
	
	if ( !cap.isOpened() ) { // if not success, exit program
        cout << "Cannot open the web cam" << endl;
    }
    else {

		cap.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
		
		while(true) {
			// Frame capture
			cap.read(cameraFeed);

			Mat M = Mat(1, 3, CV_32F); // 1x3 Matrix

			M.at<float>(0, 0) = 0.0;
			M.at<float>(0, 1) = -1.0;
			M.at<float>(0, 2) = 1.44;
			
			transform(cameraFeed, imgGray, M);
			
			imshow("imgGray", imgGray);
			
			applyOpening(imgGray, 2); 
			applyClosing(imgGray, 2);					
			
			// Histogram normalization
			normalize(imgGray, imgNormalized, 0, 255, NORM_MINMAX);
			
			imshow("Image imgNormalized", imgNormalized);	
			
			threshold(imgNormalized, imgThresholded, 180, 255, THRESH_BINARY);
			
			applyOpening(imgThresholded, 2);
			applyClosing(imgThresholded, 2);
			
			list<Object> objects;
			
			detectMultiObject(object, imgThresholded, cameraFeed, objects);	        
			
			imshow("Threshold Binarization Image", imgThresholded);			
			imshow("Original Image", cameraFeed);			
			
			waitKey(1);		
		}
	}

}



int main( void ) {
	   
    int encI, encD, rc;
    pthread_t thread1 = 1, thread2, thread3;
    t_DatosCamara datosCamara;
    t_Encoder datosEncIzq, datosEncDer;
    
    Camara * cam = new Camara();//new Camara(iLowH, iHighH, iLowS, iHighS, iLowV, iHighV);
    
    initMotores();
    initEncoders();

    datosEncDer.enable = datosEncIzq.enable = 0;
    
    try {

        rc = pthread_create(&thread1, NULL, captura, (void *)&datosCamara);

        encI = pthread_create(&thread2, NULL, cuentaIzq, (void *)&datosEncIzq);

        encD = pthread_create(&thread3, NULL, cuentaDer, (void *)&datosEncDer);

        while(1){
            run(datosCamara, datosEncIzq, datosEncDer);
        }

    } catch (const exception& e){
        cerr << "Fatal error ocurred" << endl;
    }

    return 0;
}
