/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Main.cpp
 * Author: aleja
 *
 * Created on 2 de enero de 2017, 20:41
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "../include/ImageModule.hpp"
#include "../include/MotorModule.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
//using namespace cv;

const char* window_name = "Edge Map";

/*
 * 
 */
int main(int argc, char** argv) {
    
    Mat dst, detected_edges;
    Mat src, src_gray;
    int edgeThresh = 1;
    int lowThreshold;
    int const max_lowThreshold = 100;
    int ratio = 3;
    int kernel_size = 3;    

    //if we would like to calibrate our filter values, set to true.
    bool calibrationMode = true;

    //Matrix to store each frame of the webcam feed
    Mat cameraFeed;
    Mat threshold;
    Mat HSV;

    if (calibrationMode) {
        //create slider bars for HSV filtering
        createTrackbars();
    }
    //video capture object to acquire webcam feed
    VideoCapture capture;
    //open capture object at location zero (default location for webcam)
    capture.open(0);
    //set height and width of capture frame
    capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
    //start an infinite loop where webcam feed is copied to cameraFeed matrix
    //all of our operations will be performed within this loop
    waitKey(1000);
    while (1) {
        //store image to matrix
        capture.read(cameraFeed);

        src = cameraFeed;

        if (!src.data) {
            return -1;
        }

        //convert frame from BGR to HSV colorspace
        cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);

        if (calibrationMode == true) {

            //need to find the appropriate color range values
            // calibrationMode must be false

            //if in calibration mode, we track objects based on the HSV slider values.
            cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
            inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
            morphOps(threshold);
            imshow(windowName2, threshold);

            //the folowing for canny edge detec
            /// Create a matrix of the same type and size as src (for dst)
            dst.create(src.size(), src.type());
            /// Convert the image to grayscale
            cvtColor(src, src_gray, CV_BGR2GRAY);
            /// Create a window
            namedWindow(window_name, CV_WINDOW_AUTOSIZE);
            /// Create a Trackbar for user to enter threshold
            createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold);
            /// Show the image
            trackFilteredObject(threshold, HSV, cameraFeed);
        } else {
            //create some temp fruit objects so that
            //we can use their member functions/information
            Object blue("blue"), yellow("yellow"), red("red"), green("green");

            //first find blue objects
            cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
            inRange(HSV, blue.getHSVmin(), blue.getHSVmax(), threshold);
            morphOps(threshold);
            trackFilteredObject(blue, threshold, HSV, cameraFeed);
            //then yellows
            cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
            inRange(HSV, yellow.getHSVmin(), yellow.getHSVmax(), threshold);
            morphOps(threshold);
            trackFilteredObject(yellow, threshold, HSV, cameraFeed);
            //then reds
            cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
            inRange(HSV, red.getHSVmin(), red.getHSVmax(), threshold);
            morphOps(threshold);
            trackFilteredObject(red, threshold, HSV, cameraFeed);
            //then greens
            cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
            inRange(HSV, green.getHSVmin(), green.getHSVmax(), threshold);
            morphOps(threshold);
            trackFilteredObject(green, threshold, HSV, cameraFeed);

        }
        //show frames
        //imshow(windowName2,threshold);

        imshow(windowName, cameraFeed);
        //imshow(windowName1,HSV);

        //delay 30ms so that screen can refresh.
        //image will not appear without this waitKey() command
        waitKey(30);
    }
    return 0;
}

