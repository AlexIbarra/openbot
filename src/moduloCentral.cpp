#include <unistd.h>
#include <cmath.h>
#include <wiringPi.h>
#include <mosquitto.h>
#include "moduloMotor.h"
#include "moduloBroker.h"
#include "moduloCentral.h"
#include "moduloEncoder.h"

#define DEBUG 0

int obtenerAngulo(int x1, int y1, int x2, int y2, int x3, int y3){
    double angulo, z, a1=x2-x1, a2=y2-y1, b1=x3-x2, b2=y3-y2;
    z = (a1*b1+a2*b2)/(sqrt(a1*a1+a2*a2)*sqrt(b1*b1+b2*b2));
    return acos(z) * 180 / PI;
}

int calculaEstado( int x, int y, int ultSt, int numObjetivos, int totalObjetivos) {
	if (ultSt == st_localizar && numObjetivos == totalObjetivos){
		return st_inicial;
	}else if(ultSt == st_encontrado){
		return st_localizar;
	}else if(y>=440 && x >= 100 && x <= 540){
		return st_encontrado;
	}else if (x >= 0 && x < 100){
		return st_izq;
	}else if (x >= 100 && x < 250){
		return st_trayizq;
	}else if (x >= 200 && x <= 390){
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

int busca(int x, int y, int & total){

}

int ejecuta(int st){
	int total;
	switch(st){
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
	return total;
}

int run( int x, int y, int ultSt, int ultX, int ultY, int numObjetivos, int totalObjetivos) {
	
	int estado, ultimo;
    
    if (DEBUG)
		cout << "X " << x << "\tY " << y << endl;
    
    estado = calculaEstado(x, y, ultSt, numObjetivos, totalObjetivos);
    
    if(estado == st_perdido){
		if (DEBUG)
			cout << "Perdido\t";
		ultimo = calculaEstado(ultX, ultY, ultSt);
		ejecuta(ultimo);
	}else{
		ejecuta(estado);
	}
        
    return estado;
}