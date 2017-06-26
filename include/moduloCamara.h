#ifndef MODULOCAMARA_H
#define MODULOCAMARA_H

class Camara {
private:
    int x;
    int y;
    int iLowH;
    int iHighH;
    int iLowS; 
    int iHighS;
    int iLowV;
    int iHighV;
        
public:
    Camara();
    Camara(int ilowh, int ihighh, int ilows, int isighs, int ilowv, int ihighv);
    int getX();
    int getY();
    //void *captura(void *thread_cola);
};

void *captura(void *thread_cola);

typedef struct {
	int pos_x;
	int pos_y;
} t_Coordenada;

typedef struct {
    t_Coordenada coordenadas;
    Queue cola;
} t_DatosCamara;

#endif /* MODULOCAMARA_H */

