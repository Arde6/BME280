#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "BeerCan";
const char *password = "K7TY4HK7TY";

// MQTT Broker
const char *mqtt_broker = "172.27.34.199";
const char *topic = "BME280";
const char *mqtt_username = "mosquitto";
const char *mqtt_password = "Peruna123";
const int mqtt_port = 1883;

//Client
WiFiClient espClient;
PubSubClient client(espClient);

void wifiBegin () {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the Wi-Fi network");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP()); 
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message: ");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
}

void mqttBegin () {
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());

    Serial.print("Pinging MQTT broker... ");
    Serial.println(mqtt_broker);

    WiFiClient testClient;
    if (testClient.connect(mqtt_broker, mqtt_port)) {
        Serial.println("Broker is reachable via TCP!");
        testClient.stop();
    } else {
        Serial.println("Cannot reach broker! Check IP or firewall.");
    }

    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
        if (client.connect(client_id.c_str()/*, mqtt_username, mqtt_password*/)) {
            Serial.println("Public MQTT broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void mqttPublish (float temperature,  float humidity, float pressure, int id) {
    char msg[100];
    snprintf(msg, sizeof(msg), "T:%.2f, H:%.2f, P:%.2f, ID:%d", temperature, humidity, pressure, id);
    client.publish(topic, msg);
    client.loop();
}