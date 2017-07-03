#ifndef MODULOCENTRAL_H
#define MODULOCENTRAL_H

#include "moduloEncoder.h"
#include "moduloCamara.h"

#define PI 3.14159265



typedef enum t_Direccion {arriba, abajo, izquierda, derecha, arribaDer, arribaIzq, abajoDer, abajoIzq};

typedef enum t_Estado {st_inicial, st_caminos, st_next, st_orienta, st_busca};

typedef enum t_EstadoBusca {st_izq, st_der, st_trayizq, st_trayder, st_recto, st_encontrado, st_perdido};

typedef struct {
    t_Coordenada coordenada;
    t_Direccion dir;
    int angulo; //angulo respecto al eje X
} t_PosicionActual;

bool operator<(t_Coordenada a, t_Coordenada b);

int obtenerAngulo(int x1, int y1, int x2, int y2, int x3, int y3);

int calculaEstado( int x, int y, int ultSt, int numObjetivos, int totalObjetivos);

int ejecuta( int st);

//~ int run( int x, int y, int ultSt, int ultX, int ultY, int numObjetivos, int & totalObjetivos);

void run(t_DatosCamara & datosCamara, t_Encoder & datosEncIzq, t_Encoder & datosEncDer);

#endif
