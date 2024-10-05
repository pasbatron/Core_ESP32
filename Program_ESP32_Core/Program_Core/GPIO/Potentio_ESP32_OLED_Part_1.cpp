#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

const int potPin = 34;

SoftwareSerial mySerialLora(32, 33);
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  mySerialLora.begin(19200);
  if (!display.begin(0x3C)) {
    while (true);
  }
  delay(2000);

  pinMode(potPin, INPUT);
}

void loop() {
  int potValue = analogRead(potPin);
  float voltage = potValue * (3.3 / 4095.0);
  String voltageString = String(voltage, 2);
  mySerialLora.println(voltageString);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("Voltage Value:");
  display.setCursor(0, 20);
  display.print(voltageString);
  display.print(" V");
  display.display();
  delay(1100);
}
