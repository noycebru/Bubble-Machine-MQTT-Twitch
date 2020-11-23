/*******************************************************************
  Connect to local MQTT server with a Bot

  ESP8266 library from https://github.com/esp8266/Arduino

  Created for noycebru www.twitch.tv/noycebru
 *******************************************************************/
#include "bubble-machine.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//------------------------------
WiFiClient wiFiClient;
PubSubClient client(wiFiClient); // MQTT client

// Put your setup code here, to run once:
void setup() {

  setupSerial();

  setupPins();

  setupWIFI();
 
  setupWIFI();

  setupMQTT();
}

void setupSerial() {
  Serial.begin(115200);
  Serial.println();
}

void setupPins() {
    pinMode(LED_PIN, OUTPUT);
}

void setupWIFI() {
  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");

  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}

void setupMQTT() {
  client.setServer(MQTT_BROKER.c_str(), 1883);
  client.setCallback(callback);// Initialize the callback routine
}

void loop() {
  // Check to make sure we are connected to the mqtt server
  reconnectClient();

  // Tell the mqtt client to process its loop
  client.loop();
}

// Reconnect to client
void reconnectClient() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Attempt to connect
    if(client.connect(MQTT_ID.c_str())) {

      Serial.println("Connected!");

      for(int i=0;i < MQTT_TOPIC_COUNT;i++){
        client.subscribe(MQTT_TOPIC[i].c_str());
        Serial.print("Subcribed to: ");
        Serial.println(MQTT_TOPIC[i]);
      }
    } else {
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
    Serial.println('\n');
  }
}

// Handle incomming messages from the broker
void callback(char* topic, byte* payload, unsigned int length) {
  String response;
  String msgTopic = String(topic);

  Serial.println("topic received message:");
  Serial.println(msgTopic);

  for (int i = 0; i < length; i++) {
    response += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("] ");
  Serial.println(response);

  // TODO: find the correct value to insert
  if((response.indexOf("subscriber") > -1) || (response.indexOf("slap-redeem-id-here") > -1))
  {
    // We need to turn the bubbles on
    activateBubbles();
  }
}

void activateBubbles() {

  Serial.print("activateBubbles called");

  digitalWrite(LED_PIN, HIGH);
  delay(BUBBLE_TIME);
  digitalWrite(LED_PIN, LOW);
  delay(25);
}
