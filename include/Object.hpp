/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Object.hpp
 * Author: aleja
 *
 * Created on 2 de enero de 2017, 20:02
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

class Object {
public:
    
    Object();
    Object(string const &color) : _color(color) {};
    ~Object(void);    

    int getXPos();
    void setXPos(int const &x);

    int getYPos();
    void setYPos(int const &y);

    Scalar getHSVmin();
    Scalar getHSVmax();

    void setHSVmin(Scalar const &hsv_min);
    void setHSVmax(Scalar const &hsv_max);

    inline string getType(){ return _color; }
    inline void setType(string const &color){ _color = color; }

    inline Scalar getColor(){ return _BGRColor; }
    inline void setColor(Scalar const &c){ _BGRColor = c; }

private:

    int _xPos, _yPos;
    string _color;
    Scalar _HSVmin, _HSVmax;
    Scalar _BGRColor;
};

#endif /* OBJECT_HPP */

