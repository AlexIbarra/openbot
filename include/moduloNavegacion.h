#ifndef MODULONAVEGACION_H
#define MODULONAVEGACION_H

#include <vector>

using namespace std;

/** NOTA DE USO **
    Es necesario incluir en el proyecto los siguientes ficheros (incluidos en el repositorio del proyecto): 
        - HashMap.h
        - Hash.h
        - Exceptions.h
*/

#define INIT_X_PX 320 
#define INIT_Y_PX 480

//Tipo que se devuelve en la función "pxToCm", que devuelve x e y en centímetros.
typedef struct{
    int x;
    int y;
} t_Punto;

//Tipo usado en los vectores de X, para tener el valor tanto en píxeles como en centímetros.
typedef struct{
    int x_px;
    int x_cm;
} tElemento_x;

//Tipo usado en el "valor" del hash_map, que contiene la equivalencia de la Y en cm y el vector de X asociadas
typedef struct{
    vector<tElemento_x> ejeX_vector;
    int y_cm;
} tElemento_y;

/*! 
 *  \brief Funcion que calcula la distancia entre dos puntos
 *  \param x1 Coordenada X del primer punto
 *  \param y1 Coordenada y del primer punto
 *  \param x2 Coordenada X del segundo punto
 *  \param y2 Coordenada Y del segundo punto
 *  \return Distancia entre los dos puntos
 * 
 */
int distancia(int x1, int y1, int x2, int y2);

/*! 
 *  \brief Funcion que convierte una posicion en px a su equivalente en cm
 *  \param x_px Posicion en px de un punto en el eje X
 *  \param y_px Posicion en px de un punto en el eje Y
 *  \return Coordenadas de un punto en cm
 * 
 */
t_Punto pxToCm(int x_px, int y_px);

/*! 
 *  \brief Funcion ecargada de realizar la carga de las estructuras del modulo
 * 
 * Esta función es la que rellena las estructuras con los valores que hemos 
 * tomado de las fotos de la cuadrícula.
 */
void iniciaNavegacion();

#endif /* MODULONAVEGACION_H */
