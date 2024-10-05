
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
    mySerialLora.begin(19200);
    if (!display.begin(0x3C)) {
        while (true);
    }
    delay(200);
    display.clearDisplay();
}

void loop() {

  if(mySerialLora.available() > 1){
      String input = mySerialLora.readString();
      Serial.println(input); 
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SH110X_WHITE);
      display.setCursor(20, 20);
      display.println("Voltage : ");
      display.setCursor(20, 50);
      display.print(input);
      display.println(" V");
      display.display();
      delay(1000);

  }
  delay(100);
}