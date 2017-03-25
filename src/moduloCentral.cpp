#include <unistd.h>
#include <wiringPi.h>
#include <mosquitto.h>
#include "moduloMotor.h"
#include "moduloBroker.h"
#include "moduloCentral.h"

#define DEBUG 0

int calculaEstado( int x, int y, int ultSt) {
	if(y>=440 && x >= 100 && x <= 540){
		return st_encontrado;
	}else if (x >= 0 && x < 100){
		return st_izq;
	}else if (x >=100 && x < 250){
		return st_trayizq;
	}else if (x >=200 && x <= 390){
		return st_recto;
	}else if (x > 390 && x <= 540){
		return st_trayder;
	}else if (x > 540 && x <= 640){
		return st_der;
	}else if (x == -1 && y == -1 && ultSt != st_inicial){
		return st_perdido;
	}else{
		return ultSt;
	}
}

void ejecuta( int st){
	switch(st){
		case st_inicial:
			//cout << "Inicial" << endl;
			if (DEBUG)
				cout << "|_____| |_____|" << endl;
			rotaIzq();
			break;
		case st_izq:
			//cout << "Rota Izquierda" << endl;
			if (DEBUG)
				cout << "|·____| |_____|" << endl;
			rotaIzq();
			break;
		case st_trayizq:
			//cout << "Trayectoria Izquierda" << endl;
			if (DEBUG)
				cout << "|____·| |_____|" << endl;
			trayectoriaIzq();
			break;
		case st_recto:
			//cout << "Recto" << endl;
			if (DEBUG)
				cout << "|_____|·|_____|" << endl;
			avanza();
			break;
		case st_trayder:
			//cout << "Trayectoria Derecha" << endl;
			if (DEBUG)
				cout << "|_____| |·____|" << endl;
			trayectoriaDer();
			break;
		case st_der:
			//cout << "Rota Derecha" << endl;
			if (DEBUG)
				cout << "|_____| |____·|" << endl;
			rotaDcha();
			break;
		case st_encontrado:
			if (DEBUG)
				cout << "Encontrado" << endl;
			avanza();
			usleep(5000000);
			for(int i=0; i<5; i++){
				rotaDcha();
				usleep(350000);
				rotaIzq();
				usleep(350000);
			}
			parar();
			break;
	}
}

int run( int x, int y, int ultSt, int ultX, int ultY) {
	
	int estado, ultimo;
    
    if (DEBUG)
		cout << "X " << x << "\tY " << y << endl;
    
    estado = calculaEstado(x, y, ultSt);
    
	if(estado == st_perdido){
		if (DEBUG)
			cout << "Perdido\t";
		ultimo = calculaEstado(ultX, ultY, ultSt);
		ejecuta(ultimo);
	}else
		ejecuta(estado);
        
    return estado;
}
 
/*int run( int x, int y, int moviAnte) {
	cout << "X " << x << endl;
	cout << "Y " << y << endl;
	int movi = moviAnte;
    
////    while (1) {

    //La pantalla mide 640 de ancho, establecemos el centro entre 300 y 340
    if (x > 0 && x <= 270 && moviAnte != 1) {
        rotaIzq();
        //usleep(1000000);
        //parar();
        cout << "izquierda " << endl;
        movi = -1;
    }
    else if (x > 270 && x < 380 ) { //Está centrado
	   
	   
		if(y < 440 && moviAnte != 2){
			avanzaLento();
			//usleep(2000000);
        //parar();
			cout << "avanza " << endl;
			movi = -1;
		}else if (y>=440 && moviAnte !=0){
			cout << "parar " << endl;
			parar();
			movi = -1 ;
		}
    }
    else if(x >=380 && x <= 640 && moviAnte != 3){ 
        
        rotaDcha();
        //usleep(1000000);
        //parar();
        cout << "derecha " << endl;
        movi = -1;
      }else if(x == 0 && y == 0){
		parar();
	}
	
//    }
        
    return movi;
}*/
