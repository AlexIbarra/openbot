#include <iostream>
#include <wiringPi.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

#define pwmMotorD 13
#define pwmMotorI 18
#define PWM_CLOCK 96
#define PWM_RANGE 43000

void initMotores();

void parar();

void retroceder();

void avanza();

void avanzaLento();

void rotaIzq();

void rotaDcha();