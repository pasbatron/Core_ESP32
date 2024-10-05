#include "BluetoothSerial.h" // Library untuk Bluetooth Serial

BluetoothSerial SerialBT;
const int ledPin = 2; // Pin untuk LED (misalnya GPIO2)

void setup() {
  pinMode(ledPin, OUTPUT); // Set pin LED sebagai output
  SerialBT.begin("ESP32_LED_Control"); // Nama Bluetooth ESP32
  Serial.begin(115200);
  Serial.println("Bluetooth Started! Waiting for connection...");
}

void loop() {
  if (SerialBT.available()) { // Jika ada data yang masuk
    char data = SerialBT.read(); // Baca data
    if (data == '1') {
      digitalWrite(ledPin, HIGH); // Nyalakan LED
      Serial.println("LED ON");
    } else if (data == '0') {
      digitalWrite(ledPin, LOW); // Matikan LED
      Serial.println("LED OFF");
    }
  }
}
