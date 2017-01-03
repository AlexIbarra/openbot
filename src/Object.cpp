/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "../include/Object.hpp"

using namespace cv;

Object::Object() {
    //set values for default constructor
    setType("green");
    setColor(Scalar(0, 0, 255));

}

Object::Object(string const &color) {

    setType(color);

    switch (color) {

        case "blue":
            setHSVmin(Scalar(92, 0, 0));
            setHSVmax(Scalar(124, 256, 256));
            //BGR value for Blue:
            setColor(Scalar(255, 0, 0));
            break;
        case "red":
            setHSVmin(Scalar(0, 200, 0));
            setHSVmax(Scalar(19, 255, 255));
            //BGR value for Red:
            setColor(Scalar(0, 0, 255));
            break;
        case "green":
            setHSVmin(Scalar(34, 50, 50));
            setHSVmax(Scalar(80, 220, 200));
            //BGR value for Green:
            setColor(Scalar(0, 255, 0));
            break;
        case "yellow":
            setHSVmin(Scalar(20, 124, 123));
            setHSVmax(Scalar(30, 256, 256));
            //BGR value for Yellow:
            setColor(Scalar(0, 255, 255));
            break;
        default:
            break;
    }
}

Object::~Object(void) {}

int Object::getXPos() {

    return Object::_xPos;
}

void Object::setXPos(int const &x) {
    Object::_xPos = x;
}

int Object::getYPos() {
    return Object::_yPos;
}

void Object::setYPos(int const &y) {
    Object::_yPos = y;
}

Scalar Object::getHSVmin() {
    return Object::_HSVmin;
}

Scalar Object::getHSVmax() {
    return Object::_HSVmax;
}

void Object::setHSVmin(Scalar const &min) {
    Object::_HSVmin = min;
}

void Object::setHSVmax(Scalar const &max) {
    Object::_HSVmax = max;
}