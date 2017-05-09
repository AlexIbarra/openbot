#ifndef MODULOCAMARA_H
#define MODULOCAMARA_H

#include "Object.h"
#include <list>


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
    //VeideoCapture capture(0);
        
public:
    Camara();
    Camara(int ilowh, int ihighh, int ilows, int isighs, int ilowv, int ihighv);
    int getX();
    int getY();
    //void *captura(void *thread_cola);
};

#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480
#define MAX_NUM_OBJECTS 10
#define MIN_OBJECT_AREA (20*20)
const double MAX_OBJECT_AREA ((FRAME_HEIGHT*FRAME_WIDTH)/2.5);

typedef struct {
	int pos_x;
	int pos_y;
	list<Object> lista;
} t_Coordenada;

typedef struct {
	Rect rectangle;
	Point initialClickPoint;
	Point currentMousePoint;
	bool rectangleSelected;
	bool mouseMove;
} t_Rectangle;

void *captura(void *thread_cola);
void equalizeHistogram(Mat threshold, Mat &equalized);
void recordObjectColor(t_Rectangle * rectData, Object &object, Mat cameraFeed, Mat hsvFrame);
void trackObject(Object &object, Mat threshold, Mat &cameraFeed);
void detectMultiObject(Object theObject, Mat threshold, Mat &cameraFeed, list<Object> &objects);
void excessOfColourThreshold(Mat cameraFeed, Mat &imgThresholded, const vector<int> &values);
void thresholdOtsu(Mat threshold, Mat &otsu);
void applyOpening(Mat &threshold, int obj_radius = 2);
void applyClosing(Mat &threshold, int obj_radius = 2);
void onMouse(int event, int x, int y, int flags, void * params);

#endif /* MODULOCAMARA_H */

