


#include <ModbusRTU.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
SoftwareSerial ModbusSerial(1);  // Use UART1 for Modbus communication

ModbusRTU mb;

// Parameters for RS485
#define RS485_TX_PIN 17  // TX pin of ESP32
#define RS485_RX_PIN 16  // RX pin of ESP32
#define RS485_DE_RE_PIN 4 // Pin to control DE/RE for RS485

// Modbus device ID and communication parameters
const uint8_t MODBUS_ID = 1;
const long BAUD_RATE = 19200;
const int PARITY = SERIAL_8E1;  // 8 data bits, even parity, 1 stop bit

// Register addresses to read (same as your example)
uint16_t REGISTER_ADDRESSES[] = {3817, 3833, 3849};
const int NUM_REGISTERS = sizeof(REGISTER_ADDRESSES) / sizeof(REGISTER_ADDRESSES[0]);

// Callback function for Modbus request
bool cbRead(Modbus::ResultCode event, uint16_t transactionId, void *data) {
    if (event != Modbus::EX_SUCCESS) {
        Serial.printf("Error: %02X\n", event); // Print error code if there's an issue
    }
    return true;
}

void setup() {
    // Initialize serial communication for debugging
    Serial.begin(115200);

    // Initialize RS485 communication
    ModbusSerial.begin(BAUD_RATE, PARITY, RS485_RX_PIN, RS485_TX_PIN); // RX, TX
    mb.begin(&ModbusSerial, RS485_DE_RE_PIN);  // DE/RE pin to control the RS485 transceiver
    mb.master();  // Set ESP32 as Modbus master
}

void loop() {
    for (int i = 0; i < NUM_REGISTERS; i++) {
        // Read two registers (since float takes two 16-bit registers)
        if (!mb.readHreg(MODBUS_ID, REGISTER_ADDRESSES[i], (uint16_t*) &mb.Hreg(0), 2, cbRead)) {
            Serial.println("Failed to send Modbus request!");
            delay(1000);  // Retry after delay
            continue;
        }

        // Wait for response
        while (mb.slave()) {
            mb.task();  // Process Modbus events
        }

        // Convert the two 16-bit registers to a float
        uint16_t reg1 = mb.Hreg(0);   // First register
        uint16_t reg2 = mb.Hreg(1);   // Second register

        // Convert registers into a float
        uint32_t value = ((uint32_t)reg1 << 16) | reg2;
        float float_value = *(float*)&value;

        // Print the float value
        Serial.printf("Float value at register %d: %f\n", REGISTER_ADDRESSES[i], float_value);
    }

    delay(2000);  // Delay between readings
}
