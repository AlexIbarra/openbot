#ifndef MODULOCAMARA_H
#define MODULOCAMARA_H

#include <list>
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

typedef struct {
    int x;
    int y;
} t_Coordenada;

typedef struct {
    list<t_Coordenada> objects;
} t_Lista;

/*! \brief Funcion que permite detectar objetos y calcular sus coordenadas
 *  \param objects Referencia generia a un tipo lista de coordenadas
 * 
 *  Esta funcion se encarga de capturar fotogramas con la camara del robot para
 *  detectar objetos en su campo de vision y calcular las coordenadas de dichos
 *  objetos. Estas coordenadas se retornan por referencia a traves de del
 *  parametro "objects".
 */
void * trackMultiObjects(void * objects);

/*! \brief Funcion que permite hacer el seguimiento de las coordenadas de un objeto
 *  \param obj Referencia generia a un tipo coordenada
 * 
 *  Esta funcion se encarga de capturar fotogramas con la camara del robot para
 *  hacer el seguimiento de un objeto mediante el calculo de sus coordenadas.
 */
void * trackObject(void * obj);

#endif /* MODULOCAMARA_H */