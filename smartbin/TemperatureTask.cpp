#include "TemperatureTask.h"
#include "ButtonTask.h"
#include <Arduino.h>

TemperatureTask::TemperatureTask(int pin){
    this->pin = pin;
}

void TemperatureTask::tick(){
    //misura la temperatura via arduino
    Svariable[id] = (int)((analogRead(pin) * 0.00488 ) / 0.01);
    Serial.print("temp ");
    Serial.println(id);
}