# 🌡️ IoT Environment Monitor con AWS y Node-RED

![Python](https://img.shields.io/badge/Python-3.10-blue)
![AWS IoT Core](https://img.shields.io/badge/AWS-IoT%20Core-orange)
![Node-RED](https://img.shields.io/badge/Node--RED-Flow-red)
![ESP32](https://img.shields.io/badge/ESP32-Enabled-lightgrey)
![License](https://img.shields.io/badge/License-MIT-green)

---
## 🧠 Descripción general

Este proyecto implementa un **sistema IoT** para el monitoreo en tiempo real de **temperatura y humedad** utilizando un **sensor DHT22** conectado a un **ESP32**, con integración hacia **AWS IoT Core** y visualización mediante **Node-RED**.

Los datos se almacenan automáticamente en **DynamoDB** mediante una **función AWS Lambda**, lo que permite analizar el historial ambiental o integrarlo con otros servicios en la nube.

---
## ⚙️ Flujo del sistema

El flujo general del sistema es el siguiente:
 El **ESP32** lee los valores de temperatura y humedad del **DHT22**.  
- **Node-RED** actúa como un **puente MQTT**, publicando los datos en el tópico `sala/temhum` hacia **AWS IoT Core**.  
- **AWS IoT Core** activa una **regla IoT** que envía los mensajes a una **función Lambda**.  
- **Lambda** escribe los datos en una tabla **DynamoDB**, donde pueden ser consultados desde la consola de AWS.

---
## 📡 Conexión física (hardware)

| Componente | Pin ESP32 | Descripción |
|-------------|------------|-------------|
| DHT22 (VCC) | 3.3V | Alimentación |
| DHT22 (GND) | GND | Tierra |
| DHT22 (DATA) | GPIO 4 | Lectura de datos |
| Resistencia | 10kΩ entre VCC y DATA | Pull-up recomendada |

📸 **Esquema de conexión:**
![Esqumeatico](https://github.com/Jhairo18/AWS-DynamoDB-DHT22/blob/master/esquematico.png)
---
## 🧩 Estructura de datos enviada
Los datos serán enviados en formato json, por el puerto serial en codigo arduino, luego por node-red habra una funcion que haga que lo convierta en json y este se envie por el nodo de mqtt out, que sera definido mediante el topico de sala/temhum

{
  "temperatura": 24.6,
  "humedad": 53.2,
  "tiempo": "05/10/2025, 10:24:46"
}
## Integración AWS
- Tópico MQTT: sala/temhum
- Regla IoT Core: Activa una función Lambda
- Lambda: Inserta los datos recibidos en DynamoDB
- Tabla DynamoDB: Contiene columnas temperatura, humedad y tiempo

📘 Ejemplo de registro en DynamoDB:
temperatura	humedad	tiempo

| Tiempo | Fecha | Hora | Temperatura | Humedad |
|-------------|------------|-------------|------------|-------------|
| 05/10/2025, 10:24:46 | 05/10/2025| 10:24:4 | 24.6| 53.2|
## 🔁 Node-RED como puente MQTT
Node-RED se utiliza para facilitar la publicación MQTT entre el microcontrolador y AWS IoT Core.
El flujo se compone principalmente de:
📸 Esquema del flujo general:
## 🚀 Tecnologías usadas
- ESP32 
- Sensor DHT22
- AWS IoT Core
- AWS Lambda
- AWS DynamoDB
- Node-RED (como puente MQTT)
- Arduino IDE / Python
## 👤 Autor
Jhairo Yurivilca
📧 Contacto: [jhairoypp@gmail.com]}

💡 Proyecto académico de IoT con AWS y Node-RED
