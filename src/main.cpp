#include <unistd.h>
#include <iostream>
#include <queue>
#include <pthread.h>
#include "moduloMotor.h"
#include "moduloCamara.h"
#include "moduloCentral.h"
#include "moduloBroker.h"

using namespace std;


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

    int x,y, rc, moviAnte = -1;
    
    pthread_t thread = 1;
    queue<t_Coordenada> cola;
    
    try {
        
       // Broker * brk = new Broker ("broker", "brk_1", "127.0.0.1", 1883);
       //cam->captura();
       rc = pthread_create(&thread, NULL, captura, (void *)&cola);
       
		cout << "Cola X= " << cola.front().pos_x << endl;
		cout << "Cola Y= " << cola.front().pos_y << endl;
            
		cola.pop();
        
        while(!encontrado) {
            //cam->captura();
            /*x = cam->getX();
            y = cam->getY();
            if(moviAnte == -1 && y>=440   && x > 270 && x < 380 ){
				avanzaLento();
				usleep(7000000);
				parar();
				cout << "Encontrado" << endl;
				encontrado = true;
			}else
                 moviAnte = run(x,y, moviAnte);*/
        }
    
    } catch (const exception& e){					/// if exception occured in constructor. see class declaration.
        cerr << "Error on Network Connection.\n" \
            << "Check mosquitto is running & IP/PORT\n";
    }
    

    return 0;
}

