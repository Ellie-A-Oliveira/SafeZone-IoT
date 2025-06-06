#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <MPU6050.h>

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// DHT22
#define DHTPIN 19
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// LED
#define LED_PIN 2

// MPU6050
MPU6050 imu;

// ThingSpeak
const char* server = "api.thingspeak.com";
const String writeAPIKey = "YOUR_THINGSPEAK_WRITE_API_KEY";

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("Iniciando sensores...");
  dht.begin();

  Wire.begin();
  imu.initialize();

  if (!imu.testConnection()) {
    Serial.println("Falha na conexao MPU6050");
  } else {
    Serial.println("MPU6050 conectado.");
  }

  // WiFi padrão do Wokwi
  Serial.print("Conectando WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Erro lendo DHT22");
      return;
    }

    int16_t ax, ay, az;
    imu.getAcceleration(&ax, &ay, &az);

    // Acende LED se temperatura > 30°C
    if (temperature > 30.0) {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }

    Serial.print("Temp: "); Serial.print(temperature);
    Serial.print(" °C, Umidade: "); Serial.print(humidity);
    Serial.print("% | Acel: X="); Serial.print(ax);
    Serial.print(" Y="); Serial.print(ay);
    Serial.print(" Z="); Serial.println(az);

    // Monta URL para ThingSpeak (usando update por GET)
    String url = "/update?api_key=" + writeAPIKey;
    url += "&field1=" + String(temperature);
    url += "&field2=" + String(humidity);
    url += "&field3=" + String(ax);
    url += "&field4=" + String(ay);
    url += "&field5=" + String(az);
    url += "&field6=" + String(digitalRead(LED_PIN)); // estado LED

    HTTPClient http;
    String fullUrl = String("http://") + server + url;

    http.begin(fullUrl);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.println("Dados enviados ao ThingSpeak com sucesso.");
    } else {
      Serial.println("Falha ao enviar dados: " + String(httpCode));
    }
    http.end();
  } else {
    Serial.println("WiFi desconectado");
  }

  delay(15000); // Limite do ThingSpeak (1 atualização a cada 15s)
}
