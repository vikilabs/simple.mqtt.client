## Simple MQTT Subscriber and Publisher using PAHO Library 

A simple MQTT Subscriber, Publisher written in C with PAHO Library

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


#### STEP 2 :  TESTING PAHO MQTT CLIENT IN TERMINAL 

###### Terminal 1
    
    In terminal 1, run mqtt subscriber

    $paho_c_sub -t topic_name --connection <ipaddress>:<port>

    Example:

    $paho_c_sub -t my_topic --connection mqtt.eclipse.org:1883


###### Terminal 2
    
    In terminal 2, run mqtt publisher

    $paho_c_pub -t topic_name --connection <ipaddress>:<port> -m <message to send>

    Example:

    $paho_c_pub -t my_topic --connection mqtt.eclipse.org:1883 -m "Hello World!"


#### STEP 3 :  Compiling and Running MQTT Subscriber written in C

    1. cd src/
    2. compile mqtt subscriber
        
       $gcc -L/usr/local/lib/ -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3cs -lpaho-mqtt3c  mqtt_subscriber.c -o subscriber

    3. run mqtt subscriber

       $./subscriber

       [ subscriber will be waiting for message in topic named mytopic ]

#### STEP 4 :  Compiling and Running MQTT Publisher written in C

    1. cd src/
    2. compile mqtt publisher
        
       $gcc -L/usr/local/lib/ -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3cs -lpaho-mqtt3c  mqtt_publisher.c -o publisher

    3. run mqtt publisher

       $./publisher

       [ publisher will be send message to topic named mytopic and exit]


