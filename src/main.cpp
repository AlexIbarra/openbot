#include <iostream>
#include <pthread.h>
#include "moduloMotor.h"
#include "moduloCentral.h"
#include "moduloNavegacion.h"
//#include "moduloCamara.h"

using namespace std;


int main( void ) {
	
    initMotores();
    iniciaNavegacion();

    run();
    //visitaPunto();

    //~ t_Coordenada obj;
    //~ while(true)
    //~ {
            //~ trackObject(obj);
            //~ cout << "x= " << obj.x << " y= " << obj.y << endl;
    //~ }

    return 0;
}

