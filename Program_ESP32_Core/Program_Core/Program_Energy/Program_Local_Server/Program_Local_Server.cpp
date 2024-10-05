#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <ModbusRTU.h>
#include <Adafruit_GFX.h>
#include <SoftwareSerial.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_I2CDevice.h>

#define TX_G16 16
#define RX_G17 17
#define TX_G26 26
#define RX_G27 27
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float InttoFloat(uint16_t Data0, uint16_t Data1) {
  float x;
  unsigned long *p;
  p = (unsigned long*)&x;
  *p = (unsigned long)Data0 << 16 | Data1; // Big-endian
  return (x);
}

bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data) {
  if (event != Modbus::EX_SUCCESS) {
    Serial.print("Request result: 0x");
    Serial.println(event, HEX);
  }
  return true;
}

SoftwareSerial S(RX_G17, TX_G16); // RX, TX
SoftwareSerial mySerialLora(TX_G26, RX_G27); // TX, RX
ModbusRTU mb;

void updateDisplay(const char* message) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(10, 10);
  display.println("Data : ");
  display.setCursor(10, 30);
  display.println(message);
  display.display();
}

void setup() {
  mySerialLora.begin(19200);
  S.begin(19200, SWSERIAL_8E1);
  mb.begin(&S);
  mb.master();
  if (!display.begin(0x3C)) {
    while (true);
  }
  delay(1000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(10, 20);
  display.println("App Run!");
  display.setCursor(10, 40);
  display.println("TPS Version 1.0");
  display.display();
  delay(3000); 
}

void readAndSendData(uint8_t slaveId, uint16_t reg, const char* dp, const char* power_meter) {
  uint16_t data[2];
  if (!mb.slave()) {
    mb.readHreg(slaveId, reg, data, 2, cb);
    while (mb.slave()) {
      mb.task();
      delay(200);
    }
    float Data_Watt = InttoFloat(data[1], data[0]);
    mySerialLora.print("*,");
    mySerialLora.print(dp);
    mySerialLora.print(",");
    mySerialLora.print(power_meter);
    mySerialLora.print(",");
    mySerialLora.print(String(Data_Watt));
    mySerialLora.print(",");
    mySerialLora.print("#");
    mySerialLora.println();
    String data_send = "*" + String(dp) + "," +String(power_meter) +"," + String(Data_Watt) + ",#";
    updateDisplay(data_send.c_str());
    delay(3000);
  }
}



void loop() {
  // data kwh
  readAndSendData(1, 3960, "CH_SAA", "PM_220V");
  delay(1000);

  // data kwh
  readAndSendData(2, 3960, "CH_SAA", "PM_200V");
  delay(1000);

  // data kwh
  readAndSendData(3, 3960, "CH_SAB", "PM_220V");
  delay(1000);

  // data kwh
  readAndSendData(4, 3960, "CH_SAB", "PM_200V");
  delay(1000);

}
