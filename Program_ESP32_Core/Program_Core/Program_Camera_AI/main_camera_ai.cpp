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


    if (! rtc.begin()) {
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

void loop() {
    DateTime now = rtc.now();
    if (Serial.available() > 0) {
        String receivedData = Serial.readStringUntil('\n');
        if(receivedData == "tuanku"){
          Serial.print("Received from PC: ");
          Serial.println(receivedData);

          mySerialLora.println(receivedData);  
          myDFPlayer.play(0);
          myDFPlayer.read(); 
      
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(SH110X_WHITE);
          display.setCursor(10, 20);
          display.println("Data : ");
          display.setCursor(10, 40);
          display.println(String(receivedData));
          display.display();
          
        }if(receivedData == "1"){
          Serial.print("Received from PC: ");
          Serial.println(receivedData);

          mySerialLora.println(receivedData);  
          myDFPlayer.play(1);
          myDFPlayer.read(); 
      
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(SH110X_WHITE);
          display.setCursor(10, 20);
          display.println("Data : ");
          display.setCursor(10, 40);
          display.println(String(receivedData));
          display.display();
          
        }
        if(receivedData == "2"){
          Serial.print("Received from PC: ");
          Serial.println(receivedData);

          mySerialLora.println(receivedData);  
          myDFPlayer.play(2);
          myDFPlayer.read(); 
      
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(SH110X_WHITE);
          display.setCursor(10, 20);
          display.println("Data : ");
          display.setCursor(10, 40);
          display.println(String(receivedData));
          display.display();
          
        }if(receivedData == "3"){
          Serial.print("Received from PC: ");
          Serial.println(receivedData);

          mySerialLora.println(receivedData);  
          myDFPlayer.play(3);
          myDFPlayer.read(); 
      
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(SH110X_WHITE);
          display.setCursor(10, 20);
          display.println("Data : ");
          display.setCursor(10, 40);
          display.println(String(receivedData));
          display.display();
          
        }if(receivedData == "4"){
          Serial.print("Received from PC: ");
          Serial.println(receivedData);

          mySerialLora.println(receivedData);  
          myDFPlayer.play(4);
          myDFPlayer.read(); 
      
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(SH110X_WHITE);
          display.setCursor(10, 20);
          display.println("Data : ");
          display.setCursor(10, 40);
          display.println(String(receivedData));
          display.display();
          
        }if(receivedData == "5"){
          Serial.print("Received from PC: ");
          Serial.println(receivedData);

          mySerialLora.println(receivedData);  
          myDFPlayer.play(5);
          myDFPlayer.read(); 
      
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(SH110X_WHITE);
          display.setCursor(10, 20);
          display.println("Data : ");
          display.setCursor(10, 40);
          display.println(String(receivedData));
          display.display();
          
        }if(receivedData == "6"){
          Serial.print("Received from PC: ");
          Serial.println(receivedData);

          mySerialLora.println(receivedData);  
          myDFPlayer.play(6);
          myDFPlayer.read(); 
      
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(SH110X_WHITE);
          display.setCursor(10, 20);
          display.println("Data : ");
          display.setCursor(10, 40);
          display.println(String(receivedData));
          display.display();
          
        }if(receivedData == "7"){
          Serial.print("Received from PC: ");
          Serial.println(receivedData);

          mySerialLora.println(receivedData);  
          myDFPlayer.play(7);
          myDFPlayer.read(); 
      
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(SH110X_WHITE);
          display.setCursor(10, 20);
          display.println("Data : ");
          display.setCursor(10, 40);
          display.println(String(receivedData));
          display.display();
          
        }if(receivedData == "8"){
          Serial.print("Received from PC: ");
          Serial.println(receivedData);

          mySerialLora.println(receivedData);  
          myDFPlayer.play(8);
          myDFPlayer.read(); 
      
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(SH110X_WHITE);
          display.setCursor(10, 20);
          display.println("Data : ");
          display.setCursor(10, 40);
          display.println(String(receivedData));
          display.display();
          
        }
        if(receivedData == "9"){
          Serial.print("Received from PC: ");
          Serial.println(receivedData);

          mySerialLora.println(receivedData);  
          myDFPlayer.play(9);
          myDFPlayer.read(); 
      
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(SH110X_WHITE);
          display.setCursor(10, 20);
          display.println("Data : ");
          display.setCursor(10, 40);
          display.println(String(receivedData));
          display.display();
          
        }
        if(receivedData == "10"){
          Serial.print("Received from PC: ");
          Serial.println(receivedData);

          mySerialLora.println(receivedData);  
          myDFPlayer.play(10);
          myDFPlayer.read(); 
      
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(SH110X_WHITE);
          display.setCursor(10, 20);
          display.println("Data : ");
          display.setCursor(10, 40);
          display.println(String(receivedData));
          display.display();
          
        }
        
        
        else{
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
}
