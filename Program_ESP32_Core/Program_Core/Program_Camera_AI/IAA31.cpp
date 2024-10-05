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
SoftwareSerial mySerialLora(txPinLora, rxPinLora); //TX, RX
SoftwareSerial dfplayer(rxPinDfplayer, txPinDfplayer);
DFRobotDFPlayerMini myDFPlayer;
RTC_DS3231 rtc;

char days[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

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
        while (1);
    }
    if (!display.begin(0x3C)) {
        while (true);
    }

    rtc.adjust(DateTime(__DATE__, __TIME__));
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
    myDFPlayer.play(dfPlayerTrack);
    myDFPlayer.read();

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(10, 20);
    display.println("Data : ");
    display.setCursor(10, 40);
    display.println(data);
    display.display();
}

void loop() {
    if (Serial.available() > 0) {
        String receivedData = Serial.readStringUntil('\n');
        int trackNumber = receivedData.toInt();

        switch (trackNumber) {
            case 0:
                if (receivedData == "tuanku") handleReceivedData(receivedData, 0);
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                handleReceivedData(receivedData, trackNumber);
                break;
            default:
                display.clearDisplay();
                display.setTextSize(1);
                display.setTextColor(SH110X_WHITE);
                display.setCursor(10, 20);
                display.println("Data : ");
                display.setCursor(10, 40);
                display.println("Okw");
                display.display();
                delay(1000);
                break;
        }
    }
}
