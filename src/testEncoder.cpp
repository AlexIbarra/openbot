#include <iostream>
#include <stdio.h>
#include <wiringPi.h>
#include "gpioAccess.h"

using namespace std;

#define	enc 17 //pin encoder GPOI22

//void initEncoders();

// Para compilar: g++ ../obj/gpioAccess.o -o testEncoder testEncoder.cpp -lwiringPi -I../include/

void initEncoders(){
    pinMode (enc, INPUT) ;
    pullUpDnControl(enc, PUD_UP);
}

int main(void) {

    int distancia;
//    initEncoders();
     // Set up gpi pointer for direct register access
    setup_io();    
    set_input_gpio(enc);
    
    while(1) {
//        while(digitalRead(enc) == 0) {
        while(read_gpio(enc) <= 0) {
            printf("0\n");
            delay(500);
        }
//        while(digitalRead(enc) == 1) {
        while(read_gpio(enc) > 0) {
            printf("1\n");
            delay(500);
        }
        delay(300);
        printf("tick\n");
    }
    
    return 0;
}