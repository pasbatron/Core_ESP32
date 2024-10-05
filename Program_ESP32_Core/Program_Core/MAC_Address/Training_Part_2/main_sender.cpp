#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

// Ganti dengan informasi jaringan WiFi Anda
const char* ssid = "Pena";
const char* password = "pasbatron";

// MAC Address dari receiver (untuk referensi, tidak digunakan dalam kode ini)
const uint8_t receiverMAC[6] = {0x24, 0x6F, 0x28, 0x24, 0x32, 0x54};
const int udpPort = 12345;  // Port UDP untuk komunikasi

WiFiUDP udp;

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
  int randomValue1 = random(0, 100);
  int randomValue2 = random(0, 100);
  
  String message = String(randomValue1) + "," + String(randomValue2);
  
  udp.beginPacket(WiFi.broadcastIP(), udpPort);  // Kirim ke IP broadcast untuk jaringan lokal
  udp.write((const uint8_t*)message.c_str(), message.length());  // Kirim data sebagai byte
  udp.endPacket();
  
  Serial.print("Sent: ");
  Serial.println(message);

  delay(2000);  // Delay 2 detik
}
