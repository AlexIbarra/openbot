#ifndef MODULOENCODER_H
#define MODULOENCODER_H

#define	enc_izq 5454 //pin encoder izquierdo
#define	enc_der 5454 //pin encoder derecho
#define paso 5 //mm
#define anguloXpaso 10 //grados

typedef struct{
	int enable;
	int distancia;
	int angulo;
	int fin;
}t_Encoder;

void initEncoders();

void *anguloIzq(void *thread_data);

void *anguloDer(void *thread_data);

void *cuentaIzq(void *thread_data);

void *cuentaDer(void *thread_data);

#endif

