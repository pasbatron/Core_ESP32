#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <SoftwareSerial.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SoftwareSerial mySerialLora(16, 17); //TX, RX

String previousInput = "";  // Untuk menyimpan data sebelumnya

void setup() {
  mySerialLora.begin(9600);
  if (!display.begin(0x3C)) {
    Serial.println(F("OLED tidak terdeteksi!"));
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(20, 20);
  display.println("App Running...!!!");
  display.setCursor(20, 40);
  display.println("");
  display.display();
  delay(2000);
}

void loop() {
  if (mySerialLora.available() > 0) {
    String input = mySerialLora.readString();
    
    // Hanya update display jika input berubah
    if (input != previousInput) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SH110X_WHITE);
      display.setCursor(10, 20);
      display.println("Data : ");
      display.setCursor(10, 40);
      display.println(input);
      display.display();
      
      // Simpan input sebagai previousInput
      previousInput = input;
    }
  }
  delay(1000);
}
