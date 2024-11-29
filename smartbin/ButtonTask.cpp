#include "ButtonTask.h"
#include <Arduino.h>

void ButtonTask::tick(){
    int currState = digitalRead(pin);// leggi la lettura del pulsante
    if((precState == HIGH) && (currState)){
        Svariable[id] = HIGH;
    }
    precState = currState;
}

ButtonTask::ButtonTask(int pin){
    this->pin = pin;
}
