#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "mqtt_subscriber.h"

int exit_application = 0;

void signal_handler(int val)
{
    exit_application = 1;
}

int main()
{
    signal(SIGINT, signal_handler);
    mqtt_sub_params_t conn;
    
    conn.address = MQTT_BROKER_ADDRESS;
    conn.uname = NULL;
    conn.passwd = NULL;
    conn.client_id = MQTT_CLIENT_ID;
    conn.topic = MQTT_TOPIC;

    mqtt_subscribe(&conn);


    
    while(!exit_application)
    {
        sleep(1);
    }

    mqtt_unsubscribe();

    return 0;
}
