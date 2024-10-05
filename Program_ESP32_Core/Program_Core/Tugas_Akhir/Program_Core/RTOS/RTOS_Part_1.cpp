#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

int count1 = 0;
int count2 = 0;

void task1(void *parameters){
    for(;;){
        Serial.print("Task 1 Counter");
        Serial.println(count1++);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void task2(void *parameters){
    for(;;){
        Serial.print("Task 2 Counter");
        Serial.println(count2++);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


void setup(){
    Serial.begin(9600);
    xTaskCreate(
        task1,
        "Task 1",
        1000,
        NULL,
        1, 
        NULL
    );

    xTaskCreate(
        task2,
        "Task 2",
        1000,
        NULL,
        1, 
        NULL
    );
}

void loop(){}