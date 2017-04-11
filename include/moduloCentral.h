#ifndef MODULOCENTRAL_H
#define MODULOCENTRAL_H

#define st_inicial 0
#define st_izq 1
#define st_der 2
#define st_trayizq 3
#define st_trayder 4
#define st_recto 5
#define st_encontrado 6
#define st_perdido 7
#define st_localiza 8

int obtenerAngulo(int x1, int y1, int x2, int y2, int x3, int y3);

int calculaEstado( int x, int y, int ultSt, int numObjetivos, int totalObjetivos);

int ejecuta( int st);

int run( int x, int y, int ultSt, int ultX, int ultY, int numObjetivos, int & totalObjetivos);

#endif

