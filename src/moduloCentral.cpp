#include <unistd.h>
#include <wiringPi.h>
#include <vector>
#include "moduloMotor.h"
#include "moduloCentral.h"
#include "moduloCamara.h"
#include "moduloNavegacion.h"
#include <pthread.h>
#include <signal.h>

#define DEBUG 1
#define NUM_SECTORES 6
#define INF 9999

/* Estados de la maquina de estados para el calculo de direccion del robot */
typedef enum t_EstadoBusca {st_buscaPunto, st_visitaPunto, st_izq, st_der, st_trayizq, st_trayder, st_recto, st_encontrado, st_perdido};

/* 
 * ###################################################################
 * ####  Declaracion de las funciones estaticas al modulo central ####
 * ###################################################################
 */

/*! \brief Calcula el estado siguiente de la maquina de estados
 *  \param cord Coordenadas del objeto a visitar
 *  \param ultSt Ultimo estado en el que se encontraba el robot
 * 
 *  Calcula el sigueinte estado dependiento de la ubicacion del objeto que se
 *  quiere visitar. Esto permite saber que trayectoria debe tomar el robot
 *  para llegar hasta dicho objeto.
 */
static t_EstadoBusca calculaEstado( t_Coordenada cord, t_EstadoBusca ultSt) {
    t_EstadoBusca ret;
    
    if(cord.y >= 440 && cord.x >= 150 && cord.x <= 440) {
        ret = st_encontrado;
    }
    else if (cord.x >= 0 && cord.x < 100) {
        ret = st_izq;
    }
    else if (cord.x >= 100 && cord.x < 250) {
        ret = st_trayizq;
    }
    else if (cord.x >= 250 && cord.x <= 390) {
        ret = st_recto;
    }
    else if (cord.x > 390 && cord.x <= 540) {
        ret = st_trayder;
    }
    else if (cord.x > 540 && cord.x <= 640) {
        ret = st_der;
    }
    else if (cord.x == -1 && cord.y == -1 && ultSt != st_buscaPunto) {
        ret = st_perdido;
    }
    else {
        ret = ultSt;
    }
    
    return ret;
}

/*! \brief Calcula el objeto mas cercano dentro de una lista de objetos detectados
 *  \param objetos Lista con las coordenadas de los objetos detectados
 *  \param sector Sector al que se encuentra orientado el robot
 *  \param punto Objeto que sera visitado una vez calculado
 * 
 *  Determina el objeto que se encuentra mas cerca para ser visitado de una lista
 *  de objetos. Busca en toda la lista el mas cercano y actualiza el valor del
 *  parametro "punto".
 */
static void buscaPuntoCercano(list<t_Coordenada> objetos, int sector, t_DatoVision &punto) {
	
    int size = objetos.size(), dist;
    t_Coordenada obj;
    
    for (int i = 0; i < size; i++) {
        obj = objetos.front();
        objetos.pop_front();
        dist = distancia(INIT_X_PX, INIT_Y_PX, obj.x, obj.y);
        
        if (dist < punto.distancia) {
            punto.distancia = dist;
            punto.coordenada.x = obj.x;
            punto.coordenada.y = obj.y;
            punto.sector = sector;
        }
    }
}

/*! \brief Funcion que permite calcular la trayectoria para visitar un objeto detectado
 * 
 *  Esta funcion se encarga de hacer ek seguimiento de las coordenadas de un
 *  objeto y calcular la trayectoria correcta para visitarlo.
 */
static void visitaPunto() {
    bool visitado = false;
    t_Coordenada obj;
    t_Lista list;
    t_EstadoBusca st, ultSt = st_recto;

    while(!visitado) {

        trackMultiObjects((void *)&list);

        if(list.objects.size()>0){
            obj = list.objects.front();
            list.objects.pop_front();
        }

        // Calculo el estado al que tengo que ir
        st = calculaEstado( obj, ultSt);

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


/* 
 * ###########################################
 * ####  Funciones propias de la interfaz ####
 * ###########################################
 */

void run() {
    t_DatoVision masCercano;
    t_Lista list;
    int numCapturas = 3;
    masCercano.coordenada.x = INF;
    masCercano.coordenada.y = INF;
    masCercano.sector = 0;
    masCercano.distancia = INF;
    t_EstadoBusca estado = st_buscaPunto;

    while(true) {
        
        if (estado == st_buscaPunto) {

            for (int i = 0; i < NUM_SECTORES; i++) {
                for (int j = 0; j < numCapturas; j++) {
                    trackMultiObjects((void *)&list);
                }
			
                buscaPuntoCercano(list.objects, i, masCercano); // determino cual es el objeto mas cercano

                giraFoto(); // giro hasta donde esta el punto que quiero visitar
            }
            giraFoto();
            sleep(1);
            estado = st_visitaPunto;
        } // en este estado se realiza la visita al objeto
        else if (estado == st_visitaPunto) {
            // se llama a una funcion que realice el tracking de un
            // solo objeto (no hay que usar captura)
            for (int i = 0; i < masCercano.sector; i++) {
                giraFoto(); // giro hasta donde esta el punto que quiero visitar
            }
            
            visitaPunto();
            estado = st_buscaPunto;
            masCercano.distancia = INF;
        }
    }	
}