#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include "WiFi.h"

// Replace with your network credentials
const char* ssid = "Pena";
const char* password = "pasbatron";

void setup() {
    Serial.begin(115200);

    // Set Wi-Fi mode to Station (STA)
    WiFi.mode(WIFI_STA);

    // Connect to the Wi-Fi network
    WiFi.begin(ssid, password);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    // Print the ESP32's MAC address
    Serial.print("ESP32 Board MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void loop() {
    // Your other code here
}
