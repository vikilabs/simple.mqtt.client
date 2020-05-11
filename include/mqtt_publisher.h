/* MQTT Publisher Header
 *
 *              Author : Viki (a) Vignesh Natarajan
 *              Firma  : vikilabs.org               
 */


#ifndef MQTT_PUBLISHER_H
#define MQTT_PUBLISHER_H

#define TIMEOUT         10000L
#define QOS             1

/* MQTT PUBLISHER PARAMETERS */
typedef struct{
    const char *address;
    const char *uname;
    const char *passwd;
    const char *client_id;
}mqtt_pub_params_t;


int mqtt_publish(mqtt_pub_params_t *conn, char *topic, char *message);

#endif
