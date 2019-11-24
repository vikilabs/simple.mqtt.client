#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MQTTClient.h"

#define MQTT_BROKER_ADDRESS     "tcp://mqtt.eclipse.org:1883"
#define MQTT_CLIENT_ID          "Test Client"
#define MQTT_TOPIC              "mytopic"
#define MQTT_PAYLOAD            "Hello World!"
#define CONNECT_TIMEOUT         10000L
#define DISCONNECT_TIMEOUT      10000L
#define QOS                     1

int main(int argc, char* argv[])
{
    int ret;
    MQTTClient mqtt_publisher;
    MQTTClient_connectOptions conn_params = MQTTClient_connectOptions_initializer;
    MQTTClient_message mqtt_msg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;

    MQTTClient_create(&mqtt_publisher, MQTT_BROKER_ADDRESS, MQTT_CLIENT_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_params.keepAliveInterval = 10;
    conn_params.cleansession = 1;

    ret = MQTTClient_connect(mqtt_publisher, &conn_params);

    if (ret != MQTTCLIENT_SUCCESS )
    {
        printf("[ mqtt_client ] mqtt borker connect failed %d\n", ret);
        exit(-1);
    }

    mqtt_msg.payload    = MQTT_PAYLOAD;
    mqtt_msg.payloadlen = strlen(MQTT_PAYLOAD);
    mqtt_msg.qos        = QOS;
    mqtt_msg.retained   = 0;

    printf("[ mqtt_client ] publishing message -> %s\n", MQTT_PAYLOAD);
    MQTTClient_publishMessage(mqtt_publisher, MQTT_TOPIC, &mqtt_msg, &token);
    
    ret = MQTTClient_waitForCompletion(mqtt_publisher, token, CONNECT_TIMEOUT);

    if(ret == MQTTCLIENT_SUCCESS){
        printf("[ mqtt_client ] message delivery successfully ( token = %d ) \n", token);
    }else{
        printf("[ mqtt_client ] error - unable to deliver message( ret = %d ) \n", ret);
    }

    printf("[ mqtt_client ] disconnecting mqtt publisher\n");
    MQTTClient_disconnect(mqtt_publisher, DISCONNECT_TIMEOUT);
    MQTTClient_destroy(&mqtt_publisher);
    
    return ret;
}
