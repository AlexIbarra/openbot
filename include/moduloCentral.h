#ifndef MODULOCENTRAL_H
#define MODULOCENTRAL_H
#include "moduloCamara.h"

typedef struct {
    t_Coordenada coordenada;
    int sector;
    int distancia;	
} t_DatoVision;


/*! \brief Funcion principal del robot
 * 
 *  Esta funcion es la encargada de conectar con los distintos modulos
 *  del robot para llevar a cabo el procesameinto de la imagen tomada con
 *  la camara, el calculo de las coordenadas de los objetos detectados y
 *  el calculo de la trayectoria que debe tomar el robot para visitar
 *  los objetos.
 */
void run();

#endif /* MODULOCENTRAL_H */

