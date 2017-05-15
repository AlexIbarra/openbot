#include <cmath>
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

Cada vez que se quieran los centimetros de unos pixeles dados, llamar a buscaCoordenadas(int x, int y)
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
*	tCoordenada buscaCoordenadas(int x_px, int y_px);
*
*/

//Tipo que se devuelve en la función "buscaCoordenadas", que devuelve x e y en centímetros.
typedef struct{
	int x;
	int y;
}tCoordenada;

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

vector<int> ejeY;
HashMap<int, tElemento_y> mapa_coordenadas;

//Declaración de funciones
void fillVectorY(vector<int>& ejeY);
int fillVectorX(int ejeY, vector<tElemento_x>& ejeX);
void fillMap(HashMap<int, tElemento_y> &mapa_coordenadas, vector<int>& ejeY_vector);
int busquedaBinariaY(vector<int>& ejeY, int y_px, int inicio, int fin);
int busquedaBinariaX(vector<tElemento_x> ejeX, int x_px, int inicio, int fin);


void iniciaNavegacion(){

	/**** OJO!! ***/
	//Vector y hashMap se pasan por valor o referencia para que se modofiquen???
	//Parece que por referencia, si no no se modifican, aunque no me fio al 100%

	fillVectorY(ejeY);
	fillMap(mapa_coordenadas, ejeY);

}

tCoordenada buscaCoordenadas(int x_px, int y_px){

	tCoordenada salida;
	int y_px_ajustado;
	tElemento_y valores_aux;
	vector<tElemento_x> ejeX_aux;

	// Se ajusta el punto Y recibido, al más cercano que tengamos registrado.
	y_px_ajustado = busquedaBinariaY(ejeY, y_px, 0, ejeY.size()-1);

	/*TEST*/
	cout << "y_px_ajustado " << y_px_ajustado << endl;

	if (!mapa_coordenadas.contains(y_px_ajustado))
		cout << "Error en la búsqueda binaria, no existe ese eje Y" << endl;

	valores_aux = mapa_coordenadas.at(y_px_ajustado);

	ejeX_aux = valores_aux.ejeX_vector;
	salida.y = valores_aux.y_cm;

	//Una vez tenemos la clave Y y su equivalencia en cm, hay que buscar la X más cercana en ese eje.
	salida.x = busquedaBinariaX(ejeX_aux, x_px, 0, ejeX_aux.size()-1);

	if(salida.x == -1){
		cout << "Error en la busquedaBinariaX, no se ha encontrado una X valida" << endl;
	}

	return salida;
}

//Busca el valor de los ejes Y más aproximado al dado en píxeles. **VECTOR ORDENADO DE MAYOR A MENOR
int busquedaBinariaY(vector<int>& ejeY, int y_px, int inicio, int fin){

    // Termination condition: start index greater than end index
    if(inicio > fin)
    {
        return -1;
    }

	//Caso base en el que queda una única posición, se devuelve ese valor
	if (inicio == fin) {
		return ejeY[inicio];
	}

    //Cuando solo haya dos posiciones, coger la más parecida
    if(inicio + 1 == fin){

    	//Si hay alguno igual se devuelve, si no el más cercano
    	if (ejeY[inicio] == y_px)
    		return ejeY[inicio];
    	else if (ejeY[fin] == y_px)
    		return ejeY[fin];

    	else{

    		if (abs(ejeY[inicio] - y_px) <= abs(ejeY[fin] - y_px))
    			return ejeY[inicio];

    		else 
    			return ejeY[fin];
    	}

    }

    // Find the middle element of the vector and use that for splitting
    // the array into two pieces.
    const int middle = inicio + ((fin - inicio) / 2);

    if(ejeY[middle] == y_px)
    {
        return ejeY[middle];
    }

    else if(ejeY[middle] > y_px)
    {
        return busquedaBinariaY(ejeY, y_px, middle + 1, fin);
    }

    return busquedaBinariaY(ejeY, y_px, inicio, middle - 1);

} //fin busquedaBinariaY


//Dado un X en píxeles, lo busca en el array y devuelve los cm de esa misma posición del array.
int busquedaBinariaX(vector<tElemento_x> ejeX, int x_px, int inicio, int fin){

// Termination condition: start index greater than end index
    if(inicio > fin)
    {
        return -1;
    }

	//Caso base en el que queda una única posición, se devuelve ese valor
	if (inicio == fin) {
		return ejeX[inicio].x_cm;
	}

    //Cuando solo haya dos posiciones, coger la más parecida
    if(inicio + 1 == fin){

    	//Si hay alguno igual se devuelve, si no el más cercano
    	if (ejeX[inicio].x_px == x_px)
    		return ejeX[inicio].x_cm;
    	else if (ejeX[fin].x_px == x_px)
    		return ejeX[fin].x_cm;

    	else{

    		if (abs(ejeX[inicio].x_px - x_px) <= abs(ejeX[fin].x_px - x_px))
    			return ejeX[inicio].x_cm;

    		else 
    			return ejeX[fin].x_cm;
    	}

    }
    // Find the middle element of the vector and use that for splitting
    // the array into two pieces.
    const int middle = inicio + ((fin - inicio) / 2);

    if(ejeX[middle].x_px == x_px)
    {
        return ejeX[middle].x_cm;
    }

    else if(ejeX[middle].x_px > x_px)
    {
        return busquedaBinariaX(ejeX, x_px, inicio, middle - 1);
    }

    return busquedaBinariaX(ejeX, x_px, middle + 1, fin);

} // fin busquedaBinariaX

void fillVectorY(vector<int>& ejeY){

	ejeY.push_back(472); //Eje Y a 20 cm del robot
	ejeY.push_back(397); //Eje Y a 25 cm del robot
	ejeY.push_back(339); //Eje Y a 30 cm del robot
	ejeY.push_back(297); //Eje Y a 35 cm del robot
	ejeY.push_back(262); //Eje Y a 40 cm del robot
	ejeY.push_back(237); //Eje Y a 45 cm del robot
	//ejeY.push_back(213); //Eje Y a 50 cm del robot
	//ejeY.push_back(196); //Eje Y a 55 cm del robot
	//ejeY.push_back(180); //Eje Y a 60 cm del robot

	//A partir de aqui faltan las X, hay bastante error en la Y, pero se toma la del punto central para "trazar" la horizontal
	//Hay pocos pixeles entre ejes y el error aumenta, pero en el "mundo real" es aceptable el error
	/*ejeY.push_back(166); //Eje Y a 65 cm del robot
	ejeY.push_back(155); //Eje Y a 70 cm del robot
	ejeY.push_back(143); //Eje Y a 75 cm del robot
	ejeY.push_back(134); //Eje Y a 80 cm del robot
	ejeY.push_back(125); //Eje Y a 85 cm del robot
	ejeY.push_back(119); //Eje Y a 90 cm del robot
	ejeY.push_back(112); //Eje Y a 95 cm del robot
	ejeY.push_back(105); //Eje Y a 100 cm del robot
	ejeY.push_back(99); //Eje Y a 105 cm del robot*/
}


void fillMap(HashMap<int, tElemento_y>& mapa_coordenadas, vector<int>& ejeY_vector){

	//Iterador constante con el cual vamos rellenando el hasp_map con las Y
	vector<int>::iterator it = ejeY_vector.begin();
	//Vector auxiliar de X para hacer los insert.
	vector<tElemento_x> ejeX_aux;

	tElemento_y valores_aux;
	int ejeY_actual;

	//Recorrido del vector de Y, rellenando los X asociados a cada eje Y.
	while (it != ejeY_vector.end()){
		
		//Coger el valor actual del eje Y, para rellenar las respectivas X
		ejeY_actual = *it;

		//Rellenar el eje X actual e insertar los datos en el map
		valores_aux.y_cm = fillVectorX(ejeY_actual, ejeX_aux);
		valores_aux.ejeX_vector = ejeX_aux;

		mapa_coordenadas.insert(ejeY_actual, valores_aux);

		//Vaciar el vector auxiliar para las siguientes iteraciones
		 ejeX_aux.clear();

		it++;
	}
}

//Posibilidad de hacerlo leyendo de un fichero???
//El código cambiaría poco pero los valores podrían cambiarse fácilmente
int fillVectorX(int ejeY, vector<tElemento_x>& ejeX){

	int salida_cm = 0;
	tElemento_x aux;

	switch(ejeY){

		//EJE Y a 20 cm del robot
		case 472:
			aux.x_px = 60;
			aux.x_cm = -10;
			ejeX.push_back(aux);

			aux.x_px = 184;
			aux.x_cm = -5;
			ejeX.push_back(aux);

			aux.x_px = 311;
			aux.x_cm = 0;
			ejeX.push_back(aux);

			aux.x_px = 437;
			aux.x_cm = 5;
			ejeX.push_back(aux);

			aux.x_px = 561;
			aux.x_cm = 10;
			ejeX.push_back(aux);
		
			salida_cm = 20;
		break;

		//EJE Y a 25 cm del robot
		case 397:
			aux.x_px = 99;
			aux.x_cm = -10;
			ejeX.push_back(aux);

			aux.x_px = 204;
			aux.x_cm = -5;
			ejeX.push_back(aux);

			aux.x_px = 311;
			aux.x_cm = 0;
			ejeX.push_back(aux);

			aux.x_px = 419;
			aux.x_cm = 5;
			ejeX.push_back(aux);

			aux.x_px = 524;
			aux.x_cm = 10;
			ejeX.push_back(aux);

			aux.x_px = 629;
			aux.x_cm = 15;
			ejeX.push_back(aux);

			salida_cm = 25;
		break;

		//EJE Y a 30 cm del robot
		case 339:
			aux.x_px = 35;
			aux.x_cm = -15;
			ejeX.push_back(aux);

			aux.x_px = 128;
			aux.x_cm = -10;
			ejeX.push_back(aux);

			aux.x_px = 219;
			aux.x_cm = -5;
			ejeX.push_back(aux);

			aux.x_px = 312;
			aux.x_cm = 0;
			ejeX.push_back(aux);

			aux.x_px = 405;
			aux.x_cm = 5;
			ejeX.push_back(aux);

			aux.x_px = 497;
			aux.x_cm = 10;
			ejeX.push_back(aux);

			aux.x_px = 589;
			aux.x_cm = 15;
			ejeX.push_back(aux);

			salida_cm = 30;
		break;

		//EJE Y a 35 cm del robot
		case 297:
			aux.x_px = 68;
			aux.x_cm = -15;
			ejeX.push_back(aux);

			aux.x_px = 153;
			aux.x_cm = -10;
			ejeX.push_back(aux);

			aux.x_px = 232;
			aux.x_cm = -5;
			ejeX.push_back(aux);

			aux.x_px = 313;
			aux.x_cm = 0;
			ejeX.push_back(aux);

			aux.x_px = 395;
			aux.x_cm = 5;
			ejeX.push_back(aux);

			aux.x_px = 476;
			aux.x_cm = 10;
			ejeX.push_back(aux);

			aux.x_px = 558;
			aux.x_cm = 15;
			ejeX.push_back(aux);

			aux.x_px = 637;
			aux.x_cm = 20;
			ejeX.push_back(aux);

			salida_cm = 35;
		break;

		//EJE Y a 40 cm del robot
		case 262:
			aux.x_px = 22;
			aux.x_cm = -20;
			ejeX.push_back(aux);

			aux.x_px = 96;
			aux.x_cm = -15;
			ejeX.push_back(aux);

			aux.x_px = 170;
			aux.x_cm = -10;
			ejeX.push_back(aux);

			aux.x_px = 242;
			aux.x_cm = -5;
			ejeX.push_back(aux);

			aux.x_px = 313;
			aux.x_cm = 0;
			ejeX.push_back(aux);

			aux.x_px = 386;
			aux.x_cm = 5;
			ejeX.push_back(aux);

			aux.x_px = 459;
			aux.x_cm = 10;
			ejeX.push_back(aux);

			aux.x_px = 533;
			aux.x_cm = 15;
			ejeX.push_back(aux);

			aux.x_px = 605;
			aux.x_cm = 20;
			ejeX.push_back(aux);

			salida_cm = 40;
		break;

		//EJE Y a 45 cm del robot
		case 237:
			aux.x_px = 50;
			aux.x_cm = -20;
			ejeX.push_back(aux);

			aux.x_px = 117;
			aux.x_cm = -15;
			ejeX.push_back(aux);

			aux.x_px = 184;
			aux.x_cm = -10;
			ejeX.push_back(aux);

			aux.x_px = 250;
			aux.x_cm = -5;
			ejeX.push_back(aux);

			aux.x_px = 315;
			aux.x_cm = 0;
			ejeX.push_back(aux);

			aux.x_px = 380;
			aux.x_cm = 5;
			ejeX.push_back(aux);

			aux.x_px = 445;
			aux.x_cm = 10;
			ejeX.push_back(aux);

			aux.x_px = 512;
			aux.x_cm = 15;
			ejeX.push_back(aux);

			aux.x_px = 577;
			aux.x_cm = 20;
			ejeX.push_back(aux);

			aux.x_px = 538;
			aux.x_cm = 25;
			ejeX.push_back(aux);

			salida_cm = 45;
		break;

	}//fin switch

	return salida_cm;
}// fillVectorX