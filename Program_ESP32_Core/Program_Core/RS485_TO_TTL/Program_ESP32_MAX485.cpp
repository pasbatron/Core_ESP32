#include <Arduino.h>
#include <ModbusRTU.h>
#include <SoftwareSerial.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

// Function to convert two 16-bit register values to a floating-point number
float InttoFloatInverse(uint16_t Data0, uint16_t Data1) {
  float x;
  unsigned long *p;
  p = (unsigned long*)&x;
  *p = (unsigned long)Data1 << 16 | Data0; // Inverse Big-endian to Little-endian conversion
  return(x);
}

SoftwareSerial S(17, 16);
ModbusRTU mb;

// Callback function to monitor errors
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
  mb.begin(&S, 0); // RE/DE connected to D0 of ESP8266
  mb.master();
}

uint16_t val[2]; // Array to store 2 register values
void loop() {
  
  if (!mb.slave()) {
    // Reading from Modbus register 3027 (register address is 3926)
    mb.readHreg(1, 3027, val, 2, cb); // Slave ID is 1, reading 2 registers
    while (mb.slave()) { // Check if transaction is active
      mb.task();
      delay(100);
    }

    Serial.println("Register Values ");
    Serial.println(val[0]);
    Serial.println(val[1]);

    // Convert register values using inverse float conversion
    float voltage = InttoFloatInverse(val[1], val[0]);
    Serial.println("Data = ");
    Serial.print(voltage);
    Serial.println(" V");

  }
  delay(1000);
}
