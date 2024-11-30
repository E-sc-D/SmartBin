#include "ButtonTask.h"
#include <Arduino.h>

void ButtonTask::tick(){
    int currState = digitalRead(pin);// leggi la lettura del pulsante
    if((precState == HIGH) && (currState == LOW)){
        Svariable[id] = HIGH;
    } else {
      Svariable[id] = LOW;
    }
    precState = currState;
}

ButtonTask::ButtonTask(int pin){
    this->pin = pin;
    precState = HIGH;
}
