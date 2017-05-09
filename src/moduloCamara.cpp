#include <unistd.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "moduloCamara.h"
#include "Object.h"
#include <stdio.h>
#include <vector>
#include <list>

using namespace cv;
using namespace std;

#define DEBUG 1

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

void onMouse(int event, int x, int y, int flags, void * params) {
	
	t_Rectangle * rectData = (t_Rectangle *)params;
	
	if(event == CV_EVENT_LBUTTONDOWN) { // se pulsa el boton izquierdo
		rectData->initialClickPoint = Point(x, y);
		//rectData->rectangleSelected = false;
	}
	else if(event == CV_EVENT_MOUSEMOVE) { // se mueve el raton
		rectData->currentMousePoint = Point(x, y);
		//rectData->rectangleSelected = false;
		rectData->mouseMove = true;
	}
	else if(event == CV_EVENT_LBUTTONUP) { // se suelta el boton izquierdo
		rectData->rectangle = Rect(rectData->initialClickPoint, rectData->currentMousePoint);
		rectData->rectangleSelected = true;
		rectData->mouseMove = false;
	}
	/*else if (event == CV_EVENT_RBUTTONDOWN) { // se pulsa el boton derecho
		
		// si se pulsa el boton derecho podemos hacer
		// que se reseten los valores HSV del objeto		
	}*/
}

void recordObjectColor(t_Rectangle * rectData, Object &object, Mat cameraFeed, Mat hsvFrame) {
	
	if(rectData->rectangleSelected && !rectData->mouseMove)	{ // si se ha terminado de dibujar el rectangulo
		vector<int> h, s, v;
		
		if(rectData->rectangle.width < 1 || rectData->rectangle.height < 1) {
			cout << "Dibuja un rectangulo, no una linea" << endl;
		}
		else {
			// recorro todo el rectangulo cogiendo los valores (HSV) de cada pixel
			for(int i = rectData->rectangle.x; i < rectData->rectangle.x + rectData->rectangle.width; i++) {
				for(int j = rectData->rectangle.y ; j < rectData->rectangle.y + rectData->rectangle.height; j++) {
					h.push_back((int)hsvFrame.at<Vec3b>(j, i)[0]);
					s.push_back((int)hsvFrame.at<Vec3b>(j, i)[1]);
					v.push_back((int)hsvFrame.at<Vec3b>(j, i)[2]);
				}
			}
		}
		
		rectData->rectangleSelected = false;
		
		// Asigno los valores HSV maximos y minimos
		if(h.size() > 0) {
			int hmin, hmax, smin, smax, vmin, vmax;
			
			hmin = *min_element(h.begin(), h.end());
			smin = *min_element(s.begin(), s.end());
			vmin = *min_element(v.begin(), v.end());
			
			object.setHSVmin(hmin, smin, vmin);
			
			hmax = *max_element(h.begin(), h.end());
			smax = *max_element(s.begin(), s.end());
			vmax = *max_element(v.begin(), v.end());
			
			object.setHSVmax(hmax, smax, vmax);
		}
		
	}
	else if(rectData->mouseMove) { // dibujo el rectangulo mientras no se suelte el boton izq.
		rectangle(cameraFeed, rectData->initialClickPoint, rectData->currentMousePoint, Scalar(0, 255, 0));
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

void trackObject(Object &object, Mat threshold, Mat &cameraFeed) {
	
	Moments oMoments = moments(threshold);

	double dM01 = oMoments.m01;
	double dM10 = oMoments.m10;
	double dArea = oMoments.m00;
	
	if (DEBUG)
		cout << "dArea: " << dArea << endl;

	// if the area <= 10000, I consider that the there are no object 
	// in the image and it's because of the noise, the area is not zero 
	if (dArea > 10000) {
		//calculate the position of the ball
		int posX = dM10 / dArea;
		int posY = dM01 / dArea;
		

		object.setXPos(posX);
		object.setYPos(posY);
		
		// Le dibujamos un circulo al objeto
		circle(cameraFeed, Point(posX, posY), 2, Scalar(0, 255, 0));
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
void *captura(void *thread_cola) {
	
	t_Coordenada *coordenada = (t_Coordenada *)thread_cola;   
	
    VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() ) { // if not success, exit program
        cout << "Cannot open the web cam" << endl;
    }    

    //Capture a temporary image from the camera
    Mat imgTmp, dst;
    cap.read(imgTmp); 

    //Create a black image with the size as the camera output
    Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );
 
    
    while (true) {
        
		Mat imgOriginal, imgGray, imgThresholded, imgNormalized;
        
		vector<Mat> channels;
		
        bool bSuccess = cap.read(imgOriginal);

        if (!bSuccess) {
            cout << "Cannot read a frame from video stream" << endl;
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
		detectMultiObject(object, imgThresholded, imgOriginal, coordenada->lista);
		
		/*imshow("Threshold Binarization Image", imgThresholded);			
		imshow("Original Image", imgOriginal);
		
		cout << "Num objetos: " << coordenada->lista.size() << endl;
		int i = 0;
		while (!coordenada->lista.empty()) {
			cout << "Objeto " << i << ": pos_x(" << 
			coordenada->lista.front().getXPos() << 
			") pos_y(" << coordenada->lista.front().getYPos() << ")" << endl;
			i++;
			coordenada->lista.pop_front();
		}*/
	

        /*Moments oMoments = moments(imgThresholded);

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


        imshow("Thresholded Image", imgHSV); //show the thresholded image

        //imgOriginal = imgOriginal + imgLines;
        imshow("Original", imgOriginal); //show the original image*/
        
        waitKey(2); //wait for key press
        
  }// fin while
    
  //~ pthread_exit(NULL);
}
