#include "ButtonTask.h"
#include <Arduino.h>

void ButtonTask::tick(){
    int currState = digitalRead(pin);   // leggi la lettura del pulsante
    if((precState == HIGH) && (currState == LOW)){
        Svariable[id] = HIGH;
    } else {
      Svariable[id] = LOW;
    }
    precState = currState;
   Serial.print("button ");
    Serial.println(id);
}

ButtonTask::ButtonTask(int pin){
    this->pin = pin;
    precState = LOW;
}
