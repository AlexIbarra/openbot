#ifndef MODULOBROKER_H
#define MODULOBROKER_H

#include <mosquittopp.h>
#include <mosquitto.h>


class Broker : public mosqpp::mosquittopp {
private:
    const char * host;
    const char * id;
    const char * topic;
    int		port;
    int		keepalive;

    void on_connect(int rc);
    void on_disconnect();
    void on_publish(int mid);
    void on_message(const struct mosquitto_message *message);
    void on_subcribe(int mid, int qos_count, const int *granted_qos);

public:
    Broker(const char *id, const char * _topic, const char *host, int port);
    ~Broker();
    bool send_msg(const char *message);
};

#endif /* MODULOBROKER_H */

