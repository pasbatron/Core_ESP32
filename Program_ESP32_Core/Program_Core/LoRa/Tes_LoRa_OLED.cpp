
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1


SoftwareSerial mySerialLora(16, 17); //TX, RX
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
    Serial.begin(9600);
    mySerialLora.begin(9600);
    if (!display.begin(0x3C)) {
        while (true);
    }
    delay(200);
}

void loop() {
    if(Serial.available() > 1){
        String input = Serial.readString();
        mySerialLora.println(input); 
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 10);
        display.println("Data : ");
        display.setCursor(10, 20);
        display.println(input);
        display.display();
        delay(1100);
    }
    delay(100);
}