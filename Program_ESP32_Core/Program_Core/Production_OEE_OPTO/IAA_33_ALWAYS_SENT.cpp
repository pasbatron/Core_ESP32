#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// Pin definitions
const int buttonPinA2 = 32;
const int buttonPinA3 = 33;
const int buttonPinA4 = 25;
const int buttonPinA5 = 26;
const int buttonPinA13 = 27;
const int buttonPinA14 = 14;
const int buttonPinA15 = 12;

// Data strings for button actions
String dataOnA2 = "*iaa33on_mcfault#";
String dataOnA3 = "*iaa33on_fullwork#";
String dataOnA4 = "*iaa33on_qualitycheck#";
String dataOnA5 = "*iaa33on_toolchange#";
String dataOnA13 = "*iaa33on_arm#";
String dataOnA14 = "*iaa33on_roller#";
String dataOnA15 = "*iaa33on_pin#";

String dataOffA2 = "*iaa33off_mcfault#";
String dataOffA3 = "*iaa33off_fullwork#";
String dataOffA4 = "*iaa33off_qualitycheck#";
String dataOffA5 = "*iaa33off_toolchange#";
String dataOffA13 = "*iaa33off_arm#";
String dataOffA14 = "*iaa33off_roller#";
String dataOffA15 = "*iaa33off_pin#";

// SoftwareSerial for LoRa
SoftwareSerial mySerialLora(16, 17); // TX, RX
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button state variables
bool lastStateA2 = LOW;
bool lastStateA3 = LOW;
bool lastStateA4 = LOW;
bool lastStateA5 = LOW;
bool lastStateA13 = LOW;
bool lastStateA14 = LOW;
bool lastStateA15 = LOW;

// Timing variables
unsigned long previousMillis = 0;
const long interval = 1500; // Interval at which to send data (1.5 seconds)

// Debounce timing
const long debounceDelay = 200; // 200 ms debounce delay
unsigned long lastDebounceTimeA2 = 0;
unsigned long lastDebounceTimeA3 = 0;
unsigned long lastDebounceTimeA4 = 0;
unsigned long lastDebounceTimeA5 = 0;
unsigned long lastDebounceTimeA13 = 0;
unsigned long lastDebounceTimeA14 = 0;
unsigned long lastDebounceTimeA15 = 0;

void setup() {
    Serial.begin(9600);
    mySerialLora.begin(9600);
    if (!display.begin(0x3C)) {
        while (true);
    }
    delay(200);

    // Initialize button pins
    pinMode(buttonPinA2, INPUT_PULLUP);
    pinMode(buttonPinA3, INPUT_PULLUP);
    pinMode(buttonPinA4, INPUT_PULLUP);
    pinMode(buttonPinA5, INPUT_PULLUP);
    pinMode(buttonPinA13, INPUT_PULLUP);
    pinMode(buttonPinA14, INPUT_PULLUP);
    pinMode(buttonPinA15, INPUT_PULLUP);
}

void loop() {
    unsigned long currentMillis = millis();

    // Check button states every 1.5 seconds
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        // Read and send button states with debounce
        sendButtonState(buttonPinA2, lastStateA2, dataOnA2, dataOffA2, lastDebounceTimeA2);
        sendButtonState(buttonPinA3, lastStateA3, dataOnA3, dataOffA3, lastDebounceTimeA3);
        sendButtonState(buttonPinA4, lastStateA4, dataOnA4, dataOffA4, lastDebounceTimeA4);
        sendButtonState(buttonPinA5, lastStateA5, dataOnA5, dataOffA5, lastDebounceTimeA5);
        sendButtonState(buttonPinA13, lastStateA13, dataOnA13, dataOffA13, lastDebounceTimeA13);
        sendButtonState(buttonPinA14, lastStateA14, dataOnA14, dataOffA14, lastDebounceTimeA14);
        sendButtonState(buttonPinA15, lastStateA15, dataOnA15, dataOffA15, lastDebounceTimeA15);
    }

    // Check for incoming LoRa messages
    if (mySerialLora.available() > 1) {
        String input = mySerialLora.readString();
        Serial.println(input);
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(20, 20);
        display.println("Data : ");
        display.setCursor(20, 40);
        display.println(input);
        display.display();
        delay(1100);
    }
}

void sendButtonState(int buttonPin, bool &lastState, String dataOn, String dataOff, unsigned long &lastDebounceTime) {
    bool currentState = digitalRead(buttonPin);
    if (currentState != lastState) {
        lastDebounceTime = millis(); // Reset the debounce timer
    }

    // Check if the debounce time has passed
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (currentState != lastState) {
            if (currentState == LOW) { // Button pressed
                mySerialLora.println(dataOn);
            } else { // Button released
                mySerialLora.println(dataOff);
            }
            lastState = currentState; // Update the last state
        }
    }
}
