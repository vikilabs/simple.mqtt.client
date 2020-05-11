#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "mqtt_publisher.h"

#define MQTT_BROKER_ADDRESS     "tcp://mqtt.eclipse.org:1883"
#define CLIENT_ID               "Test Client"
#define TOPIC                   "mytopic"
#define MESSAGE                 "Hello World!"


int exit_application = 0;

void signal_handler(int val)
{
    exit_application = 1;
}

int main()
{
    signal(SIGINT, signal_handler);
    mqtt_pub_params_t conn;
    
    conn.address = MQTT_BROKER_ADDRESS;
    conn.uname = NULL;
    conn.passwd = NULL;
    conn.client_id = CLIENT_ID;
        
    mqtt_publish(&conn, TOPIC, MESSAGE);

    
    while(!exit_application)
    {
        sleep(1);
    }

    return 0;
}
