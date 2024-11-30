#include "TemperatureTask.h"
#include "ButtonTask.h"
#include <Arduino.h>

TemperatureTask::TemperatureTask(int pin){
    this->pin = pin;
    //pinmode e altri config di arduino
}

void TemperatureTask::tick(){
   Svariable[id] = (int)((analogRead(pin) * 0.00488 ) / 0.01);//misura la temperatura via arduino
}