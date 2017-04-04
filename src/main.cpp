#include <unistd.h>
#include <iostream>
#include <queue>
#include <pthread.h>
#include "moduloMotor.h"
#include "moduloCamara.h"
#include "moduloCentral.h"
#include "moduloBroker.h"
#include "Object.h"

using namespace std;

const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image";
const string windowName3 = "After Morphological Operations";


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
        
        detectMultiObject(red,threshold,HSV,cameraFeed);
        
        imshow(windowName,cameraFeed);
        //imshow(windowName1,HSV);

        //delay 30ms so that screen can refresh.
        //image will not appear without this waitKey() command
        waitKey(30);
    }
}


int main( void ) {
    
    int iLowH = 170;
    int iHighH = 179;

    int iLowS = 80; //50 si hay mucha luz de sol
    int iHighS = 255;

    int iLowV = 60;
    int iHighV = 255;
    
    bool encontrado = false;
    
    Camara * cam = new Camara(iLowH, iHighH, iLowS, iHighS, iLowV, iHighV);
    initMotores();

    int x, y, ultX=-1, ultY=-1, rc, moviAnte = -1, estado = st_inicial;
    
    pthread_t thread = 1;
    //queue<t_Coordenada> cola;
    t_Coordenada coordenada;
    
    //testMultiObject();    
    //equalize();
	//captura((void *)&coordenada);

    
    try {
        
       // Broker * brk = new Broker ("broker", "brk_1", "127.0.0.1", 1883);

        rc = pthread_create(&thread, NULL, captura, (void *)&coordenada);
       	
       	while(coordenada.pos_x == -1 && coordenada.pos_x == -1) {sleep(1);}
       	        
        while(estado != st_encontrado) {
			
            x = coordenada.pos_x;
            y = coordenada.pos_y;
            
            if(coordenada.pos_x == -1 && coordenada.pos_x == -1) {sleep(1);}
            
            estado = run(x, y, estado, ultX, ultY);
            
            if (estado != st_perdido){
				ultX = x;
				ultY = y;
			}
            /*if(moviAnte == -1 && y>=440   && x > 270 && x < 380 ){
				avanza();
				usleep(5000000);
				parar();
				cout << "Encontrado" << endl;
				encontrado = true;
			}else
                 moviAnte = run(x,y, moviAnte);*/
                
        }
    
    } catch (const exception& e) {
        cerr << "Error on Network Connection.\n" << "Check mosquitto is running & IP/PORT\n";
    }
    

    return 0;
}

