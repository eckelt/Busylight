#include <Arduino.h>
#include <WiFi.h> // Für ESP32, bei ESP8266: #include <ESP8266WiFi.h>

struct WifiCredential {
  const char* ssid;
  const char* password;
};

WifiCredential wifiCredentials[] = {
  {"Guest", "***!"},
  {"iPhuhn", "***"},
  {"Nest", "***"},
};

const int wifiCredentialsCount = sizeof(wifiCredentials) / sizeof(wifiCredentials[0]);

const int led = D10; // there is no LED_BUILTIN available for the XIAO ESP32C3.

int currentCredential = 0;
unsigned long lastReconnectAttempt = 0;
const unsigned long reconnectInterval = 12000; // ms

void connectToWiFi() {
  Serial.print("Verbinde mit SSID: ");
  Serial.println(wifiCredentials[currentCredential].ssid);
  WiFi.mode(WIFI_STA); // SETS TO STATION MODE!
  WiFi.begin(wifiCredentials[currentCredential].ssid, wifiCredentials[currentCredential].password);
}

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  connectToWiFi();
  delay(1000);
}

void loop() {
  // LED blink
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
  Serial.print(wifiCredentials[currentCredential].ssid);
  Serial.println(WiFi.status() == WL_CONNECTED ? " verbunden" : " nicht verbunden");

  Serial.print("IP is ");
  Serial.println(WiFi.localIP());

  // WiFi reconnect logic
  if (WiFi.status() != WL_CONNECTED) {
    unsigned long now = millis();
    if (now - lastReconnectAttempt > reconnectInterval) {
      lastReconnectAttempt = now;
      currentCredential = (currentCredential + 1) % wifiCredentialsCount;
      connectToWiFi();
    }
  }
}
