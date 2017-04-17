#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <cmath.h>
#include <wiringPi.h>
#include <mosquitto.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "moduloEncoder.h"

#define DEBUG 0

void initEncoders(){
	pinMode (enc_izq, INPUT) ;
	pinMode (enc_der, INPUT) ;
	pullUpDnControl(enc_izq, PUD_UP);
    pullUpDnControl(enc_der, PUD_UP);
}

void *anguloIzq(void *thread_data){
	t_Encoder *enc = (t_Encoder *)thread_data;
	int angulo = 0;
	enc->fin = 0;
	while(angulo < enc->angulo){
		while(digitalRead(enc_izq) == 0);
		while(digitalRead(enc_izq) == 1);
		angulo += anguloXpaso;
	}
	enc->fin = 1;
	
	pthread_exit(NULL);
}

void *anguloIzq(void *thread_data){
	t_Encoder *enc = (t_Encoder *)thread_data;
	int angulo = 0;
	enc->fin = 0;
	while(angulo < enc->angulo){
		while(digitalRead(enc_der) == 0);
		while(digitalRead(enc_der) == 1);
		angulo += anguloXpaso;
	}
	enc->fin = 1;
	
	pthread_exit(NULL);
}

void *cuentaIzqe(void *thread_data){
	t_Encoder *enc = (t_Encoder *)thread_data;
	while(1){
		enc->distancia = 0;
		while(enc->enable){
			while(digitalRead(enc_izq) == 0);
			while(digitalRead(enc_izq) == 1);
			enc->distancia += paso;
			enc->angulo += anguloXpaso;
		}
	}

	pthread_exit(NULL);
}

void *cuentaDer(void *thread_data){
	t_Encoder *enc = (t_Encoder *)thread_data;
	while(1){
		enc->distancia = 0;
		while(enc->enable){
			while(digitalRead(enc_der) == 0);
			while(digitalRead(enc_der) == 1);
			enc->distancia += paso;
		}
	}

	pthread_exit(NULL);
}


#endif

