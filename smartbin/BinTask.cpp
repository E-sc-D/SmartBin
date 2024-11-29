#include "BinTask.h"
#include <Arduino.h>

 BinTask::BinTask( int idTemperature, int idWaste, int idButtonOpen,int idButtonClose) {
    this->idTemperature = idTemperature;
    this->idWaste = idWaste;
    this->idButtonOpen = idButtonOpen;
    this->idButtonClose = idButtonClose;
    this->state = STATUS_CLOSED;
    this->door.attach(this->pin);
}

void BinTask::tick() {
    switch (state)
    {
        case STATUS_CLOSED:
            if (Svariable[idWaste]) {
                state = STATUS_FULL;
            } else if (Svariable[idTemperature]) {
                state = STATUS_HOT; 
            } else if (Svariable[idButtonOpen]) {
                state = STATUS_OPENED;
                open();
            }
            break;
        case STATUS_OPENED:
            if (Svariable[idWaste] || Svariable[idTemperature] || !Svariable[idButtonClose]) {
                state = STATUS_CLOSED;
                close();
            }
            break;
        case STATUS_FULL:
            if (Svariable[idTemperature]) {
                state = STATUS_HOT;
            }
            //if segnale inviato da arduino torna chiuso
            break;
        case STATUS_HOT:
            //Attendere GUI
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
    this->door.write(-90);
}
