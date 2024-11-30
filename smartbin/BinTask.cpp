#include "BinTask.h"
#include <Arduino.h>

#define MIN_FREE_SPACE 1 //distanza minima in cm tra il sonar e il contenuto del bidone 

BinTask::BinTask( int idTemperature, int idWaste, int idButtonOpen,int idButtonClose,int pin) {
    this->idTemperature = idTemperature;
    this->idWaste = idWaste;
    this->idButtonOpen = idButtonOpen;
    this->idButtonClose = idButtonClose;
    this->state = STATUS_CLOSED;
    this->pin = pin;
    this->door.attach(this->pin);
    this->timeReference = 0;
    Serial.println("here");
    //the led green starts on
    //lcd shows text for closed state
}

void BinTask::tick() {
  Serial.println(millis());
  Serial.println(state);
    switch (state)
    {
        case STATUS_CLOSED:
            if (Svariable[idWaste] < MIN_FREE_SPACE) {
                state = STATUS_FULL;
                //write containter full
            } else if (Svariable[idTemperature] > 60) {
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
            if (Svariable[idWaste] > MIN_FREE_SPACE ||
                 Svariable[idTemperature] > 60 || 
                !Svariable[idButtonClose] || elapsed(5000)) {
                state = STATUS_CLOSED;
                //change text and wait for T2
                close();
                wait(3000);
            }
            break;

        case STATUS_FULL:
            if (Svariable[idTemperature] > 60) {
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
            if(elapsed(amountOfWait)){
                state = prevState;
            }
            break;

        default:
            break;
    }

    Svariable[idButtonOpen] = 1;//pulisco gli stati ogni volta
    Svariable[idButtonClose] = 1;
    Svariable[id] = state;
}

void BinTask::open() {
    this->door.write(90);
    Serial.println("open");
}

void BinTask::close() {
    this->door.write(0);
    Serial.println("close");
}

void BinTask::empty(){
    this->door.write(-90);
    Serial.println("empty");
}

void BinTask::wait(unsigned long amountOfWait){ 
    prevState = state;
    state = STATUS_WAITING;
    this->amountOfWait = amountOfWait;
    timeReference = millis();
}

bool BinTask::elapsed(unsigned long time){
    return (millis() - timeReference >= time);    
           
}