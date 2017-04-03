#ifndef MODULOCAMARA_H
#define MODULOCAMARA_H

#include "Object.h"

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
void equalize();
void detectMultiObject(Object theObject, Mat threshold, Mat HSV, Mat &cameraFeed);

typedef struct {
	int pos_x;
	int pos_y;
} t_Coordenada;

#endif /* MODULOCAMARA_H */

