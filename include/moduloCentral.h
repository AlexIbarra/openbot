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

int calculaEstado( int x, int y, int ultSt);

void ejecuta( int st);

int run( int x, int y, int ultSt, int ultX, int ultY);


#endif /* MODULOBROKER_H */

