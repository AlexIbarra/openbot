#ifndef MODULOBROKER_H
#define MODULOBROKER_H

#include <mosquitto.h>

using namespace std;

#define MQTT_USERNAME "admin"
#define MQTT_PASSWORD "admin"

class Broker {
private:
    struct mosquitto *mosq;
    const char * host;
    const char * id;
    int		port;

    void on_connect(int rc);
    void on_disconnect();
    void on_publish(int mid);
    void on_message(const struct mosquitto_message *message);
    void on_subcribe(int mid, int qos_count, const int *granted_qos);

public:
    Broker(const char *id, const char *host, int port);
    ~Broker();
    bool send_msg(const char *message, const char * topic);
    char* receive_msg();
    bool subscribe_topic(const char * topic);
};

#endif /* MODULOBROKER_H */

