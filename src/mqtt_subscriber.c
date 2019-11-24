#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "MQTTClient.h"

#define MQTT_BROKER_ADDRESS     "tcp://mqtt.eclipse.org:1883"
#define MQTT_CLIENT_ID    "client_1"
#define MQTT_TOPIC       "mytopic"
#define CONNECT_TIMEOUT         10000L
#define DISCONNECT_TIMEOUT      10000L
#define QOS         1


volatile MQTTClient_deliveryToken delivered_token;

int terminate_application = 0;

void signal_handler(int ret) 
{
    printf("[ mqtt_client ] 'ctrl + c' signal received\n");
    terminate_application = 1;
}

int CB_MessageArrived(void *context, char *topic_name, int topic_len, MQTTClient_message *message)
{
    int i, payload_len;
    char *payload;
    
    printf("[ mqtt_client ] message arrived  -> ");
    
    payload = message->payload;
    payload_len = message->payloadlen;

    for(i=0; i < payload_len; i++)
    {
        putchar(*payload++);
    }
    putchar('\n');
    
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topic_name);
   
    return 1;
}

void CB_MessageDelivered(void *context, MQTTClient_deliveryToken token)
{
    printf("[ mqtt_client ] message delivered  %d\n", token);
    delivered_token = token;
}


void CB_ConnectionLost(void *context, char *reason)
{
    printf("[ mqtt_client ] connection lost ( %s )\n", reason);
}

int main(int argc, char* argv[])
{
    int ret;
    
    signal(SIGINT, signal_handler);



    MQTTClient mqtt_subscriber;
    MQTTClient_connectOptions conn_params = MQTTClient_connectOptions_initializer;
    MQTTClient_create(&mqtt_subscriber, MQTT_BROKER_ADDRESS, MQTT_CLIENT_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_params.keepAliveInterval = 10;
    conn_params.cleansession = 1;
    MQTTClient_setCallbacks(mqtt_subscriber, NULL, CB_ConnectionLost, CB_MessageArrived, CB_MessageDelivered);

    ret = MQTTClient_connect(mqtt_subscriber, &conn_params);

    if (ret != MQTTCLIENT_SUCCESS)
    {
        printf("[ mqtt_client ] connect failed ( %d )\n", ret);
        exit(EXIT_FAILURE);
    }

    printf("\n");
    printf("[ mqtt_client ] subscribing to topic %s\n", MQTT_TOPIC);
   
    MQTTClient_subscribe(mqtt_subscriber, MQTT_TOPIC, QOS);
    
    printf("[ mqtt_client ] press 'ctrl + c' to quit application\n");
    
    while(terminate_application == 0){}
    
    MQTTClient_disconnect(mqtt_subscriber, DISCONNECT_TIMEOUT);
    MQTTClient_destroy(&mqtt_subscriber);
    
    return ret;
}
