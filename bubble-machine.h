/*******************************************************************
  Connect to local MQTT server with a Bot

  Created with code from noycebru www.twitch.tv/noycebru
 *******************************************************************/

#ifndef BUBBLE_MACHINE_H
#define BUBBLE_MACHINE_H

// Configure your default pin numbers
const int LED_PIN = 5;

// The amount of time to run the bubble machine
const int BUBBLE_TIME = 10000; // time in ms

//------- Update the following! ------
const String MQTT_ID = "bubble-machine-001"; // ID for this client when connecting to MQTT
const String MQTT_BROKER = "192.168.1.22"; // Hostname or IP of your MQTT server
const int MQTT_PORT = 1883; // Set the port used by your MQTT server
const int MQTT_RECONNECT_DELAY = 5000; // Time in ms to wait between reconnect attempts
const int MQTT_TOPIC_COUNT = 1; // This should match the number of topics you wish to subscribe to
const String MQTT_TOPIC[MQTT_TOPIC_COUNT] = {"bubbles"}; // The topic name you wish to listen for

#endif
