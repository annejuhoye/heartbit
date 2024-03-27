#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

const char* ssid = "ESP32-AP-A";
const char* password = "12345678";

WebServer server(80);

#define BUTTON_PIN 1
#define LED_PIN 0

unsigned long ledActivatedTime = 0; // Follow the Led
bool ledIsActivated = false; // LED state

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/activateLED", []() {
    Serial.println("Received request to activate LED on A");
    digitalWrite(LED_PIN, HIGH); // Led state HIGH
    ledActivatedTime = millis(); // Save the moment
    ledIsActivated = true;
    server.send(200, "text/plain", "LED activated on A for 2 seconds");
  });

  server.begin();
}

void loop() {
  server.handleClient();

  // LED HIGH for 2 seconds
  if (ledIsActivated && (millis() - ledActivatedTime >= 2000)) {
    digitalWrite(LED_PIN, LOW); // Éteindre la LED
    ledIsActivated = false; // Réinitialisez l'état de la LED
  }

  // button
  static unsigned long lastDebounceTime = 0;
  bool buttonState = digitalRead(BUTTON_PIN);

  if (millis() - lastDebounceTime > 50) { // Debounce delay
    if (buttonState == LOW) {
      Serial.println("Button on A pressed, sending request to B");
      HTTPClient http;
      http.begin("http://192.168.4.2/activateRGBAndMotor");
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.println("Request sent to B successfully");
      } else {
        Serial.println("Failed to send request to B");
      }
      http.end();
      lastDebounceTime = millis();
    }
  }
}
