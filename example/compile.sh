gcc -L/usr/local/lib/ -L../lib -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3cs -lpaho-mqtt3c -lpthread -lmqtt_publisher -I../include test_mqtt_publisher.c -o mqtt_pub 

gcc -L/usr/local/lib/ -L../lib -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3cs -lpaho-mqtt3c -lpthread  -lmqtt_subscriber -I../include test_mqtt_subscriber.c -o mqtt_sub
