#include <Arduino.h>
#include <ModbusRTU.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1


Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


float InttoFloatInverse(uint16_t Data0, uint16_t Data1) {
  float x;
  unsigned long *p;
  p = (unsigned long*)&x;
  *p = (unsigned long)Data1 << 16 | Data0;
  return(x);
}


SoftwareSerial S(17, 16);
SoftwareSerial mySerialLora(26, 27);

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
  S.begin(19200, SWSERIAL_8E1);  // Begin Software Serial with correct baud rate and parity for Modbus
  mb.begin(&S);                  // Initialize Modbus communication
  mb.master();                   // Set Modbus mode to master

  // Initialize the OLED display
  if (!display.begin(0x3C)) {
    Serial.println("OLED display initialization failed!");
    while (true); // Stay here if OLED initialization fails
  }

  // Initialize LoRa communication
  mySerialLora.begin(9600);  // Set baud rate for LoRa communication

  delay(2000);  // Give OLED time to initialize
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(20, 20);
  display.println("App Run!");
  display.setCursor(20, 40);
  display.println("OEE 1.0 TPS");
  display.display();
  delay(2000);
  display.clearDisplay();
}

uint16_t val[2];  // Array to hold register values

// Function to read, display, and send Modbus register values via LoRa
void readDisplayAndSendRegister(uint16_t reg, int displayRow) {
  if (!mb.slave()) {
    mb.readHreg(1, reg, val, 2, cb);  // Read two 16-bit registers
    while (mb.slave()) {
      mb.task();
      delay(100);
    }

    float voltage = InttoFloatInverse(val[1], val[0]);  // Convert to float

    // Display the value on OLED
    display.setCursor(0, displayRow * 10);  // Adjust the row to avoid overwriting text
    display.print("Reg ");
    display.print(reg);
    display.print(": ");
    display.print(voltage);
    display.println(" V");
    display.display();  // Update OLED

    // Send data via LoRa
    String dataToSend = "*CR1220" + "," + String(voltage) + "V,;";
    mySerialLora.println(dataToSend);  // Send the register value through LoRa

    Serial.print("Register ");
    Serial.print(reg);
    Serial.print(": ");
    Serial.println(voltage);
    delay(1100);
  }
}

void loop() {

// GET VOLTAGE
  display.clearDisplay();
  readDisplayAndSendRegister(3019, 0);
  display.clearDisplay();
  readDisplayAndSendRegister(3021, 1);
  display.clearDisplay();
  readDisplayAndSendRegister(3023, 2);
  display.clearDisplay();
  readDisplayAndSendRegister(3025, 3);
  display.clearDisplay();
  readDisplayAndSendRegister(3027, 4);
  display.clearDisplay();
  readDisplayAndSendRegister(3029, 5);
  display.clearDisplay();
  readDisplayAndSendRegister(3031, 6);
  display.clearDisplay();
  readDisplayAndSendRegister(3035, 7);
  display.clearDisplay();
  delay(2000);
}
