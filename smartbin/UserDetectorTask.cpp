#include "UserDetectorTask.h"
#include <Arduino.h>

bool isSleeping = false;

UserDetectorTask::UserDetectorTask(int pin, int idBin) {
    this->pin = pin;
    this->idBin = idBin;
    this->state = 0;
    this->prevRange = LOW;
    attachInterrupt(digitalPinToInterrupt(pin), wakeUp, RISING);
}

void UserDetectorTask::tick() {
    isUserInRange();
}

void UserDetectorTask::isUserInRange() {
    int range = digitalRead(this->pin);

    switch (this->state)
    {
        case 0:
            if (range == LOW && this->prevRange == HIGH && Svariable[idBin] == 1) {
                this->timeReference = millis();
                this->state = 1;
            }
            Svariable[id] = 0;
            break;

        case 1:
            if (range == LOW && this->prevRange == LOW && (millis() - this->timeReference >= TSLEEP)) {
                this->state = 2;
                isSleeping = true;
                Svariable[id] = 1;
            } else if (range == LOW && this->prevRange == LOW && !(millis() - this->timeReference >= TSLEEP)) {
                Svariable[id] = 0;
            } else if (range == HIGH && this->prevRange == LOW) {
                this->state = 0;
                Svariable[id] = 0;
            }
            break;

        case 2:
            if (isSleeping == false) {
                this->state = 0;
                Svariable[id] = 0;
            }
            break;
        
        default:
            break;
    }

    this->prevRange = range;
}

void UserDetectorTask::wakeUp() {
    isSleeping = false;
}
