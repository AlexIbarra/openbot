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
    pwmWrite(pwmMotorD, 300);
    pwmWrite(pwmMotorI, 328); 
}
void avanzaLento(){
    pwmWrite(pwmMotorD, 313);
    pwmWrite(pwmMotorI, 326); 
}
void rotaIzq(){
    pwmWrite(pwmMotorD, 310);
    pwmWrite(pwmMotorI, 310); 
}
void rotaDcha(){
    pwmWrite(pwmMotorD, 328);
    pwmWrite(pwmMotorI, 328);
   
}
