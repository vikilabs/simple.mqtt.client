CC=gcc
DEPS=mqtt_publisher.h mqtt_subscriber.h
CFLAGS=-I../include
ODIR=../lib
LIBS=-lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3cs -lpaho-mqtt3c -lpthread

all:
		$(CC) -shared -o $(ODIR)/libmqtt_publisher.so   $(LIBS) $(CFLAGS)  -fPIC   mqtt_publisher.c
		$(CC) -shared -o $(ODIR)/libmqtt_subscriber.so  $(LIBS) $(CFLAGS)  -fPIC   mqtt_subscriber.c
		$(CC) -c $(CFLAGS) -o $(ODIR)/mqtt_publisher.o mqtt_publisher.c
		$(CC) -c $(CFLAGS) -o $(ODIR)/mqtt_subscriber.o mqtt_subscriber.c

		ar rcs $(ODIR)/libmqtt_publisher.a  $(ODIR)/mqtt_publisher.o
		ar rcs $(ODIR)/libmqtt_subscriber.a $(ODIR)/mqtt_publisher.o
		rm -rf $(ODIR)/mqtt_publisher.o $(ODIR)/mqtt_subscriber.o

clean:
	rm -rf $(ODIR)/mqtt_subscriber.o
	rm -rf $(ODIR)/mqtt_publisher.o
	rm -rf $(ODIR)/libmqtt_subscriber.so
	rm -rf $(ODIR)/libmqtt_publisher.so
	rm -rf $(ODIR)/libmqtt_publisher.a
	rm -rf $(ODIR)/libmqtt_subscriber.a
