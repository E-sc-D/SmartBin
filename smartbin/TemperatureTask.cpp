#include "TemperatureTask.h"
#include "ButtonTask.h"

TemperatureTask::TemperatureTask(int pin){
    this->pin = pin;
    //pinmode e altri config di arduino
}

void TemperatureTask::tick(){
    Svariable[id] = 1;//misura la temperatura via arduino
}