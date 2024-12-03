#include "GUITask.h"
#include <Arduino.h>

GUITask::GUITask(int idWaste, int idTemperature, int idBin) {
    this->idWaste = idWaste;
    this->idTemperature = idTemperature;
    this->idBin = idBin;
}

void GUITask::tick() {
    printTempAndWaste();

    if (Serial.available()) {
        char command = Serial.read();
        if (command == 'E' && Svariable[this->idBin] == 7) {
            Svariable[this->id] = 1;
        } else if (command == 'R' && Svariable[this->idBin] == 13) {
            Svariable[this->id] = 2;
        } else {
            Svariable[this->id] = 0;
        }
    }
}

void GUITask::printTempAndWaste() {
    Serial.println(Svariable[this->idWaste] > 100 ? 0 : 100 - Svariable[this->idWaste]);
    Serial.println(Svariable[this->idTemperature] % 2 != 0 ? (Svariable[this->idTemperature] - 1) / 100 : Svariable[this->idTemperature] / 100);
}