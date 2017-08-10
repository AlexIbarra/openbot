#include <iostream>
#include <pthread.h>
#include "moduloMotor.h"
#include "moduloCentral.h"
#include "moduloNavegacion.h"
#include "moduloCamara.h"

using namespace std;
using namespace cv;


int main( void ) {
	pthread_t th1 = 1;
    initMotores();
    iniciaNavegacion();

    run();
    //visitaPunto();

	
    //~ t_Coordenada obj;
    //~ t_List lista;
    //~ pthread_create(&th1, NULL, &captura, (void *)&lista);
    //~ while(true)
    //~ {
            //~ tackObject(obj);
            //~ cout << "x= " << obj.x << " y= " << obj.y << endl;
            //~ cout << "Objetos: " << lista.objects.size() << endl;
    //~ }

    return 0;
}

