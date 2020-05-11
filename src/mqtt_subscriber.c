/* MQTT Subscriber Library
 *
 *              Author : Viki (a) Vignesh Natarajan
 *              Firma  : vikilabs.org               
 */

#include <unistd.h>
#include "mqtt_subscriber.h"
#include <pthread.h>

volatile MQTTClient_deliveryToken delivered_token;
static MQTTClient mqtt_subscriber;
pthread_t subscriber_thread;

int exit_mqtt_subscriber = 0;

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

int mqtt_subscribe(mqtt_sub_params_t *conn)
{
    int ret;
    ret = pthread_create(&subscriber_thread, NULL, mqtt_subscribe_thread, (void *) conn);
    return ret;
}

void *mqtt_subscribe_thread( void *args)
{
    int ret;
    
    mqtt_sub_params_t *conn = (mqtt_sub_params_t *) args;

    MQTTClient_connectOptions conn_params = MQTTClient_connectOptions_initializer;
    MQTTClient_create(&mqtt_subscriber, conn->address, conn->client_id, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_params.keepAliveInterval = 10;
    conn_params.cleansession = 1;

    if(conn->uname){
        conn_params.username = conn->uname;
    }

    if(conn->passwd){
        conn_params.password = conn->passwd;
    }


    MQTTClient_setCallbacks(mqtt_subscriber, NULL, CB_ConnectionLost, CB_MessageArrived, CB_MessageDelivered);

    ret = MQTTClient_connect(mqtt_subscriber, &conn_params);

    if (ret != MQTTCLIENT_SUCCESS)
    {
        printf("[ mqtt_client ] connect failed ( %d )\n", ret);
        exit(EXIT_FAILURE);
    }

    printf("\n");
    printf("[ mqtt_client ] subscribing to topic %s\n", conn->topic);
   
    MQTTClient_subscribe(mqtt_subscriber, conn->topic, QOS);
    
    
    while(exit_mqtt_subscriber == 0){
        sleep(1);
    }

    printf("[ mqtt_client ] disconnecting mqtt subscriber\n");
    MQTTClient_disconnect(mqtt_subscriber, TIMEOUT);
    MQTTClient_destroy(&mqtt_subscriber);
    printf("[ mqtt_client ] mqtt subscriber disconnected\n");
    pthread_exit(NULL); 
}

int mqtt_unsubscribe()
{
    exit_mqtt_subscriber = 1;
    pthread_join(subscriber_thread, NULL); 
    return 0;
}
