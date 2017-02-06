#include "moduloMotor.h"

const int pwmMotorD = 13; //Pin 13 de la rasp
const int pwmMotorI = 18; //Pin 18 de la rasp
const int PWM_CLOCK = 96, PWM_RANGE = 4300;

void parar() {
    pwmWrite(pwmMotorD, 319);
    pwmWrite(pwmMotorI, 319);
}

/***** Calcular las cifras *****/
void retroceder(){
    pwmWrite(pwmMotorD, );
    pwmWrite(pwmMotorI, ); 
}
void avanza(){
    pwmWrite(pwmMotorD, );
    pwmWrite(pwmMotorI, ); 
}
void avanzaLento(){
    pwmWrite(pwmMotorD, );
    pwmWrite(pwmMotorI, ); 
}
void rotaIzq(){
    pwmWrite(pwmMotorD, );
    pwmWrite(pwmMotorI, ); 
}
void rotaDcha(){
    pwmWrite(pwmMotorD, );
    pwmWrite(pwmMotorI, ); 
}


int main( int argc, char** argv ){

    /********** Establecemos los parámetros iniciales, necesarios para el PWM ************/

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


    /*********** Para empezar, desarrollar aquí un ejemplo para mover las ruedas ***********/
    //Después, aquí se recibirán peticiones y habrá que atenderlas




    return 0;
}
