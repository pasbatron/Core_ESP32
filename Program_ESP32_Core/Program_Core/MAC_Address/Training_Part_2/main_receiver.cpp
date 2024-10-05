#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

// Ganti dengan informasi jaringan WiFi Anda
const char* ssid = "Pena";
const char* password = "pasbatron";

// MAC Address dari sender (untuk referensi, tidak digunakan dalam kode ini)
const uint8_t senderMAC[6] = {0xFC, 0xE8, 0xC0, 0x74, 0xF8, 0x24};
const int udpPort = 12345;  // Port UDP untuk komunikasi

WiFiUDP udp;
char incomingPacket[255];

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  udp.begin(udpPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
      
      Serial.print("Received: ");
      Serial.println(incomingPacket);
    }
  }
}
