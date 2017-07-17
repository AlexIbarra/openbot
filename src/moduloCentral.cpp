#include <unistd.h>
#include <wiringPi.h>
#include <vector>
#include <mosquitto.h>
#include "moduloMotor.h"
#include "moduloBroker.h"
#include "moduloCentral.h"
#include "moduloCamara.h"
#include "moduloNavegacion.h"


t_EstadoBusca calculaEstado( int x, int y, t_EstadoBusca ultSt) {
	if(y>=440 && x >= 100 && x <= 540) {
		return st_encontrado;
	}
	else if (x >= 0 && x < 100) {
		return st_izq;
	}
	else if (x >=100 && x < 250) {
		return st_trayizq;
	}
	else if (x >=200 && x <= 390) {
		return st_recto;
	}
	else if (x > 390 && x <= 540) {
		return st_trayder;
	}
	else if (x > 540 && x <= 640) {
		return st_der;
	}
	else if (x == -1 && y == -1 && ultSt != st_inicial) {
		return st_perdido;
	}
	else {
		return ultSt;
	}
}

void ejecuta() {
	int totalGiros = 6;
	int giros = 0, i, distancia_minima = 500; //Una distancia muy grande para que cualquier punto sea mejor
	t_Coordenada coordenada;
	//~ t_EstadoInicial punto_aux, punto_objetivo;
	//~ vector<t_EstadoInicial> puntos;
	//~ vector<int> distancias;
	//~ t_Punto punto;
	
	switch(st) {
		//~ case st_inicial:
			//~ //rotaIzq();
			//~ 
			//~ while (giros < totalGiros){
			//~ 
				//~ captura((void *)&coordenada);
				//~ cout << coordenada.pos_x << "   " << coordenada.pos_y << endl;
				//~ 
				//~ punto_aux.coordenada = coordenada;
				//~ punto_aux.cuadrante = giros;
				//~ puntos.push_back(punto_aux);
				//~ 
				//~ cout << "llamada gira foto  " << giros << endl;
				//~ giraFoto();
						//~ 
				//~ giros++;
			//~ }
			//~ 
			//~ i = 0;
			//~ while (i < puntos.size()){
				//~ cout << "vector :" << i << " X: "  << puntos[i].coordenada.pos_x << " Y: "  << puntos[i].coordenada.pos_y << " cuandrante " << puntos[i].cuadrante << endl;
				//~ 
				//~ if ((puntos[i].coordenada.pos_x != -1) && (puntos[i].coordenada.pos_y != -1)){
					//~ 
					//~ punto = pxToCm(puntos[i].coordenada.pos_x , puntos[i].coordenada.pos_y);
					//~ puntos[i].distancia = distancia(0, 0,  punto.x , punto.y);
					//~ cout << "distancia :" << puntos[i].distancia << endl;
					//~ 
					//~ //Actualizar el punto más cercano si está mas cerca que el actual
					//~ if(puntos[i].distancia < distancia_minima){
						//~ punto_objetivo.coordenada.pos_x = puntos[i].coordenada.pos_x;
						//~ punto_objetivo.coordenada.pos_y = puntos[i].coordenada.pos_y;
						//~ punto_objetivo.cuadrante = puntos[i].cuadrante;
						//~ punto_objetivo.distancia = puntos[i].distancia;
						//~ distancia_minima = punto_objetivo.distancia;
					//~ }
				//~ }
				//~ i++;
				//~ cout << "Distancia minima  " << distancia_minima <<  endl;
				//~ cout << "Cuadrante del punto objetivo  " << punto_objetivo.cuadrante <<  endl;
				//~ cout << endl;
			//~ }
			//~ cout << "Salgo del while y hay que buscar el punto mas cercano del vector" << endl;
			//~ 
			//~ i=0;
			//~ while (i < punto_objetivo.cuadrante){
				//~ giraFoto();
				//~ i++;
			//~ }
			//~ 
			//~ cout << "HE ACABADO " << endl;
			//~ sleep(5);
			//~ 
		//~ break;
			
		case st_izq:
			rotaIzq();
			break;
			
		case st_trayizq:
			trayectoriaIzq();
			break;
		case st_recto:
			avanza();
			break;
			
		case st_trayder:
			trayectoriaDer();
			break;
			
		case st_der:
			rotaDcha();
			break;
			
		case st_encontrado:
			avanza();
			usleep(5000000);
			parar();
			break;
	}
}

// Recorre la lista de objetos capturada, convierte pixeles a cm y devuelve el punto mas cercano
void buscaPuntoCercano(list<t_Coordenada> objetos, int cuadrante, t_DatoVision &punto) {
	
	int size = objetos.size();
	t_Coordenada obj;
	punto.cuadrante = cuadrante;
	
	for (int i = 0; i < size; i++) {
		obj = objetos.front();
		objetos.pop_front();
		// TODO: llamar a la funcion que convierte t_Coordenada a cm.
		obj.distancia = pxToCm(punto.coordenada.x, punto.coordenada.y);
		punto.distancia = pxToCm(obj.x, obj.y);
		if (obj.distancia < punto.distancia) {
			punto.distancia = obj.distancia;
			punto.coordenada.x = obj.x;
			punto.coordenada.y = obj.y;
		}
	}
}

void visitaPunto() {
	bool visitado = false;
	t_Coordenada obj;
	t_EstadoBusca st, ultSt;
	
	wihle (!visitado) {
		// determino la pos x,y del objeto que esta viendo la camara
		trackObject(obj);
		
		// Calculo el estado al que tengo que ir
		ultSt = st_recto;
		st = calculaEstado( obj.x, obj.y, ultSt);
		
		// Ejecuto la accion del robot segun el estado
		switch(st) {
			case st_izq:
				rotaIzq();
				break;				
			case st_trayizq:
				trayectoriaIzq();
				break;
			case st_recto:
				avanza();
				break;				
			case st_trayder:
				trayectoriaDer();
				break;				
			case st_der:
				rotaDcha();
				break;				
			case st_encontrado: // Una vez visitado, salgo de la funcion
				avanza();
				usleep(5000000);
				parar();
				visitado = true;
				break;
		}
		
		// Actualizo el ultimo estado
		ultSt = st;
	}
}

int run() {
    
    list<t_Coordenada> objetos;
    t_DatoVision masCercano;
    masCercano.coordenada.x = 0;
    masCercano.coordenada.y = 0;
    masCercano.cudrante = 0;
    masCercano.distancia = INF;

	t_GlobalSt estado = st_buscaPuto;
	
	while (true) {
		
		// En este estado se hace la busqueda del objeto al que se va a visitar
		if (estado == st_buscaPuto) {
			for (int i = 0; i < NUM_CUADRANTES; i++) {
				captura(objetos); // devuelve una lista de objetos
				buscaPuntoCercano(objetos, i, masCercano); // determino cual es el objeto mas cercano
				// TODO: giraFoto() tendra que conocer cual es el objeto a visitar
				// para determinar cual va a ser la direccion del giro
				giraFoto(); // giro hasta donde esta el punto que quiero visitar
			}
			estado = st_visitaPunto;
		} // en este estado se realiza la visita al objeto
		else if (estado == st_visitaPunto) {
			// se llama a una funcion que realice el tracking de un
			// solo objeto (no hay que usar captura)
			visitaPunto();
			estado = st_buscaPuto;
			masCercano.distancia = INF;
		}
	}
	
}
