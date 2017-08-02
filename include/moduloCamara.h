#ifndef MODULOCAMARA_H
#define MODULOCAMARA_H

#include <list>
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480
#define MAX_NUM_OBJECTS 10
#define MIN_OBJECT_AREA 1000
#define MAX_OBJECT_AREA 1500000

typedef struct {
    int x;
    int y;
} t_Coordenada;

typedef struct {
    list<t_Coordenada> objects;
} t_List;

//int captura(list<t_Coordenada> &objects);
void *captura(void *objects);
void equalizeHistogram(Mat threshold, Mat &equalized);
//void trackObject(t_Coordenada &object);
void *trackObject(void * obj);
void detectMultiObject(Mat threshold, Mat &cameraFeed, list<t_Coordenada> &objects);
void excessOfColourThreshold(Mat cameraFeed, Mat &imgThresholded, vector<float> &values);
void thresholdOtsu(Mat threshold, Mat &otsu);
void applyOpening(Mat &threshold, int obj_radius);
void applyClosing(Mat &threshold, int obj_radius);


#endif /* MODULOCAMARA_H */

