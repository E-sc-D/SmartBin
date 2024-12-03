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
        if (command == 'E' && Svariable[idBin] == 7) {
            Svariable[id] = 1;
        } else if (command == 'R' && Svariable[idBin] == 13) {
            Svariable[id] = 2;
        } else {
            Svariable[id] = 0;
        }
    }
}

void GUITask::printTempAndWaste() {
    Serial.println(Svariable[idWaste] > 100 ? 0 : 100 - Svariable[idWaste]);
    Serial.println(Svariable[idTemperature] % 2 != 0 ? (Svariable[idTemperature] - 1) / 100 : Svariable[idTemperature] / 100);
}