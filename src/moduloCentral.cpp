#include <unistd.h>
#include <wiringPi.h>
#include <mosquitto.h>
#include "moduloMotor.h"
#include "moduloBroker.h"
#include "moduloCentral.h"

int run( void ) {

    int x = 0, y = 0;
////    while (1) {

    //La pantalla mide 640 de ancho, establecemos el centro entre 300 y 340
    if (x >= 0 && x <= 300) {
        rotaDcha();
        usleep(5000000); //Mirar un tiempo para que se mueva un poco solo
        parar();
    }
    else if (x > 300 && x < 340) { //Está centrado
        avanza();
        usleep(5000000);
        parar();
    }
    else { 
        rotaIzq();
        usleep(5000000);
        parar();
    }

//    }
        
    return 0;
}
