#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

SoftwareSerial mySerialLora1(12, 13); //TX, RX
SoftwareSerial mySerialLora2(26, 27); //TX, RX
SoftwareSerial mySerialLora3(32, 33); //TX, RX
SoftwareSerial mySerialLora4(16, 17); //TX, RX


void setup() {
  Serial.begin(9600);
  mySerialLora1.begin(9600);
  mySerialLora2.begin(9600);
  mySerialLora3.begin(9600);
  mySerialLora4.begin(9600);
}

void loop() {
  
  if(Serial.available() > 0){
    String input = Serial.readString();
    mySerialLora1.println(input);    
    mySerialLora2.println(input); 
    mySerialLora3.println(input); 
    mySerialLora4.println(input); 
    
  }
 
  if(mySerialLora1.available() > 1 || mySerialLora2.available() > 1 || mySerialLora3.available() > 1 || mySerialLora4.available() > 1){
    String input1 = mySerialLora1.readString();
    String input2 = mySerialLora2.readString();
    String input3 = mySerialLora3.readString();
    String input4 = mySerialLora4.readString();

    Serial.println(input1);    
    Serial.println(input2); 
    Serial.println(input3); 
    Serial.println(input4); 

  }
  delay(1000);
}