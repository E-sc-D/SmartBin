#include "BinTask.h"
#include <Arduino.h>

#define MIN_FREE_SPACE 1 //distanza minima in cm tra il sonar e il contenuto del bidone 
#define MAX_TEMP 60


BinTask::BinTask(int idTemperature, int idWaste, int idButtonOpen, int idButtonClose, int pin, int greenLedPin, int redLedPin) {
    this->pin = pin;
    this->greenLedPin = greenLedPin;
    this->redLedPin = redLedPin;
    this->idTemperature = idTemperature;
    this->idWaste = idWaste;
    this->idButtonOpen = idButtonOpen;
    this->idButtonClose = idButtonClose;
    this->state = STATUS_CLOSED;
    this->timeReference = 0;
    this->door.attach(this->pin);
    //the led green starts on
    //lcd shows text for closed state
}

void BinTask::tick() {
    switch (state)
    {
        case STATUS_CLOSED:
            if (Svariable[idWaste] < MIN_FREE_SPACE) {  
                state = STATUS_FULL;
                //write containter full
            } else if (Svariable[idTemperature] > MAX_TEMP) {
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
                    Svariable[idTemperature] > MAX_TEMP || 
                    Svariable[idButtonClose] || 
                    elapsed(5000)) {
                state = STATUS_CLOSED;
                //change text and wait for T2
                close();
                //wait(3000);
            }
            break;

        case STATUS_FULL:
            if (Svariable[idTemperature] > MAX_TEMP) {
                state = STATUS_HOT;
            }
            //if segnale inviato da arduino si apre al contrario per T3 e poi si chiude
            break;

        case STATUS_EMPTYING:
            //il servo si apre al contrario
            //dopo T4 si richiude
            empty();
            //wait(4);
            close();
            state = STATUS_CLOSED;
            break; 

        case STATUS_HOT:
            //Attendere GUI
            break;

        case STATUS_WAITING:
            /*if(elapsed(amountOfWait)){
                state = prevState;
            }*/
            break;

        default:
            break;
    }

    Svariable[idButtonOpen] = 0;//pulisco gli stati ogni volta
    Svariable[idButtonClose] = 0;
    Svariable[id] = state;
    Serial.println(Svariable[id]);
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

bool BinTask::elapsed(unsigned long time){
    return (millis() - timeReference >= time);
}
