#include "Object.h"

Object::Object()
{
    //set values for default constructor
    setType("Object");
    setColor(Scalar(0,0,0));
}

Object::Object(string name){

    setType(name);

    if(name=="blue") {

        setHSVmin(Scalar(92,0,0));
        setHSVmax(Scalar(124,256,256));

        //BGR value for Blue:
        setColor(Scalar(255,0,0));
    }
    if(name=="green") {

        setHSVmin(Scalar(34,50,50));
        setHSVmax(Scalar(80,220,200));

        //BGR value for Green:
        setColor(Scalar(0,255,0));
    }
    if(name=="yellow") {

        setHSVmin(Scalar(20,124,123));
        setHSVmax(Scalar(30,256,256));

        //BGR value for Yellow:
        setColor(Scalar(0,255,255));
    }
    if(name=="red") {
        
        int iLowH = 170;
        int iHighH = 179;
        int iLowS = 80; //50 si hay mucha luz de sol
        int iHighS = 255;
        int iLowV = 60;
        int iHighV = 255;

        setHSVmin(Scalar(iLowH, iLowS, iLowV));
        setHSVmax(Scalar(iHighH, iHighS, iHighV));
        
//        setHSVmin(Scalar(0,200,0));
//        setHSVmax(Scalar(19,255,255));

        //BGR value for Red:
        setColor(Scalar(0,0,255));
    }
}

Object::~Object(void)
{
}

int Object::getXPos(){
    return Object::xPos;
}

void Object::setXPos(int x){
    Object::xPos = x;
}

int Object::getYPos(){
    return Object::yPos;
}

void Object::setYPos(int y){
    Object::yPos = y;
}

Scalar Object::getHSVmin(){
    return Object::HSVmin;
}
Scalar Object::getHSVmax(){
    return Object::HSVmax;
}

void Object::setHSVmin(Scalar min){
    Object::HSVmin = min;
}

void Object::setHSVmax(Scalar max){
    Object::HSVmax = max;
}
