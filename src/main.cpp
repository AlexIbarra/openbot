#include <iostream>
#include "moduloMotor.h"
#include "moduloCentral.h"
#include "moduloNavegacion.h"

using namespace std;


int main( void ) {
	
    initMotores();
    iniciaNavegacion();

	run();

    return 0;
}

