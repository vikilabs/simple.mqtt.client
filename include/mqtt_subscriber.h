/* MQTT Subscriber Library [ Header File ]
 *
 *              Author : Viki (a) Vignesh Natarajan
 *              Firma  : vikilabs.org               
 */
#ifndef MQTT_SUBSCRIBER_H
#define MQTT_SUBSCRIBER_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "MQTTClient.h"

#define TIMEOUT                 10000L
#define QOS                     1

/* MQTT SUBSCRIBER PARAMETERS */
typedef struct{
    const char *address;
    const char *uname;
    const char *passwd;
    const char *client_id;
    const char *topic;
}mqtt_sub_params_t;


extern pthread_t subscriber_thread;
extern int exit_mqtt_subscriber;
extern volatile MQTTClient_deliveryToken delivered_token;

extern int mqtt_subscribe();
extern void *mqtt_subscribe_thread(void *args);
extern int mqtt_unsubscribe();
extern int CB_MessageArrived(void *context, char *topic_name, int topic_len, MQTTClient_message *message);
extern void CB_MessageDelivered(void *context, MQTTClient_deliveryToken token);
extern void CB_ConnectionLost(void *context, char *reason);

#endif


