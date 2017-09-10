#include <cmath>
#include <iostream>
#include <vector>
#include "HashMap.h"
#include "moduloNavegacion.h"

using namespace std;  

vector<int> ejeY;
HashMap<int, tElemento_y> mapa_coordenadas;

/* 
 * #########################################################################
 * ####  Declaracion de las funciones estaticas al modulo de navegacion ####
 * #########################################################################
 */


/*! 
 *  \brief Busca la distancia en el eje Y más aproximado a la coordenada dada
 *  \param ejeY Vector de distancias para el eje Y
 *  \param y_px Valor en pixeles en el eje Y de la posicion del objeto
 *  \param inicio Pivote inicial del rango de busqueda
 *  \param fin Pivote final del rango de busqueda
 *  \return Valor aproximado de distancia real
 * 
 *  Realiza una busqueda binaria en el vector de distancias para encontrar un valor
 *  que mas se aproxime a la posicion en pixeles dada. El vector se encuentra
 *  ordenado de mayor a menor.
 */
static int busquedaBinariaY(vector<int> &ejeY, int y_px, int inicio, int fin){

    // Termination condition: start index greater than end index
    if(inicio > fin) {
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
        return busquedaBinariaY(ejeY, y_px, middle, fin);
    }

    return busquedaBinariaY(ejeY, y_px, inicio, middle);
}

/*! 
 *  \brief Busca la distancia en el eje X más aproximado a la coordenada dada
 *  \param ejeX Vector de distancias para el eje X
 *  \param x_px Valor en pixeles en el eje X de la posicion del objeto
 *  \param inicio Pivote inicial del rango de busqueda
 *  \param fin Pivote final del rango de busqueda
 *  \return Valor aproximado de distancia real
 * 
 *  Realiza una busqueda binaria en el vector de distancias para encontrar un valor
 *  que mas se aproxime a la posicion en pixeles dada. El vector se encuentra
 *  ordenado de mayor a menor.
 */
static int busquedaBinariaX(vector<tElemento_x> ejeX, int x_px, int inicio, int fin){
    // Termination condition: start index greater than end index
    if(inicio > fin) {
        return -1;
    }

    //Caso base en el que queda una única posición, se devuelve ese valor
    if (inicio == fin) {
        return ejeX[inicio].x_cm;
    }

    //Cuando solo haya dos posiciones, coger la más parecida
    if(inicio + 1 == fin) {

    	//Si hay alguno igual se devuelve, si no el más cercano
    	if (ejeX[inicio].x_px == x_px)
            return ejeX[inicio].x_cm;
    	else if (ejeX[fin].x_px == x_px)
            return ejeX[fin].x_cm;
    	else {
            if (abs(ejeX[inicio].x_px - x_px) <= abs(ejeX[fin].x_px - x_px))
                return ejeX[inicio].x_cm;
            else 
                return ejeX[fin].x_cm;
    	}

    }
    // Find the middle element of the vector and use that for splitting
    // the array into two pieces.
    const int middle = inicio + ((fin - inicio) / 2);

    if(ejeX[middle].x_px == x_px) {
        return ejeX[middle].x_cm;
    }
    else if(ejeX[middle].x_px > x_px) {
        return busquedaBinariaX(ejeX, x_px, inicio, middle);
    }

    return busquedaBinariaX(ejeX, x_px, middle, fin);
}

/*! 
 *  \brief Rellena un eje Y a mano con los valores tomados de la cuadrícula
 *  \param ejeY Coordenadas del objeto a visitar
 * 
 *  Rellena un vector correspondiente al eje Y con valores tomados
 *  a nano de la una cuadricula medida.
 */
static void fillVectorY(vector<int>& ejeY){

    ejeY.push_back(472); //Eje Y a 20 cm del robot
    ejeY.push_back(397); //Eje Y a 25 cm del robot
    ejeY.push_back(339); //Eje Y a 30 cm del robot
    ejeY.push_back(297); //Eje Y a 35 cm del robot
    ejeY.push_back(262); //Eje Y a 40 cm del robot
    ejeY.push_back(237); //Eje Y a 45 cm del robot
    ejeY.push_back(213); //Eje Y a 50 cm del robot
    ejeY.push_back(196); //Eje Y a 55 cm del robot
    ejeY.push_back(180); //Eje Y a 60 cm del robot
    ejeY.push_back(166); //Eje Y a 65 cm del robot
    ejeY.push_back(155); //Eje Y a 70 cm del robot
    ejeY.push_back(143); //Eje Y a 75 cm del robot

    //A partir de aqui faltan las X, hay bastante error en la Y, pero se toma la del punto central para "trazar" la horizontal
    //Hay pocos pixeles entre ejes y el error aumenta, pero en el "mundo real" es aceptable el error
    /*
    ejeY.push_back(134); //Eje Y a 80 cm del robot
    ejeY.push_back(125); //Eje Y a 85 cm del robot
    ejeY.push_back(119); //Eje Y a 90 cm del robot
    ejeY.push_back(112); //Eje Y a 95 cm del robot
    ejeY.push_back(105); //Eje Y a 100 cm del robot
    ejeY.push_back(99); //Eje Y a 105 cm del robot
    */
}

/*! 
 *  \brief Rellena un eje X a mano con los valores tomados de la cuadrícula
 *  \param ejeY Coordenadas del objeto a visitar
 *  \param ejeX Ultimo estado en el que se encontraba el robot
 *  \return Retorna el valor de Y en centimetros
 * 
 *  Rellena un eje X a mano con los valores tomados de la cuadrícula, 
 *  en función del eje Y que recibe por parámetro.
 */
static int fillVectorX(int ejeY, vector<tElemento_x>& ejeX){

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
        //EJE Y a 50 cm del robot
        case 213:
            aux.x_px = 15;
            aux.x_cm = -25;
            ejeX.push_back(aux);

            aux.x_px = 75;
            aux.x_cm = -20;
            ejeX.push_back(aux);

            aux.x_px = 135;
            aux.x_cm = -15;
            ejeX.push_back(aux);

            aux.x_px = 196;
            aux.x_cm = -10;
            ejeX.push_back(aux);

            aux.x_px = 255;
            aux.x_cm = -5;
            ejeX.push_back(aux);

            aux.x_px = 315;
            aux.x_cm = 0;
            ejeX.push_back(aux);

            aux.x_px = 374;
            aux.x_cm = 5;
            ejeX.push_back(aux);

            aux.x_px = 434;
            aux.x_cm = 10;
            ejeX.push_back(aux);

            aux.x_px = 495;
            aux.x_cm = 15;
            ejeX.push_back(aux);

            aux.x_px = 554;
            aux.x_cm = 20;
            ejeX.push_back(aux);

            aux.x_px = 614;
            aux.x_cm = 25;
            ejeX.push_back(aux);

            salida_cm = 50;
        break;
        //EJE Y a 55 cm del robot
        case 196:
            aux.x_px = 38;
            aux.x_cm = -25;
            ejeX.push_back(aux);

            aux.x_px = 94;
            aux.x_cm = -20;
            ejeX.push_back(aux);

            aux.x_px = 150;
            aux.x_cm = -15;
            ejeX.push_back(aux);

            aux.x_px = 206;
            aux.x_cm = -10;
            ejeX.push_back(aux);

            aux.x_px = 260;
            aux.x_cm = -5;
            ejeX.push_back(aux);

            aux.x_px = 315;
            aux.x_cm = 0;
            ejeX.push_back(aux);

            aux.x_px = 369;
            aux.x_cm = 5;
            ejeX.push_back(aux);

            aux.x_px = 424;
            aux.x_cm = 10;
            ejeX.push_back(aux);

            aux.x_px = 480;
            aux.x_cm = 15;
            ejeX.push_back(aux);

            aux.x_px = 535;
            aux.x_cm = 20;
            ejeX.push_back(aux);

            aux.x_px = 590;
            aux.x_cm = 25;
            ejeX.push_back(aux);

            aux.x_px = 640;
            aux.x_cm = 30;
            ejeX.push_back(aux);

            salida_cm = 55;
        break;
        //EJE Y a 60 cm del robot
        case 180:
            aux.x_px = 10;
            aux.x_cm = -30;
            ejeX.push_back(aux);

            aux.x_px = 59;
            aux.x_cm = -25;
            ejeX.push_back(aux);

            aux.x_px = 112;
            aux.x_cm = -20;
            ejeX.push_back(aux);

            aux.x_px = 163;
            aux.x_cm = -15;
            ejeX.push_back(aux);

            aux.x_px = 214;
            aux.x_cm = -10;
            ejeX.push_back(aux);

            aux.x_px = 265;
            aux.x_cm = -5;
            ejeX.push_back(aux);

            aux.x_px = 315;
            aux.x_cm = 0;
            ejeX.push_back(aux);

            aux.x_px = 365;
            aux.x_cm = 5;
            ejeX.push_back(aux);

            aux.x_px = 416;
            aux.x_cm = 10;
            ejeX.push_back(aux);

            aux.x_px = 468;
            aux.x_cm = 15;
            ejeX.push_back(aux);

            aux.x_px = 518;
            aux.x_cm = 20;
            ejeX.push_back(aux);

            aux.x_px = 568;
            aux.x_cm = 25;
            ejeX.push_back(aux);

            aux.x_px = 619;
            aux.x_cm = 30;
            ejeX.push_back(aux);

            salida_cm = 60;
        break;
        //EJE Y a 65 cm del robot
        case 166:
            aux.x_px = 30;
            aux.x_cm = -30;
            ejeX.push_back(aux);

            aux.x_px = 77;
            aux.x_cm = -25;
            ejeX.push_back(aux);

            aux.x_px = 125;
            aux.x_cm = -20;
            ejeX.push_back(aux);

            aux.x_px = 173;
            aux.x_cm = -15;
            ejeX.push_back(aux);

            aux.x_px = 222;
            aux.x_cm = -10;
            ejeX.push_back(aux);

            aux.x_px = 269;
            aux.x_cm = -5;
            ejeX.push_back(aux);

            aux.x_px = 315;
            aux.x_cm = 0;
            ejeX.push_back(aux);

            aux.x_px = 362;
            aux.x_cm = 5;
            ejeX.push_back(aux);

            aux.x_px = 410;
            aux.x_cm = 10;
            ejeX.push_back(aux);

            aux.x_px = 458;
            aux.x_cm = 15;
            ejeX.push_back(aux);

            aux.x_px = 505;
            aux.x_cm = 20;
            ejeX.push_back(aux);

            aux.x_px = 551;
            aux.x_cm = 25;
            ejeX.push_back(aux);

            aux.x_px = 599;
            aux.x_cm = 30;
            ejeX.push_back(aux);

            salida_cm = 65;
        break;
        //EJE Y a 70 cm del robot
        case 155:
            aux.x_px = 4;
            aux.x_cm = -35;
            ejeX.push_back(aux);

            aux.x_px = 49;
            aux.x_cm = -30;
            ejeX.push_back(aux);

            aux.x_px = 93;
            aux.x_cm = -25;
            ejeX.push_back(aux);

            aux.x_px = 138;
            aux.x_cm = -20;
            ejeX.push_back(aux);

            aux.x_px = 183;
            aux.x_cm = -15;
            ejeX.push_back(aux);

            aux.x_px = 227;
            aux.x_cm = -10;
            ejeX.push_back(aux);

            aux.x_px = 272;
            aux.x_cm = -5;
            ejeX.push_back(aux);

            aux.x_px = 316;
            aux.x_cm = 0;
            ejeX.push_back(aux);

            aux.x_px = 359;
            aux.x_cm = 5;
            ejeX.push_back(aux);

            aux.x_px = 403;
            aux.x_cm = 10;
            ejeX.push_back(aux);

            aux.x_px = 448;
            aux.x_cm = 15;
            ejeX.push_back(aux);

            aux.x_px = 493;
            aux.x_cm = 20;
            ejeX.push_back(aux);

            aux.x_px = 538;
            aux.x_cm = 25;
            ejeX.push_back(aux);

            aux.x_px = 580;
            aux.x_cm = 30;
            ejeX.push_back(aux);

            aux.x_px = 624;
            aux.x_cm = 35;
            ejeX.push_back(aux);

            salida_cm = 70;
        break;
        //EJE Y a 75 cm del robot
        case 143:
            aux.x_px = 23;
            aux.x_cm = -35;
            ejeX.push_back(aux);

            aux.x_px = 66;
            aux.x_cm = -30;
            ejeX.push_back(aux);

            aux.x_px = 106;
            aux.x_cm = -25;
            ejeX.push_back(aux);

            aux.x_px = 149;
            aux.x_cm = -20;
            ejeX.push_back(aux);

            aux.x_px = 191;
            aux.x_cm = -15;
            ejeX.push_back(aux);

            aux.x_px = 233;
            aux.x_cm = -10;
            ejeX.push_back(aux);

            aux.x_px = 275;
            aux.x_cm = -5;
            ejeX.push_back(aux);

            aux.x_px = 316;
            aux.x_cm = 0;
            ejeX.push_back(aux);

            aux.x_px = 357;
            aux.x_cm = 5;
            ejeX.push_back(aux);

            aux.x_px = 398;
            aux.x_cm = 10;
            ejeX.push_back(aux);

            aux.x_px = 440;
            aux.x_cm = 15;
            ejeX.push_back(aux);

            aux.x_px = 481;
            aux.x_cm = 20;
            ejeX.push_back(aux);

            aux.x_px = 523;
            aux.x_cm = 25;
            ejeX.push_back(aux);

            aux.x_px = 563;
            aux.x_cm = 30;
            ejeX.push_back(aux);

            aux.x_px = 605;
            aux.x_cm = 35;
            ejeX.push_back(aux);

            salida_cm = 75;
        break;
    }//fin switch

    return salida_cm;
}

/*! 
 *  \brief Rellena el HashMap con claves Y, y valores, todos los puntos X asociados a ese eje Y
 *  \param mapa_coordenadas 
 *  \param ejeY_vector 
 * 
 *  Rellena una tabla cuyas claves corresponden con las distancias del vector
 *  del eje Y y los valores corresponden a todos los puntos del eje X asociados
 *  al punto Y.
 */
static void fillMap(HashMap<int, tElemento_y>& mapa_coordenadas, vector<int>& ejeY_vector){

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


/* 
 * ###########################################
 * ####  Funciones propias de la interfaz ####
 * ###########################################
 */

void iniciaNavegacion(){

    fillVectorY(ejeY);
    fillMap(mapa_coordenadas, ejeY);
}

t_Punto pxToCm(int x_px, int y_px){

    t_Punto salida;
    int y_px_ajustado;
    tElemento_y valores_aux;
    vector<tElemento_x> ejeX_aux;

    // Se ajusta el punto Y recibido, al más cercano que tengamos registrado.
    y_px_ajustado = busquedaBinariaY(ejeY, y_px, 0, ejeY.size()-1);

    if (!mapa_coordenadas.contains(y_px_ajustado))
        cout << "Error en la búsqueda binaria, no existe ese eje Y" << endl;

    valores_aux = mapa_coordenadas.at(y_px_ajustado);

    ejeX_aux = valores_aux.ejeX_vector;
    salida.y = valores_aux.y_cm;

    //Una vez tenemos la clave Y y su equivalencia en cm, hay que buscar la X más cercana en ese eje.
    salida.x = busquedaBinariaX(ejeX_aux, x_px, 0, ejeX_aux.size()-1);

    if(salida.x == -1) {
        cout << "Error en la busquedaBinariaX, no se ha encontrado una X valida" << endl;
    }

    return salida;
}

int distancia(int x1, int y1, int x2, int y2) {
    int dist = 0;
    int c1, c2;
    c1 = abs(x2 - x1);
    c2 = abs(y2 - y1);
    dist = sqrt(c1*c1 + c2*c2);
    
    return dist;	
}