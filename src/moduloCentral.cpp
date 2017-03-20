#include <unistd.h>
#include <wiringPi.h>
#include <mosquitto.h>
#include "moduloMotor.h"
#include "moduloBroker.h"
#include "moduloCentral.h"

int run( int x, int y, int moviAnte) {
	cout << "X " << x << endl;
	cout << "Y " << y << endl;
	int movi = moviAnte;
    
////    while (1) {

    //La pantalla mide 640 de ancho, establecemos el centro entre 300 y 340
    if (x > 0 && x <= 270 && moviAnte != 1) {
        rotaIzq();
        
        cout << "izquierda " << endl;
        movi = 1;
    }
    else if (x > 270 && x < 380 ) { //Está centrado
	   
	   
		if(y < 440 && moviAnte != 2){
			avanza();
			cout << "avanza " << endl;
			movi = 2;
		}else if (y>=440 && moviAnte !=0){
			cout << "parar " << endl;
			parar();
			movi = 0 ;
		}
    }
    else if(x >=380 && x <= 640 && moviAnte != 3){ 
        
        rotaDcha();
        cout << "derecha " << endl;
        movi = 3;
      }else if(x == 0 && y == 0){
		parar();
	}
	
//    }
        
    return movi;
}
