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
    void initCamara();
    int getX();
    int getY();
    void captura();
};

#endif /* MODULOCAMARA_H */

