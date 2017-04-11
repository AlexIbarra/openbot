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