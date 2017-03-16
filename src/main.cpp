#include <unistd.h>
#include <iostream>
#include "moduloMotor.h"
#include "moduloCamara.h"
#include "moduloCentral.h"
#include "moduloBroker.h"

using namespace std;


int main( void ) {
    
    int iLowH = 170;
    int iHighH = 179;

    int iLowS = 150; 
    int iHighS = 255;

    int iLowV = 60;
    int iHighV = 255;
    
    Camara * cam = new Camara(iLowH, iHighH, iLowS, iHighS, iLowV, iHighV);
    initMotores();
    //cam->initCamara();
    int x,y;
    try {
        
       // Broker * brk = new Broker ("broker", "brk_1", "127.0.0.1", 1883);
        
        while(1) {
            cam->captura();
            x = cam->getX();
            y = cam->getY();
            run(x,y);
        }
    
    } catch (const exception& e){					/// if exception occured in constructor. see class declaration.
        cerr << "Error on Network Connection.\n" \
            << "Check mosquitto is running & IP/PORT\n";
    }
    

    return 0;
}

