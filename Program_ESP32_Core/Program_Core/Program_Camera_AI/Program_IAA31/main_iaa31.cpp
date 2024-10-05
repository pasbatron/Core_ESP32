#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <RTClib.h>

const byte rxPinDfplayer = 27;
const byte txPinDfplayer = 26;
const byte txPinLora = 16;
const byte rxPinLora = 17;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SoftwareSerial mySerialLora(txPinLora, rxPinLora); // TX, RX
SoftwareSerial dfplayer(rxPinDfplayer, txPinDfplayer);
DFRobotDFPlayerMini myDFPlayer;
RTC_DS3231 rtc;

bool dataReceived = false;

void setup() {
    Serial.begin(115200);
    mySerialLora.begin(9600);
    dfplayer.begin(9600);
    myDFPlayer.begin(dfplayer);
    Wire.begin();
    Serial.setTimeout(1);
    pinMode(rxPinDfplayer, INPUT);
    pinMode(txPinDfplayer, OUTPUT);

    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }
    if (!display.begin(0x3C)) {
        Serial.println("Couldn't find OLED");
        while (true);
    }

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set RTC time to compile time
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(20, 20);
    display.println("App Run!");
    display.setCursor(20, 40);
    display.println("Version 1.0");
    display.display();
    delay(5000);
}

void handleReceivedData(String data, int dfPlayerTrack) {
    Serial.print("Received from PC: ");
    Serial.println(data);

    mySerialLora.println(data);
    if (dfPlayerTrack >= 0 && dfPlayerTrack <= 10) {
        myDFPlayer.play(dfPlayerTrack);
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(10, 20);
    display.println("Data : ");
    display.setCursor(10, 40);
    display.println(data);
    display.display();
}

void sendCurrentDateTime() {
    DateTime now = rtc.now();
    String currentTime = String(now.year()) + "-" +
                         (now.month() < 10 ? "0" + String(now.month()) : now.month()) + "-" +
                         (now.day() < 10 ? "0" + String(now.day()) : now.day()) + " " +
                         (now.hour() < 10 ? "0" + String(now.hour()) : now.hour()) + ":" +
                         (now.minute() < 10 ? "0" + String(now.minute()) : now.minute()) + ":" +
                         (now.second() < 10 ? "0" + String(now.second()) : now.second());

    Serial.println(currentTime);  // Send RTC time via serial
    mySerialLora.println(currentTime);  // Optionally, send time via LoRa
}

void loop() {
    if (Serial.available() > 0) {
        String receivedData = Serial.readStringUntil('\n');
        int trackNumber = receivedData.toInt();

        dataReceived = true;
        
        if (trackNumber >= 1 && trackNumber <= 10) {
            handleReceivedData(receivedData, trackNumber);
        } else if (receivedData.equals("tuanku") && trackNumber == 0) {
            handleReceivedData(receivedData, 0);
        } else {
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(SH110X_WHITE);
            display.setCursor(10, 20);
            display.println("Data : ");
            display.setCursor(10, 40);
            display.println("Okw");
            display.display();
            delay(1000);
        }
    }

    // Only send current datetime if data was received
    if (dataReceived) {
        sendCurrentDateTime();
        dataReceived = false; // Reset flag after sending datetime
    }

    delay(1000); // Wait for 1 second before checking for new data
}
