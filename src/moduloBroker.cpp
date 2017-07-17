#include <iostream>
#include <cstring>
#include <stdexcept>
#include "moduloBroker.h"
#include <mosquitto.h>

using namespace std;

Broker::Broker(const char * _id, const char * _host, int _port)
{
    this->id = _id;
    this->port= _port;
    this->host = _host;
 
    mosquitto_lib_init(); // Initialize libmosquitto
    
    this->mosq = mosquitto_new (_id, true, NULL);
    if (!mosq) {
        throw runtime_error("##Cant initialize Mosquitto library##");
    }
 
    if ( mosquitto_connect (this->mosq, _host, _port, 0) != MOSQ_ERR_SUCCESS) { // Connect to MQTT Broker
            throw runtime_error("##Cant connect to Mosquitto server##");
    }    
  
    mosquitto_loop_start(this->mosq);   // Start thread managing connection / publish / subscribe
};

Broker::~Broker() {
    mosquitto_loop_stop(this->mosq, true); // Kill the thread
    mosquitto_destroy (this->mosq);
    mosquitto_lib_cleanup(); // Mosquitto library cleanup
}

void Broker::on_connect(int rc) {
    if (rc == 0){
        cout << " ##-Connected with Broker-## " << std::endl;
    }
    else {
        cout << "##-Unable to Connect Broker-## " << std::endl;
    }
}

bool Broker::subscribe_topic(const char * topic) {

    int ret = mosquitto_subscribe(this->mosq, NULL, topic, 0);
    if (ret) {
        cout << " ##-Cant publish topic {" << topic << "}-## " << std::endl;
        return false;
    }
    return true;
}

char* Broker::receive_msg() {

    return "";
}

bool Broker::send_msg (const char *message, const char * topic) {    
    int ret = mosquitto_publish (mosq, NULL, topic, strlen(message), message, 0, false);
    return (ret == MOSQ_ERR_SUCCESS);
}

void Broker::on_disconnect() {
    cout << " ##-Disconnected from Broker-## " << std::endl;
}

void Broker::on_publish(int mid) {
    cout << "## - Message published successfully" << endl;
}

void Broker::on_message(const struct mosquitto_message *message) {

}

void Broker::on_subcribe(int mid, int qos_count, const int *granted_qos) {

}