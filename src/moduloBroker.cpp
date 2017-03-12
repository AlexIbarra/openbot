#include <iostream>
#include <cstring>
#include <stdexcept>
#include "moduloBroker.h"
#include <mosquittopp.h>
#include <mosquitto.h>

using namespace std;
using namespace mosqpp;

Broker::Broker(const char * _id, const char * _topic, const char * _host, int _port) : mosquittopp(_id)
{
    this->keepalive = 60;
    this->id = _id;
    this->port= _port;
    this->host = _host;
    this->topic = _topic;
 
    mosqpp::lib_init(); // Initialize libmosquitto
 
    if ( connect_async(host, port, keepalive) == MOSQ_ERR_ERRNO) { // Connect to MQTT Broker
            throw runtime_error("##ERROR##");
    }    
  
    loop_start();   // Start thread managing connection / publish / subscribe
};

Broker::~Broker() {
    loop_stop(); // Kill the thread
    mosqpp::lib_cleanup(); // Mosquitto library cleanup
}

void Broker::on_connect(int rc) {
    if (rc == 0){
        cout << " ##-Connected with Broker-## " << std::endl;
    }
    else {
        cout << "##-Unable to Connect Broker-## " << std::endl;
    }
}

bool Broker::send_msg (const char *message) {
    // Send message - depending on QoS, mosquitto lib managed re-submission this the thread
    //
    // * NULL : Message Id (int *) this allow to latter get status of each message
    // * topic : topic to be used
    // * lenght of the message
    // * message
    // * qos (0,1,2)
    // * retain (boolean) - indicates if message is retained on broker or not
    // Should return MOSQ_ERR_SUCCESS
    int ret =  publish (NULL, this->topic, strlen(message), message, 2, false);
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