#include <iostream>
#include "moduloMotor.h"
#include "moduloCentral.h"
#include "moduloNavegacion.h"

using namespace std;


int main( void ) {
    
    /*
     *  Llamada a las funciones inicializadoras de 
     * los modulos de motores y navegacion 
     */
    initMotores();
    iniciaNavegacion();

    /* Llamada a la funcion principal del robot */
    run();
    
    return 0;
}

