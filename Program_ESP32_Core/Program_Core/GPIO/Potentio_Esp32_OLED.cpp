#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

const int potPin = 34;

SoftwareSerial mySerialLora(32, 33); // TX, RX
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  mySerialLora.begin(19200);

  // Initialize the display
  if (!display.begin(0x3C)) {
    while (true); // Stop here if display does not initialize
  }
  delay(2000);

  pinMode(potPin, INPUT);
}

void loop() {
  // Read the potentiometer value
  int potValue = analogRead(potPin);
  
  // Convert the potentiometer value to voltage
  float voltage = potValue * (3.3 / 4095.0);

  // Convert voltage to string
  String voltageString = String(voltage, 2); // 2 decimal places

  // Send data via LoRa
  mySerialLora.print("Potentio: ");
  mySerialLora.print(potValue);
  mySerialLora.print(" | Voltage: ");
  mySerialLora.println(voltageString);

  // Clear the display
  display.clearDisplay();

  // Set text size and color
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

  // Print text on the display
  display.setCursor(0, 0); // Set cursor to the top left corner
  display.println("Voltage Value:");

  display.setCursor(0, 20); // Set cursor to the next line
  display.print(voltageString); // Print the voltage string
  display.print(" V"); // Add a "V" for volts

  // Display the content on the OLED
  display.display();

  // Calculate delay based on potentiometer value
  // Map the potentiometer value to a delay range
  // For example, map 0-4095 to 100-1000 milliseconds
  int delayTime = map(potValue, 0, 4095, 100, 1000);

  // Delay for a period based on the potentiometer value
  delay(delayTime);
}
