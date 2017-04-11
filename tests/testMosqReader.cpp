#include <unistd.h>
#include <iostream>
#include "moduloBroker.h"

using namespace std;

int main( void ) { 

    Broker * brk = new Broker ("brk_rd", "127.0.0.1", 1883);

    return 0;
}