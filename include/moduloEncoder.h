#ifndef MODULODECODER_H
#define MODULODECODER_H

#define	dec_izq 5454
#define	dec_der 5454
#define paso 5 //mm

struct{
	int enable;
	int distancia;
}t_Decoder;

void initDecoders();

void *cuentaIzq(void *thread_data);

void *cuentaDer(void *thread_data);

#endif

