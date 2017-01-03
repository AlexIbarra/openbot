/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ImageModule.hpp
 * Author: aleja
 *
 * Created on 2 de enero de 2017, 21:38
 */

#ifndef IMAGEMODULE_HPP
#define IMAGEMODULE_HPP

#include "Object.hpp"

using namespace cv;

int H_MIN = 0;
int H_MAX = 255;
int S_MIN = 0;
int S_MAX = 255;
int V_MIN = 0;
int V_MAX = 255;
//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//names that will appear at the top of each window
const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image";
const string windowName3 = "After Morphological Operations";
const string trackbarWindowName = "Trackbars";
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS=50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 20*20;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;

class ImageModule {
public:
    void createTrackbars();
    void on_trackbar( int, void* );
    void drawObject(vector<Object> theObjects,Mat &frame, Mat &temp, vector< vector<Point> > contours, vector<Vec4i> hierarchy);
    void drawObject(vector<Object> theObjects,Mat &frame);
    void morphOps(Mat &thresh);
    void trackFilteredObject(Mat threshold,Mat HSV, Mat &cameraFeed);
    void trackFilteredObject(Object theObject,Mat threshold,Mat HSV, Mat &cameraFeed);
    string intToString(int number);
        
};
#endif /* IMAGEMODULE_HPP */

