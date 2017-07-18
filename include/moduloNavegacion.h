#include <cmath>
#include <iostream>
#include <vector>
#include "HashMap.h"

using namespace std;

/** USO **
Es necesario incluir en el proyecto los siguientes ficheros (subidos al git): 
	- moduloNavegacion.h
	- HashMap.h
	- Hash.h
	- Exceptions.h
Es necesaria una llamada a iniciaNavegacion() siempre al inicio [por ejemplo en main, cuando se inicializan los motores,
podría ser un buen sitio], ya que es la función que rellena los valores que hemos tomado de las fotos de la cuadrícula.
Cada vez que se quieran los centimetros de unos pixeles dados, llamar a pxToCm(int x, int y)
Devolverá un tipo coordenada, definido aqui también, que contiene dos enteros, la X y la Y en cm
NOTA: no están todos los valores de ejes añadidos, los ire añadiendo sobre la marcha, era mas importante tener
el modulo funcional primero, solo es añadir a mano mas valores tomados a las funciones "fill"
*/

/** Funciones de este fichero **
*
* Rellena el vector de ejes Y, con los valores tomados a mano de la cuadrícula
* 	void fillVectorY(vector<int> ejeY);
*
* Rellena un eje X a mano con los valores tomados de la cuadrícula, en función del eje Y que recibe por parámetro.
* Devuelve la Y en cm.
* 	int fillVectorX(int ejeY, vector<tElemento_x>& ejeX)
*
* Rellena el HashMap con claves Y, y valores, todos los puntos X asociados a ese eje Y
* 	void fillMap(HashMap<int, vector<int>> mapa_coordenadas, vector<int> ejeY);
*
* La función busca es la función principal de este módulo, recibe unos puntos en píxeles, y devuelve su equivalencia en centímetros
*	t_Punto pxToCm(int x_px, int y_px);
*
*/

#define INIT_X_PX 320 
#define INIT_Y_PX 480

//Tipo que se devuelve en la función "pxToCm", que devuelve x e y en centímetros.
typedef struct{
	int x;
	int y;
}t_Punto;

//Tipo usado en los vectores de X, para tener el valor tanto en píxeles como en centímetros.
typedef struct{
	int x_px;
	int x_cm;
}tElemento_x;

//Tipo usado en el "valor" del hash_map, que contiene la equivalencia de la Y en cm y el vector de X asociadas
typedef struct{
	vector<tElemento_x> ejeX_vector;
	int y_cm;
}tElemento_y;

//Declaración de funciones
t_Punto pxToCm(int x_px, int y_px);

int distancia(int x1, int y1, int x2, int y2);

void fillVectorY(vector<int>& ejeY);

int fillVectorX(int ejeY, vector<tElemento_x>& ejeX);

void fillMap(HashMap<int, tElemento_y> &mapa_coordenadas, vector<int>& ejeY_vector);

int busquedaBinariaY(vector<int>& ejeY, int y_px, int inicio, int fin);

int busquedaBinariaX(vector<tElemento_x> ejeX, int x_px, int inicio, int fin);

void iniciaNavegacion();
