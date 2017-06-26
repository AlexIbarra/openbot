#include <unistd.h>
#include <iostream>
#include <queue>
#include <pthread.h>
#include "moduloMotor.h"
#include "moduloCamara.h"
#include "moduloCentral.h"
#include "moduloBroker.h"
#include "moduloEncoder.h"

using namespace std;

/*int main( void ) {
    
    int iLowH = 170;
    int iHighH = 179;

    int iLowS = 80; //50 si hay mucha luz de sol
    int iHighS = 255;

    int iLowV = 60;
    int iHighV = 255;
    
    bool encontrado = false;
    
    Camara * cam = new Camara(iLowH, iHighH, iLowS, iHighS, iLowV, iHighV);
    initMotores();
    initEncoders();

    int x, y, ultX=-1, ultY=-1, rc, moviAnte = -1, estado = st_inicial, encI, encD;
    
    int numObjetivos = 0, totalObjetivos = 0;

    pthread_t thread1 = 1, thread2, thread3;
    //queue<t_Coordenada> cola;
    t_Coordenada coordenada;
    t_Encoder datosEncIzq, datosEncDer;

    datosEncDer.enable = datosEncIzq.enable = 0;
    
    try {
        
        // Broker * brk = new Broker ("broker", "brk_1", "127.0.0.1", 1883);

        rc = pthread_create(&thread1, NULL, captura, (void *)&coordenada);

        encI = pthread_create(&thread2, NULL, cuentaIzq, (void *)&datosEncIzq);

        encD = pthread_create(&thread3, NULL, cuentaDer, (void *)&datosEncDer);
       	
       	while(coordenada.pos_x == -1 && coordenada.pos_x == -1) {sleep(1);}
       	        
        while(1) {
			
            x = coordenada.pos_x;
            y = coordenada.pos_y;
            
            if(coordenada.pos_x == -1 && coordenada.pos_x == -1) {sleep(1);}
            
            if(estado == st_inicial){
                estado = busca(x, y, totalObjetivos);
            }else{
                estado = run(x, y, estado, ultX, ultY);
            
                if (estado != st_perdido){
    				ultX = x;
    				ultY = y;
    			}

                if(estado == st_encontrado){                
                    numObjetivos++;   
                }else if(estado == st_inicial && numObjetivos == totalObjetivos){
                    numObjetivos = totalObjetivos = 0;
                }
            }
        }

    } catch (const exception& e){					/// if exception occured in constructor. see class declaration.
        cerr << "Error on Network Connection.\n" \
            << "Check mosquitto is running & IP/PORT\n";
    }
    

    return 0;
}*/

int main( void ) {
    
    int iLowH = 170;
    int iHighH = 179;

    int iLowS = 80; //50 si hay mucha luz de sol
    int iHighS = 255;

    int iLowV = 60;
    int iHighV = 255;
    
    int encI, encD;
    pthread_t thread1 = 1, thread2, thread3;
    t_DatosCamara datosCamara;
    
    t_Encoder datosEncIzq, datosEncDer;
    Camara * cam = new Camara(iLowH, iHighH, iLowS, iHighS, iLowV, iHighV);
    
    initMotores();
    initEncoders();

    datosEncDer.enable = datosEncIzq.enable = 0;
    
    try {

        rc = pthread_create(&thread1, NULL, captura, (void *)&datosCamara);

        encI = pthread_create(&thread2, NULL, cuentaIzq, (void *)&datosEncIzq);

        encD = pthread_create(&thread3, NULL, cuentaDer, (void *)&datosEncDer);

        while(1){
            run(&datosCamara, &datosEncIzq, &datosEncDer);
        }

    } catch (const exception& e){
        cerr << "Fatal error ocurred" << endl;
    }

    return 0;
}
