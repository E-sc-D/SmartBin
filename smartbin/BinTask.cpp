#include "BinTask.h"
#include <Arduino.h>

 BinTask::BinTask( int idTemperature, int idWaste, int idButtonOpen,int idButtonClose) {
    this->idTemperature = idTemperature;
    this->idWaste = idWaste;
    this->idButtonOpen = idButtonOpen;
    this->idButtonClose = idButtonClose;
    this->state = STATUS_CLOSED;
    this->door.attach(this->pin);
    //the led green starts on
    //lcd shows text for closed state
}

void BinTask::tick() {
   Serial.println(state);
    switch (state)
    {
        case STATUS_CLOSED:
            if (Svariable[idWaste]) {
                state = STATUS_FULL;
                //write containter full
            } else if (Svariable[idTemperature]) {
                state = STATUS_HOT; 
            } else if (Svariable[idButtonOpen]) {
                state = STATUS_OPENED;
                timeReference = millis();//when the bin gets open, we need to count the time
                //write in LCD
                open();
            }
            break;

        case STATUS_OPENED:
            //check time, the bin closes after T time, 
            if (Svariable[idWaste] || Svariable[idTemperature] || 
                !Svariable[idButtonClose]|| elapsed(1)) {
                state = STATUS_CLOSED;
                //change text and wait for T2
                wait(1);
                close();
            }
            break;

        case STATUS_FULL:
            if (Svariable[idTemperature]) {
                state = STATUS_HOT;
            }
            //if segnale inviato da arduino si apre al contrario per T3 e poi si chiude
            break;

        case STATUS_EMPTYING:
            //il servo si apre al contrario
            //dopo T4 si richiude
            empty();
            wait(4);
            close();
            state = STATUS_CLOSED;
            break; 

        case STATUS_HOT:
            //Attendere GUI
            break;

        case STATUS_WAITING:
            if(elapsed(1)){
                state = prevState;
            }
            break;

        default:
            break;
    }
    Svariable[idButtonOpen] = 0;//pulisco gli stati ogni volta
    Svariable[idButtonClose] = 0;
    Svariable[id] = state;
}

void BinTask::open() {
    this->door.write(90);
}

void BinTask::close() {
    this->door.write(0);
}

void BinTask::empty(){
    this->door.write(-90);
}

void BinTask::wait(int amountOfWait){ 
    prevState = state;
    state = STATUS_WAITING;
    this->amountOfWait = amountOfWait;
    timeReference = millis();
}

bool BinTask::elapsed(int time){
    return (millis() - timeReference >= amountOfWait);
                
}