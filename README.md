## Basic MQTT Subscriber, Publisher library based on PAHO Library

Basic MQTT Subscriber, Publisher library based on PAHO Library

#### STEP 1 :  PAHO MQTT CLIENT Library Installation 

    1. git clone https://github.com/eclipse/paho.mqtt.c.git
    2. brew install doxygen
    3. cd paho.mqtt.c
    4. make
    5. sudo make install

###### In the event of compilation error do the following

    1. Open 'Makefile'
    2. Search for the following lines and comment them

        #   - $(INSTALL_DATA) ${blddir}/doc/MQTTClient/man/man3/MQTTClient.h.3 $(DESTDIR)${man3dir}
        #   - $(INSTALL_DATA) ${blddir}/doc/MQTTAsync/man/man3/MQTTAsync.h.3 $(DESTDIR)${man3dir}

    3. Save the file and exit


###### Clean and Recompile 

    1. sudo make clean
    2. sudo rm /usr/local/lib/libpaho-mqtt* #removes old libraries
    3. make
    4. sudo make install


#### STEP 2 : Compiling the library

    1. cd src
    2. make
    3. shared library and static library is generated at "../lib" directory

#### STEP 3: Example programs using the library

    1. cd examples
    2. ./compile.sh
    3. ./mqtt_sub   # This executable starts mqtt subscriber
    4. ./mqtt_pub   # This executable starts mqtt publisher
