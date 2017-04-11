#ifndef MODULODECODER_H
#define MODULODECODER_H

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

void initDecoders(){
	pinMode (dec_izq, INPUT) ;
	pinMode (dec_der, INPUT) ;
	pullUpDnControl(dec_izq, PUD_UP);
    pullUpDnControl(dec_der, PUD_UP);
}

void *cuentaIzqe(void *thread_data){
	t_Decoder *dec = (t_Decoder *)thread_data;
	while(1){
		dec->distancia = 0;
		while(dec->enable){
			while(digitalRead(dec_izq) == 0);
			while(digitalRead(dec_izq) == 1);
			dec->distancia += paso;
		}
	}

	pthread_exit(NULL);
}

void *cuentaDer(void *thread_data){
	t_Decoder *dec = (t_Decoder *)thread_data;
	while(1){
		dec->distancia = 0;
		while(dec->enable){
			while(digitalRead(dec_izq) == 0);
			while(digitalRead(dec_izq) == 1);
			dec->distancia += paso;
		}
	}

	pthread_exit(NULL);
}


#endif

