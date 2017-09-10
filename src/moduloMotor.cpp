#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include "moduloMotor.h"

using namespace std;

#define pwmMotorD 13
#define pwmMotorI 18
#define PWM_CLOCK 96
#define PWM_RANGE 4300

void initMotores() {
    /* Se inicializa la libreria wiringPi */
    wiringPiSetupGpio();
    
    /* 
     * Se establece el moodo de funcionamiento (de salida) para los pines del motor
     * izquierdo y derecho.
     */
    pinMode(pwmMotorI, PWM_OUTPUT);
    pinMode(pwmMotorD, PWM_OUTPUT);

    /* Se establece el modo de funcionamiento del PWM */
    pwmSetMode(PWM_MODE_MS);

    /* Se establece el rango en el registro del generador PWM */
    pwmSetRange(PWM_RANGE);

    /* Se establece el valor del divisor del reloj */
    pwmSetClock(PWM_CLOCK);
}

void parar() {
    pwmWrite(pwmMotorD, 320);
    pwmWrite(pwmMotorI, 319);
}

void retroceder(){
    pwmWrite(pwmMotorD, 327);
    pwmWrite(pwmMotorI, 312); 
}

void avanza(){
    pwmWrite(pwmMotorD, 316);
    pwmWrite(pwmMotorI, 324); 
}

void trayectoriaIzq(){
    pwmWrite(pwmMotorD, 317);
    pwmWrite(pwmMotorI, 321); 
}

void trayectoriaDer(){
    pwmWrite(pwmMotorD, 319);
    pwmWrite(pwmMotorI, 322); 
}

void avanzaLento(){
    pwmWrite(pwmMotorD, 318);
    pwmWrite(pwmMotorI, 322); 
}

void rotaIzq(){
    pwmWrite(pwmMotorD, 317);
    pwmWrite(pwmMotorI, 318); 
}

void rotaDcha(){
    pwmWrite(pwmMotorD, 322);
    pwmWrite(pwmMotorI, 322);
}

void vuelta(){
    pwmWrite(pwmMotorD, 322);
    pwmWrite(pwmMotorI, 323);	
}

void giraFoto(){
    pwmWrite(pwmMotorD, 322);
    pwmWrite(pwmMotorI, 323);	
    sleep(5);
    parar();
}

void vueltaRapida(){
    pwmWrite(pwmMotorD, 324);
    pwmWrite(pwmMotorI, 325);	
}

