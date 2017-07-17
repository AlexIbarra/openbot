#ifndef MODULOCAMARA_H
#define MODULOCAMARA_H

#include "Object.h"
#include <list>
#include <queue>

#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480
#define MAX_NUM_OBJECTS 10
#define MIN_OBJECT_AREA (20*20)
const double MAX_OBJECT_AREA ((FRAME_HEIGHT*FRAME_WIDTH)/2.5);

typedef struct {
		int x;
		int y;
} t_Coordenada;

int captura(list<Object> &objects);
void equalizeHistogram(Mat threshold, Mat &equalized);
int trackObject(t_Coordenada &object)
void detectMultiObject(Object theObject, Mat threshold, Mat &cameraFeed, list<Object> &objects);
void excessOfColourThreshold(Mat cameraFeed, Mat &imgThresholded, const vector<int> &values);
void thresholdOtsu(Mat threshold, Mat &otsu);
void applyOpening(Mat &threshold, int obj_radius = 2);
void applyClosing(Mat &threshold, int obj_radius = 2);


#endif /* MODULOCAMARA_H */

