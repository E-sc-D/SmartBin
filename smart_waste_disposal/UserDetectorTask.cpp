#include "UserDetectorTask.h"
#include <Arduino.h>

bool isSleeping = false;

UserDetectorTask::UserDetectorTask(int pin, int idBin) {
    this->pin = pin;
    this->idBin = idBin;
    this->state = STATE_1;
    this->prevRange = LOW;
    attachInterrupt(digitalPinToInterrupt(this->pin), wakeUp, RISING);
}

void UserDetectorTask::tick() {
    isUserInRange();
}

void UserDetectorTask::isUserInRange() {
    int range = digitalRead(this->pin);

    switch (this->state)
    {
        case STATE_1:
            if (range == LOW && this->prevRange == HIGH && Svariable[this->idBin] == 1) {
                this->timeReference = millis();
                this->state = STATE_2;
            }
            Svariable[this->id] = 0;
            break;

        case STATE_2:
            if (range == LOW && this->prevRange == LOW && (millis() - this->timeReference >= TSLEEP)) {
                this->state = STATE_3;
                isSleeping = true;
                Svariable[this->id] = 1;
            } else if (range == LOW && this->prevRange == LOW && !(millis() - this->timeReference >= TSLEEP)) {
                Svariable[this->id] = 0;
            } else if (range == HIGH && this->prevRange == LOW) {
                this->state = STATE_1;
                Svariable[this->id] = 0;
            }
            break;

        case STATE_3:
            if (isSleeping == false) {
                this->state = STATE_1;
                Svariable[this->id] = 0;
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
