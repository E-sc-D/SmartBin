#include "ButtonTask.h"
//#include "Arduino.h"

ButtonTask::ButtonTask(int pin){
    this->pin = pin;
    //pinmode input pullup, e altre robe di arduino
}

void ButtonTask::tick(){
    int currState = 1;// leggi la lettura del pulsante
    if((precState == 1) && (currState)){
        Svariable[id] = 1;
    } 
    precState = currState;
}




