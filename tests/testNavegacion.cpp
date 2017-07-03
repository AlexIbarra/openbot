#include <iostream>
#include <stdio.h>
#include "moduloNavegacion.h"
#include "HashMap.h"

using namespace std;


int main() {

	cout << "****** TEST NAVEGACIÓN OPEN BOT ******" << endl;

	iniciaNavegacion();

	tCoordenada salida = buscaCoordenadas(60, 472);
	cout << "La salida esperada para las coordenadas <60, 472> es <-10, 20> " << endl;
	cout << "La salida real para las coordenadas <60, 472> es: <" << salida.x << ", " << salida.y << "> " << endl;
	cout << endl;

	salida = buscaCoordenadas(232, 297);
	cout << "La salida esperada para las coordenadas <232, 297> es <-5, 35> " << endl;
	cout << "La salida real para las coordenadas <232, 297> es: <" << salida.x << ", " << salida.y << "> " << endl;
	cout << endl;

	salida = buscaCoordenadas(577, 237);
	cout << "La salida esperada para las coordenadas <577, 237> es <20, 45> " << endl;
	cout << "La salida real para las coordenadas <577, 237> es: <" << salida.x << ", " << salida.y << "> " << endl;
	cout << endl;

	cout << "/***************************************/" << endl;
	cout << "Pruebas con valores NO exactos " << endl;

	salida = buscaCoordenadas(313, 280);
	cout << "La salida esperada para las coordenadas <313, 280> es <0, 35> " << endl;
	cout << "La salida real para las coordenadas <313, 280> es: <" << salida.x << ", " << salida.y << "> " << endl;
	cout << endl;

	salida = buscaCoordenadas(460, 420);
	cout << "La salida esperada para las coordenadas <460, 420> es <5, 25> " << endl;
	cout << "La salida real para las coordenadas <460, 420> es: <" << salida.x << ", " << salida.y << "> " << endl;
	cout << endl;

	salida = buscaCoordenadas(20, 220);
	cout << "La salida esperada para las coordenadas <20, 220> es <-20, 45> " << endl;
	cout << "La salida real para las coordenadas <20, 220> es: <" << salida.x << ", " << salida.y << "> " << endl;
	cout << endl;

	system("PAUSE");

	return 0;
}
