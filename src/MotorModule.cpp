/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <wiringPi.h>
#include "../include/rpiPWM1.h"
#include "../include/MotorModule.hpp"

using namespace std;

void giraMDDelante() {
    pwmWrite(MotorModule::getPwmPinD(), 310);
}

void giraMDAtras() {
    pwmWrite(MotorModule::getPwmPinD(), 510);
}

void giraMIDelante() {
    pwmWrite(MotorModule::getPwmPinI(), 510);
}

void giraMIAtras() {
    pwmWrite(MotorModule::getPwmPinI(), 310);
}

void pararMD() {
    pwmWrite(MotorModule::getPwmPinD(), 450);
}

void giraMI() {
    pwmWrite(MotorModule::getPwmPinI(), 450);
}