#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 21
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char *ssid = ".........";
const char *password = ".........";
const char *host = ".........";
const int port = 3000;

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }  

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial.println(F("DHTxx test!"));  
  dht.begin();  
}

void loop() 
{ 
  delay(10000);
  // Configuração do DHT11 ----------------------------  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);

  float hic = dht.computeHeatIndex(t, h, false);
  
  // Requisição HTTP -----------------------------------
  HTTPClient http;
  http.begin(host, port, "/");
 
  http.addHeader("Content-Type", "application/json");

  String payload = "{\"temperatura\":" + String(t) + ",\"umidade\":" + String(h) + "}";   
  
  int httpCode = http.POST(payload);  

  if (httpCode > 0) {
    // Requisição bem-sucedida
    String resposta = http.getString();
    Serial.println(resposta);
  } else {
    // Falha na requisição
    Serial.println("Erro ao realizar requisição");
  }
  http.end();
}
