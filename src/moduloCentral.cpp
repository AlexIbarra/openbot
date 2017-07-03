#include <unistd.h>
#include <math.h>
#include <queue>
#include <wiringPi.h>
#include <mosquitto.h>
#include "moduloMotor.h"
#include "moduloBroker.h"
#include "moduloCentral.h"
#include "moduloEncoder.h"

#define DEBUG 0

t_PosicionActual posActual;

bool operator<(t_Coordenada a, t_Coordenada b){
	return a.pos_x == b.pos_x && a.pos_y == b.pos_y;
}

t_Direccion obtenerDireccionVector(int x, int y){
    if (x==0)
    	return y>0 ? arriba : abajo;
    else{
    	if (y==0)
	    	return x>0 ? derecha : izquierda;
	    else{
	    	if(x>0)
	    		return y>0 ? arribaDer : abajoDer;
	    	else
	    		return y>0 ? arribaIzq : abajoIzq;
	    }
    }
}
//Angulo de giro entre los dos vectores, 0A y AB
//Angulo > 0 = Derecha
//Angulo < 0 = Izquierda
int obtenerAngulo(int x1, int y1, int x2, int y2, int x3, int y3){
    double z; 
    int a1=x2-x1, a2=y2-y1, b1=x3-x2, b2=y3-y2, signo;
    t_Direccion dirOA = obtenerDireccionVector(a1, a2);
    if (dirOA == arriba)
    	signo = x3 > x2 ? 1 : -1;
    else if(dirOA == abajo)
    	signo = x3 > x2 ? -1 : 1;
    else if(dirOA == derecha)
    	signo = y3 > y2 ? -1 : 1;
    else if(dirOA == izquierda)
    	signo = y3 > y2 ? 1 : -1;
    else{
	    //ecuacion explicita recta - y = mx + b
	    //m = pendiente recta OrigAct (recta1) y de sus paralelas
	    //y - y3 = m*(x-x3) -> y = m*x - m*x3 + y3
	    int m = (y2-y1)/(x2-x1), bO = y1 - m*x1, bP = y3 - m*x3;
	    if(dirOA == arribaIzq || dirOA == abajoIzq)
			signo = bP > bO ? 1 : -1;
		else // arribaDer || abajoDer
			signo = bP > bO ? -1 : 1;
	}

    z = (a1*b1+a2*b2)/(sqrt(a1*a1+a2*a2)*sqrt(b1*b1+b2*b2));

    return (acos(z) * 180 / PI) * signo;
}

t_EstadoBusca calculaEstado( int x, int y, t_EstadoBusca ultSt) {
	if(y>=440 && x >= 100 && x <= 540){
		return st_encontrado;
	}else if (x >= 0 && x < 100){
		return st_izq;
	}else if (x >= 100 && x < 250){
		return st_trayizq;
	}else if (x >= 250 && x <= 390){
		return st_recto;
	}else if (x > 390 && x <= 540){
		return st_trayder;
	}else if (x > 540 && x <= 640){
		return st_der;
	}else if (x == -1 && y == -1){
		return st_perdido;
	}else{
		return ultSt;
	}
}

int ejecuta(t_EstadoBusca st){
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
			break;
	}
	return total;
}

static void buscaObjetivo(t_Coordenada & actual, t_Coordenada objetivo) {
	
	t_EstadoBusca estado, ultimo;
	t_Coordenada actual, anterior;
    int x, y, ultX, ultY;
    x = actual.pos_x;
    y = actual.pos_y;
    
	estado = calculaEstado(x, y, ultimo);
	ultimo = st_recto;
    
    while(estado != st_encontrado){

	    if (DEBUG)
			cout << "X " << x << "\tY " << y << endl;
	    
	    if(estado == st_perdido){
			if (DEBUG)
				cout << "Perdido\t";
			ultimo = calculaEstado(ultX, ultY, ultimo);
			ejecuta(ultimo);
		}else{
			ejecuta(estado);
			ultX = x;	
			ultY = y;
    		ultimo = estado;
		}

		x = actual.pos_x;
	    y = actual.pos_y;

    	estado = calculaEstado(x, y, ultimo);
    }
}

void orientarse(t_Coordenada objActual, t_Coordenada objOrigen, t_Coordenada objDestino){
	int angulo = obtenerAngulo(objOrigen.pos_x, objOrigen.pos_y, 
								objActual.pos_x, objActual.pos_y,
								objDestino.pos_x, objDestino.pos_y);
	//~ girarAngulo(angulo);
}

static int busquedaInicial(t_DatosCamara & datosCamara, queue<t_Coordenada> & camino){
	int numGiros = 0, totalObjetivos = 0;
	t_Coordenada punto;
	while(numGiros < totalGiros){
		while(!datosCamara.cola.empty()){
			punto = cmToMapa(pxToCm(datosCamara.cola.top()), posActual);
			if(!existePunto(punto)){
				camino.push(punto);
				totalObjetivos++;
			}
			datosCamara.cola.pop();
		}
		giraFoto();//Saber cuanto girar de cada vez, así sabremos cuantas tandas hacer
		numGiros++;
	}
	return totalObjetivos;
}

static void todosEncontrados(){
	for(int i=0; i<5; i++){
		rotaDcha();
		usleep(350000);
		rotaIzq();
		usleep(350000);
	}
	parar();
	usleep(5000000);
}

void run(const t_DatosCamara & datosCamara, t_Encoder & datosEncIzq, t_Encoder & datosEncDer){
	t_Estado estado = st_inicial;
	t_Coordenada objActual, objOrigen, objDestino, aux;
	int totalObjetivos = 0, numObjetivos = 0;
	Queue<t_Coordenada> camino;

	objOrigen.pos_x = 50;
	objOrigen.pos_y = 50;
	objActual.pos_x = 50;
	objActual.pos_y = 50;

	posActual.coordenada.pos_x = 50;
	posActual.coordenada.pos_y = 50;
	posActual.dir = derecha;
	posActual.angulo = 0;

	do{
		switch(estado){
			case st_inicial:
				totalObjetivos = busquedaInicial(&datosCamara.coordenadas, &camino);
				estado = st_caminos;
				break;
			case st_caminos:
				camino = generaCamino(camino);
				estado = st_next;
				break;
			case st_next:
				objDestino = camino.top();
				estado = st_orienta;
				break;
			case st_orienta:
				if(objOrigen == objActual){
					aux.pos_x = 40; //Como la situacion inicial es mirando a la derecha, me invento un punto origen que este antes del 50,50 a la izquierda
					aux.pos_y = 50;//Tener cuidado con la direccion hacia la que nos quedamos mirando despues de inicial
					orientarse(objOrigen, aux, objDestino);
				}else
					orientarse(objActual, objOrigen, objDestino);
				estado = st_busca;
				break;
			case st_busca:
				objOrigen = objActual;
				objActual = objDestino;
				buscaObjetivo(&datosCamara.coordenadas, objDestino);
				camino.pop();
				numObjetivos++;
				estado = st_next;
				break;
		}
	}while(numObjetivos < totalObjetivos);

	todosEncontrados();
}
