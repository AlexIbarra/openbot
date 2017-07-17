#include <wiringPi.h>
#include "moduloMotor.h"

/*
*
* NOTA: falta ajustar un poco más las cifras, sobretodo el parado a 319 y el resto actualizarlas en consecuencia.
*
*/

void initMotores() {
	wiringPiSetupGpio();
    // Primero se establece el modo --> void pinMode (int pin, int mode);
    pinMode(pwmMotorI, PWM_OUTPUT);
    pinMode(pwmMotorD, PWM_OUTPUT);

    //put PWM in mark-space mode, which will give you 
    //the traditional (and easily predictable) PWM
    pwmSetMode(PWM_MODE_MS);

    //Establecemos el rango
    pwmSetRange(PWM_RANGE);

    //Establecemos el divisor del reloj
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
    pwmWrite(pwmMotorI, 323); 
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

//El robot da una vuelta completa a la derecha en 30 segundos.
void vuelta(){
	pwmWrite(pwmMotorD, 322);
    pwmWrite(pwmMotorI, 323);	
}
//Hace un barrido de unos 60 grados aproximadamente.
//Si en 30 seg rota 360 grados, en 5 seg gira 60 grados
void giraFoto(){
	pwmWrite(pwmMotorD, 322);
    pwmWrite(pwmMotorI, 323);	
    sleep(5.1);
    parar();
}
//El robot da una vuelta más rápida a la derecha en 11 segundos.
void vueltaRapida(){
	pwmWrite(pwmMotorD, 324);
    pwmWrite(pwmMotorI, 325);	
}

