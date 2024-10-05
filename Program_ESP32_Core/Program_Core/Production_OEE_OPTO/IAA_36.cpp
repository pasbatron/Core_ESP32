#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

const int buttonPinA2 = 32;
const int buttonPinA3 = 33;
const int buttonPinA4 = 25;
const int buttonPinA5 = 26;
const int buttonPinA13 = 27;
const int buttonPinA14 = 14;
const int buttonPinA15 = 12;

String dataOnA2 = "*iaa36on_mcfault#";
String dataOnA3 = "*iaa36on_fullwork#";
String dataOnA4 = "*iaa36on_qualitycheck#";
String dataOnA5 = "*iaa36on_toolchange#";
String dataOnA13 = "*iaa36on_arm#";
String dataOnA14 = "*iaa36on_roller#";
String dataOnA15 = "*iaa36on_pin#";

String dataOffA2 = "*iaa36off_mcfault#";
String dataOffA3 = "*iaa36off_fullwork#";
String dataOffA4 = "*iaa36off_qualitycheck#";
String dataOffA5 = "*iaa36off_toolchange#";
String dataOffA13 = "*iaa36off_arm#";
String dataOffA14 = "*iaa36off_roller#";
String dataOffA15 = "*iaa36off_pin#";

int buttonStateA2 = HIGH;
int buttonStateA3 = HIGH;
int buttonStateA4 = HIGH;
int buttonStateA5 = HIGH;
int buttonStateA13 = HIGH;
int buttonStateA14 = HIGH;
int buttonStateA15 = HIGH;

unsigned long lastDebounceTimeA2 = 0;
unsigned long lastDebounceTimeA3 = 0;
unsigned long lastDebounceTimeA4 = 0;
unsigned long lastDebounceTimeA5 = 0;
unsigned long lastDebounceTimeA13 = 0;
unsigned long lastDebounceTimeA14 = 0;
unsigned long lastDebounceTimeA15 = 0;
const unsigned long debounceDelay = 200;

unsigned long lastSendTime = 0;
const unsigned long sendInterval = 1000;  // 1 second

SoftwareSerial mySerialLora(16, 17); // TX, RX
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  mySerialLora.begin(9600);

  pinMode(buttonPinA2, INPUT_PULLUP);
  pinMode(buttonPinA3, INPUT_PULLUP);
  pinMode(buttonPinA4, INPUT_PULLUP);
  pinMode(buttonPinA5, INPUT_PULLUP);
  pinMode(buttonPinA13, INPUT_PULLUP);
  pinMode(buttonPinA14, INPUT_PULLUP);
  pinMode(buttonPinA15, INPUT_PULLUP);

  if (!display.begin(0x3C)) {
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(20, 20);
  display.println("App Run!");
  display.setCursor(20, 40);
  display.println("OEE 1.0 TPS");
  display.display();
}

void sendButtonData() {
  mySerialLora.print("*");
  mySerialLora.print(digitalRead(buttonPinA2) == LOW ? "on_mcfault" : "off_mcfault");
  mySerialLora.print(",");
  mySerialLora.print(digitalRead(buttonPinA3) == LOW ? "on_fullwork" : "off_fullwork");
  mySerialLora.print(",");
  mySerialLora.print(digitalRead(buttonPinA4) == LOW ? "on_qualitycheck" : "off_qualitycheck");
  mySerialLora.print(",");
  mySerialLora.print(digitalRead(buttonPinA5) == LOW ? "on_toolchange" : "off_toolchange");
  mySerialLora.print(",");
  mySerialLora.print(digitalRead(buttonPinA13) == LOW ? "on_arm" : "off_arm");
  mySerialLora.print(",");
  mySerialLora.print(digitalRead(buttonPinA14) == LOW ? "on_roller" : "off_roller");
  mySerialLora.print(",");
  mySerialLora.println(digitalRead(buttonPinA15) == LOW ? "on_pin" : "off_pin");

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(10, 20);
  display.println("Data Sent!");
  display.display();
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Kirim data setiap detik
  if (currentMillis - lastSendTime >= sendInterval) {
    sendButtonData();
    lastSendTime = currentMillis;
  }
}
