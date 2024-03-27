#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>
#include <HTTPClient.h>

// Paramètres WiFi
const char* ssid = "ESP32-AP-A";
const char* password = "12345678";

WebServer server(80);

#define BUTTON_PIN 1
#define RGB_LED_PIN 0
#define NUMPIXELS 1 
#define MOTOR_PIN 20 

Adafruit_NeoPixel pixels(NUMPIXELS, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);
unsigned long timeLEDActivated = 0; // follow the LED's state
bool ledActive = false; // State LED HIGH

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pixels.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.on("/activateRGBAndMotor", []() {
    Serial.println("Activating RGB and Motor for 2 seconds on B");
    pixels.setPixelColor(0, pixels.Color(0, 255, 0)); // Color Green
    pixels.show();
    timeLEDActivated = millis();
    ledActive = true;
    server.send(200, "text/plain", "Activated RGB and Motor on B");
  });
   server.begin();
}

void loop(){
  server.handleClient();
  // LED HIGH for 2 seconds
  if (ledActive && (millis() - timeLEDActivated >= 2000)) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Led state is LOW
    pixels.show();
    ledActive = false;
  }

  static unsigned long lastDebounceTime = 0;
  bool buttonState = digitalRead(BUTTON_PIN);

  if (millis() - lastDebounceTime > 50) {
    if (buttonState == LOW) {
      Serial.println("Button on B pressed, attempting to send request to A...");
      HTTPClient http;
      http.begin("http://192.168.4.1/activateLED"); 
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.println("Request sent to A successfully");
      } else {
        Serial.printf("Failed to send request to A, HTTP code: %d\n", httpCode);
      }
      http.end();
      lastDebounceTime = millis();
    }
  }
}


