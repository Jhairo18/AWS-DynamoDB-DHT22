#include <ArduinoJson.h>   // Librería para manejar y generar JSON en Arduino
#include "DHT.h"           // Librería para manejar el sensor DHT (humedad y temperatura)
#include <TimeLib.h>       // Librería para manejar fecha y hora en Arduino

#define DHTPIN 4           // Pin digital donde está conectado el sensor DHT
#define DHTTYPE DHT22      // Tipo de sensor (DHT11, DHT22, etc.)

DHT dht(DHTPIN, DHTTYPE);  // Creación del objeto DHT con el pin y tipo definidos

void setup() {
  Serial.begin(9600);      // Inicializa la comunicación serie a 9600 baudios
  setTime(10, 0, 0, 5, 10, 2025); // Fija la hora inicial: hh, mm, ss, día, mes, año
  dht.begin();             // Inicializa el sensor DHT
}

void loop() {
  delay(2000);             // Espera 2 segundos entre lecturas del sensor
  
  String fechaHora = obtenerFechaHora();  // Obtiene la fecha y hora actual como string
  float h = dht.readHumidity();           // Lee la humedad del DHT
  float t = dht.readTemperature();        // Lee la temperatura en °C del DHT

  // Validación: si la lectura falla, imprime un mensaje de error en formato JSON
  if (isnan(h) || isnan(t)) {
    Serial.println(F("{\"error\":\"Failed to read from DHT sensor\"}"));
    return; // Sale de la función loop para volver a intentarlo en el siguiente ciclo
  }

  // Creamos un objeto JSON con ArduinoJson
  StaticJsonDocument<200> doc; // Reservamos 200 bytes para el objeto JSON
  doc["humidity"] = h;         // Insertamos el valor de humedad
  doc["temperature"] = t;      // Insertamos el valor de temperatura
  doc["tiempo"] = fechaHora;   // Insertamos la fecha y hora como string

  // Serializamos (convertimos a texto) el objeto JSON para enviarlo por Serial
  String output;
  serializeJson(doc, output);
  Serial.println(output);      // Imprime el JSON generado
}

// Función que retorna la fecha y hora en formato "dd/mm/aaaa, hh:mm:ss"
String obtenerFechaHora() {
  String fechaHora = "";

  // Día
  if (day() < 10) fechaHora += "0";     // Añade un 0 delante si es menor a 10
  fechaHora += String(day()) + "/";

  // Mes
  if (month() < 10) fechaHora += "0";   // Añade un 0 delante si es menor a 10
  fechaHora += String(month()) + "/";

  // Año
  fechaHora += String(year()) + ", ";

  // Hora
  if (hour() < 10) fechaHora += "0";    // Añade un 0 delante si es menor a 10
  fechaHora += String(hour()) + ":";

  // Minuto
  if (minute() < 10) fechaHora += "0";  // Añade un 0 delante si es menor a 10
  fechaHora += String(minute()) + ":";

  // Segundo
  if (second() < 10) fechaHora += "0";  // Añade un 0 delante si es menor a 10
  fechaHora += String(second());

  return fechaHora;  // Devuelve la cadena con fecha y hora formateada
}

