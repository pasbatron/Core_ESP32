#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

SoftwareSerial mySerialLora1(32, 33); //TX, RX
SoftwareSerial mySerialLora2(26, 27); //TX, RX
void setup() {
  Serial.begin(9600);
  mySerialLora1.begin(9600);
  mySerialLora2.begin(9600);
}

void loop() {
  if(Serial.available() > 0){
    String input = Serial.readString();
    mySerialLora2.println(input);    
  }
  if(mySerialLora2.available() > 1){
    String input1 = mySerialLora2.readString();
    Serial.println(input1);
  }
  delay(1000);
}