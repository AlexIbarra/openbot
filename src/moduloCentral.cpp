#include <unistd.h>
#include <wiringPi.h>
#include <mosquitto.h>
#include "moduloMotor.h"
#include "moduloBroker.h"
#include "moduloCentral.h"

int run( int x, int y ) {
	cout << "X " << x << endl;
	cout << "Y " << y << endl;
	
    //int x = 0, y = 0;
////    while (1) {

    //La pantalla mide 640 de ancho, establecemos el centro entre 300 y 340
    if (x > 0 && x <= 300) {
        rotaIzq();
        //usleep(5000000); //Mirar un tiempo para que se mueva un poco solo
        //parar();
        cout << "izquierda " << endl;
    }
    else if (x > 300 && x < 340) { //Está centrado
	   
	   
		if(y < 440){
			avanza();
			cout << "avanza " << endl;
		}else if (y>=440){
			parar();
		}

		//usleep(5000000);
		//parar();
    }
    else if(x >=340 && x <= 640){ 
        
        rotaDcha();
        cout << "derecha " << endl;
        //usleep(5000000);
        //parar();
    }else if(x == 0 && y == 0){
		parar();
	}
	//parar();
//    }
        
    return 0;
}
