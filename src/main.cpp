#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  Serial.println(GOTRANSIT_KEY);
  WiFi.begin(ssid);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("Sending http request");

    HTTPClient http;

    http.begin("https://jsonplaceholder.typicode.com/todos/1");
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
      Serial.println("Success");
    } else {
      Serial.print("Error on http request: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Wi-Fi not connected");
  }

  delay(10000);
}
