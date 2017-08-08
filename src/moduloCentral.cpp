#include <unistd.h>
#include <wiringPi.h>
#include <vector>
#include <mosquitto.h>
#include "moduloMotor.h"
#include "moduloCentral.h"
//NEW
//#include "moduloCamara.h"
//OLD
#include "moduloCamara_old.h"

#include "moduloNavegacion.h"

#include <pthread.h>

#define DEBUG 1


t_EstadoBusca calculaEstado( int x, int y, t_EstadoBusca ultSt) {
	if(y>=440 && x >= 150 && x <= 440) {
		if(DEBUG)
			cout << "st_encontrado" << endl;
		return st_encontrado;
	}
	else if (x >= 0 && x < 100) {
		if(DEBUG)
			cout << "st_izq" << endl;
		return st_izq;
	}
	else if (x >=100 && x < 250) {
		if(DEBUG)
			cout << "st_trayizq" << endl;
		return st_trayizq;
	}
	else if (x >=200 && x <= 390) {
		if(DEBUG)
			cout << "st_recto" << endl;
		return st_recto;
	}
	else if (x > 390 && x <= 540) {
		if(DEBUG)
			cout << "st_trayder" << endl;
		return st_trayder;
	}
	else if (x > 540 && x <= 640) {
		if(DEBUG)
			cout << "st_der" << endl;
		return st_der;
	}
	else if (x == -1 && y == -1 && ultSt != st_buscaPuto) {
		if(DEBUG)
			cout << "st_perdido" << endl;
		return st_perdido;
	}
	else {
		if(DEBUG)
			cout << "ultSt" << endl;
		return ultSt;
	}
}

// Recorre la lista de objetos capturada, convierte pixeles a cm y devuelve el punto mas cercano
void buscaPuntoCercano(list<t_Coordenada> objetos, int cuadrante, t_DatoVision &punto) {
	
	int size = objetos.size();
	int dist;
	t_Coordenada obj;
	
	for (int i = 0; i < size; i++) {
		obj = objetos.front();
		objetos.pop_front();
		// TODO: llamar a la funcion que convierte t_Coordenada a cm.
		dist = distancia(INIT_X_PX, INIT_Y_PX, obj.x, obj.y);
		if (dist < punto.distancia) {
			punto.distancia = dist;
			punto.coordenada.x = obj.x;
			punto.coordenada.y = obj.y;
			punto.cuadrante = cuadrante;
		}
	}
}

void buscaPuntoCercano_old(t_Coordenada aux, int cuadrante, t_DatoVision &punto) {
	
	int dist;
		
	// TODO: llamar a la funcion que convierte t_Coordenada a cm.
	dist = distancia(INIT_X_PX, INIT_Y_PX, aux.x, aux.y);
	if (dist < punto.distancia) {
		punto.distancia = dist;
		punto.coordenada.x = aux.x;
		punto.coordenada.y = aux.y;
		punto.cuadrante = cuadrante;
	}
}


void visitaPunto() {
	bool visitado = false;
	t_Coordenada obj;
	t_EstadoBusca st, ultSt;
	ultSt = st_recto;
	
	//pthread_t thread1 = 1;
	//int rc;
	
	//rc = pthread_create(&thread1, NULL, &trackObject, (void*)&obj);
	
	while (!visitado) {
		// determino la pos x,y del objeto que esta viendo la camara
		// TODO: probar si va lento para lanzar en otro hilo
		
		//NEW
		//trackObject(obj);
		
		//OLD
		captura(obj, 1);
		
		cout << "Voy al punto: " << obj.x << "   " << obj.y << endl;
		
		// Calculo el estado al que tengo que ir
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
    t_Coordenada aux;
    masCercano.coordenada.x = INF;
    masCercano.coordenada.y = INF;
    masCercano.cuadrante = 0;
    masCercano.distancia = INF;

	t_GlobalSt estado = st_buscaPunto;
	
	while (true) {
		
		// En este estado se hace la busqueda del objeto al que se va a visitar
		if (estado == st_buscaPunto) {
			for (int i = 0; i < NUM_CUADRANTES; i++) {
				
				//NEW
				//captura(objetos); // devuelve una lista de objetos
				
				//OLD
				//cout << "llamada a captura " << endl;
				captura(aux, 5); // devuelve una lista de objetos
				
				//NEW			
				//buscaPuntoCercano(objetos, i, masCercano); // determino cual es el objeto mas cercano
				
				//OLD
				//cout << "llamada a busca punto " << endl;
				buscaPuntoCercano_old(aux, i, masCercano); // determino cual es el objeto mas cercano
				
				// TODO: giraFoto() tendra que conocer cual es el objeto a visitar
				// para determinar cual va a ser la direccion del giro
				giraFoto(); // giro hasta donde esta el punto que quiero visitar
			}
			sleep(2);
			estado = st_visitaPunto;
			
			cout << "Mas cercano " << masCercano.cuadrante << endl;
			
		} // en este estado se realiza la visita al objeto
		else if (estado == st_visitaPunto) {
			// se llama a una funcion que realice el tracking de un
			// solo objeto (no hay que usar captura)
			for (int i = 0; i < masCercano.cuadrante; i++) {
				giraFoto(); // giro hasta donde esta el punto que quiero visitar
				if(DEBUG)
					cout << "Girando a cuadrante " << i << endl;
			}
			visitaPunto();
			estado = st_buscaPunto;
			masCercano.distancia = INF;
		}
	}
	
}




//~ void ejecuta() {
	//~ int totalGiros = 6;
	//~ int giros = 0, i, distancia_minima = 500; //Una distancia muy grande para que cualquier punto sea mejor
	//~ t_Coordenada coordenada;
	//~ t_EstadoInicial punto_aux, punto_objetivo;
	//~ vector<t_EstadoInicial> puntos;
	//~ vector<int> distancias;
	//~ t_Punto punto;
	//~ 
	//~ switch(st) {
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
			//~ 
		//~ case st_izq:
			//~ rotaIzq();
			//~ break;
			//~ 
		//~ case st_trayizq:
			//~ trayectoriaIzq();
			//~ break;
		//~ case st_recto:
			//~ avanza();
			//~ break;
			//~ 
		//~ case st_trayder:
			//~ trayectoriaDer();
			//~ break;
			//~ 
		//~ case st_der:
			//~ rotaDcha();
			//~ break;
			//~ 
		//~ case st_encontrado:
			//~ avanza();
			//~ usleep(5000000);
			//~ parar();
			//~ break;
	//~ }
//~ }
