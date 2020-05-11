/* MQTT Publisher Library
 *
 *              Author : Viki (a) Vignesh Natarajan
 *              Firma  : vikilabs.org               
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#include "mqtt_publisher.h"

int mqtt_publish(mqtt_pub_params_t *conn, char *topic, char *message)
{
    int ret;
    MQTTClient mqtt_publisher;
    MQTTClient_connectOptions conn_params = MQTTClient_connectOptions_initializer;
    MQTTClient_message mqtt_msg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;

    MQTTClient_create(&mqtt_publisher, conn->address, conn->client_id, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    if(conn->uname){
        conn_params.username = conn->uname;
    }

    if(conn->passwd){
        conn_params.password = conn->passwd;
    }

    conn_params.keepAliveInterval = 10;
    conn_params.cleansession = 1;

    ret = MQTTClient_connect(mqtt_publisher, &conn_params);

    if (ret != MQTTCLIENT_SUCCESS )
    {
        printf("[ mqtt_client ] mqtt borker connect failed %d\n", ret);
        return ret;
    }

    mqtt_msg.payload    = message;
    mqtt_msg.payloadlen = strlen(message);
    mqtt_msg.qos        = QOS;
    mqtt_msg.retained   = 0;

    printf("[ mqtt_client ] publishing message -> %s\n", message);
    MQTTClient_publishMessage(mqtt_publisher, topic, &mqtt_msg, &token);
    
    ret = MQTTClient_waitForCompletion(mqtt_publisher, token, TIMEOUT);

    if(ret == MQTTCLIENT_SUCCESS){
        printf("[ mqtt_client ] message delivery successfully ( token = %d ) \n", token);
    }else{
        printf("[ mqtt_client ] error - unable to deliver message( ret = %d ) \n", ret);
    }

    printf("[ mqtt_client ] disconnecting mqtt publisher\n");
    MQTTClient_disconnect(mqtt_publisher, TIMEOUT);
    MQTTClient_destroy(&mqtt_publisher);
    
    return ret;
}
