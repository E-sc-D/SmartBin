#include "ButtonTask.h"
#include <Arduino.h>

void ButtonTask::tick() {
    int currState = digitalRead(this->pin);   // leggi la lettura del pulsante
    if((this->precState == HIGH) && (currState == LOW)) {
        Svariable[this->id] = HIGH;
    } else {
        Svariable[this->id] = LOW;
    }
    this->precState = currState;
}

ButtonTask::ButtonTask(int pin) {
    this->pin = pin;
    this->precState = LOW;
}
