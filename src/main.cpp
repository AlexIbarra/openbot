#include <iostream>
#include "moduloMotor.h"
#include "moduloCentral.h"
#include "moduloNavegacion.h"

using namespace std;


int main( void ) {
	
    initMotores();
    iniciaNavegacion();

	run();
	//~ t_Coordenada obj;
	//~ while(true)
	//~ {
		//~ trackObject(obj);
		//~ cout << "x= " << obj.x << " y= " << obj.y << endl;
	//~ }

    return 0;
}

