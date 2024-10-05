#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <SoftwareSerial.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SoftwareSerial mySerialLora(16, 17); //TX, RX

void setup() {
  mySerialLora.begin(9600);
  if (!display.begin(0x3C)) {
    while (true);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(20, 20);
  display.println("App Run!");
  display.setCursor(20, 40);
  display.println("Version 1.0");
  display.display();
}

void loop() {
  if(Serial.available() > 0){
    String input = Serial.readString();
    mySerialLora.println(input); 
  
  }
 
  if(mySerialLora.available() > 1){
    String input = mySerialLora.readString();
    Serial.println(input);  
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(10, 20);
    display.println("Data :");
    display.setCursor(10, 40);
    display.println(input);
    display.display();   
  }
  delay(1000);
}
