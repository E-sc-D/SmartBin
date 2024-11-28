#include "ButtonTask.h"
//#include "Arduino.h"

void ButtonTask::tick(){
    int currState = 1;// leggi la lettura del pulsante
    if((precState == 1) && (currState)){
        Svariable[id] = 1;
    }
    precState = currState;
}
