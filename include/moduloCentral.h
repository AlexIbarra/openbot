#ifndef MODULOCENTRAL_H
#define MODULOCENTRAL_H

typedef enum t_GlobalSt {st_buscaPuto, st_visitaPunto}
typedef enum t_EstadoBusca {st_izq, st_der, st_trayizq, st_trayder, st_recto, st_encontrado, st_perdido};

#define NUM_CUADRANTES 6
#define INF 9999

typedef struct {
	t_Coordenada coordenada;
	int cuadrante;
	int distancia;	
} t_DatoVision;

int calculaEstado( int x, int y, int ultSt);
void ejecuta( int st);
int run();
void visitaPunto();
void buscaPuntoCercano(list<t_Coordenada> objetos, int cuadrante, t_DatoVision &punto);


#endif /* MODULOBROKER_H */

