#include <unistd.h>
#include <wiringPi.h>
#include <mosquitto.h>
#include "moduloMotor.h"
#include "moduloBroker.h"
#include "moduloCentral.h"

int calculaEstado( int x, int y, int ultSt) {
	if(y>=440 && x >= 270 && x <= 380){
		return st_encontrado;
	}else if (x >= 0 && x < 245){
		return st_izq;
	}else if (x >=245 && x < 295){
		return st_trayizq;
	}else if (x >=295 && x <= 345){
		return st_recto;
	}else if (x > 345 && x <= 395){
		return st_trayder;
	}else if (x > 395 && x <= 640){
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
			cout << "|_____| |_____|" << endl;
			rotaIzq();
			break;
		case st_izq:
			//cout << "Rota Izquierda" << endl;
			cout << "|·____| |_____|" << endl;
			rotaIzq();
			break;
		case st_trayizq:
			//cout << "Trayectoria Izquierda" << endl;
			cout << "|____·| |_____|" << endl;
			trayectoriaIzq();
			break;
		case st_recto:
			//cout << "Recto" << endl;
			cout << "|_____|·|_____|" << endl;
			avanzaLento();
			break;
		case st_trayder:
			//cout << "Trayectoria Derecha" << endl;
			cout << "|_____| |·____|" << endl;
			trayectoriaDer();
			break;
		case st_der:
			//cout << "Rota Derecha" << endl;
			cout << "|_____| |____·|" << endl;
			rotaDcha();
			break;
		case st_encontrado:
			cout << "Encontrado" << endl;
			avanza();
			usleep(5000000);
			parar();
			break;
	}
}

int run( int x, int y, int ultSt, int ultX, int ultY) {
	
	int estado, ultimo;
    
    cout << "X " << x << "\tY " << y << endl;
    
    estado = calculaEstado(x, y, ultSt);
    
	if(estado == st_perdido){
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
