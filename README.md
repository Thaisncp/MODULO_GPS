# ESP32 + NEO-6M GPS + MQTT

Este proyecto permite obtener coordenadas de un módulo **GPS NEO-6M** conectado a un **ESP32**, y enviarlas mediante el protocolo **MQTT** a un broker configurado en la red.

## 🚀 Características
- Conexión del ESP32 a una red WiFi.  
- Lectura de coordenadas de latitud y longitud usando la librería [TinyGPS++](https://github.com/mikalhart/TinyGPSPlus).  
- Publicación de los datos en formato JSON a un tópico MQTT (`ubicacion`).  
- Reconexión automática en caso de pérdida de conexión al broker.  

## 📂 Estructura del repositorio
El repositorio contiene únicamente el archivo principal:  

- `gps_mqtt.ino` → Código fuente para el ESP32 que integra WiFi, GPS y MQTT.  

## 🔧 Requisitos de hardware
- ESP32  
- Módulo GPS NEO-6M  
- Conexión a internet (WiFi)  
- Servidor MQTT (puede ser Mosquitto u otro broker compatible)  

## 🛠️ Dependencias de software
Asegúrate de instalar estas librerías en el **Arduino IDE** o **PlatformIO**:  

- `TinyGPSPlus`  
- `WiFi` (incluida con ESP32)  
- `PubSubClient`  

## ⚙️ Configuración
En el archivo `.ino`, modifica las siguientes variables según tu entorno:  

```cpp
const char* ssid = "TU_SSID";          // Nombre de la red WiFi
const char* password = "TU_PASSWORD";  // Contraseña de la red WiFi

const char* mqtt_server = "IP_DEL_BROKER"; // Dirección IP del broker MQTT
const int mqtt_port = 1883;                // Puerto del broker (por defecto 1883)
const char* topic = "ubicacion";           // Tópico MQTT para publicar coordenadas
