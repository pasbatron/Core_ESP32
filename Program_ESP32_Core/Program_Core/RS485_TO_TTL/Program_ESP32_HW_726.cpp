#include <Arduino.h>
#include <ModbusRTU.h>
#include <SoftwareSerial.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

float InttoFloatInverse(uint16_t Data0, uint16_t Data1) {
  float x;
  unsigned long *p;
  p = (unsigned long*)&x;
  *p = (unsigned long)Data1 << 16 | Data0;
  return(x);
}

SoftwareSerial S(17, 16);
ModbusRTU mb;


bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data) {
  if (event != Modbus::EX_SUCCESS) {
    Serial.print("Request result: 0x");
    Serial.print(event, HEX);
  }
  return true;
}
void setup() {
  Serial.begin(9600);
  S.begin(19200, SWSERIAL_8E1);
  mb.begin(&S);
  mb.master();
}
uint16_t val[2];
void loop() {
  if (!mb.slave()) {
    mb.readHreg(1, 3027, val, 2, cb);
    while (mb.slave()) {
      mb.task();
      delay(100);
    }
    Serial.println("Register Values: ");
    Serial.println(val[0]);
    Serial.println(val[1]);
    float voltage = InttoFloatInverse(val[1], val[0]);
    Serial.println("Data = ");
    Serial.print(voltage);
    Serial.println(" V");
  }

  delay(1000);
}
