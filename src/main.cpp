#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <lcd.hpp>
#include <text.hpp>

const char* ssid = "Wokwi-GUEST";
LCD *lcd;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
// setup wifi
  WiFi.begin(ssid);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected");

  // setup lcd
  lcd = new LCD(0x27, 20, 4);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("Sending http request");

    HTTPClient http;

    String server = String("http://") + MAC_IP + ":8080/route/" + BUS_STOP;
    http.begin(server);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Text text(response, 20);
      if (text.getError()) {
        Serial.print("Json parse error: ");
        Serial.println(text.getError().c_str());
        http.end();
        return;
      }
      lcd->LCD_PrintLCD(text.getFirstBuffer(), text.getSecondBuffer(), "", text.getBottomBuffer());
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
