#include "BinTask.h"
#include "Arduino.h"

void BinTask::init(int period, int pin, int idTemperature, int idWaste, int idButton) {
    Task::init(period, pin);
    this->idTemperature = idTemperature;
    this->idWaste = idWaste;
    this->idButton = idButton;
    this->state = STATUS_CLOSED;
}

void BinTask::tick() {
    switch (state)
    {
        case STATUS_CLOSED:
            if (Svariable[idWaste]) {
                state = STATUS_FULL;
            } else if (Svariable[idTemperature]) {
                state = STATUS_HOT; 
            } else if (Svariable[idButton]) {
                state = STATUS_OPENED;
                open();
            }
            break;
        case STATUS_OPENED:
            if (Svariable[idWaste] || Svariable[idTemperature] || !Svariable[idButton]) {
                state = STATUS_CLOSED;
                close();
            }
            break;
        case STATUS_FULL:
            if (Svariable[idTemperature]) {
                state = STATUS_HOT;
            }
            break;
        case STATUS_HOT:
            //Attendere GUI
            break;
        default:
            break;
    }
}

void BinTask::open() {

}

void BinTask::close() {
    
}
