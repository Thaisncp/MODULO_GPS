#include <TinyGPSPlus.h>
#include <WiFi.h>
#include <PubSubClient.h>

TinyGPSPlus gps;

const char* ssid = "DAYSI";
const char* password = "1106042474001";

const char* mqtt_server = "20.205.17.176";
const int mqtt_port = 1883;
const char* topic = "ubicacion";

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando a MQTT...");
    if (client.connect("ESP32-NEO6M")) {
      Serial.println("Conectado.");
    } else {
      Serial.print("Error, rc=");
      Serial.print(client.state());
      Serial.println(" Intentando de nuevo en 5 segundos.");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  Serial0.begin(9600);

  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" WiFi conectado.");
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  while (Serial0.available() > 0) {
    char c = Serial0.read();
    if (gps.encode(c)) {
      if (gps.location.isValid()) {
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();
        String payload = "{\"latitud\":" + String(latitude, 6) + 
                         ",\"longitud\":" + String(longitude, 6) + "}";
        
        client.publish(topic, payload.c_str());
        Serial.println("Coordenadas enviadas a MQTT:");
        Serial.println(payload);
      }
    }
  }

  delay(10000);

}
