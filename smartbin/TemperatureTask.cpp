#include "TemperatureTask.h"
#include <Arduino.h>

TemperatureTask::TemperatureTask(int pin) {
    this->pin = pin;
    this->prevTemp = 0;
}

void TemperatureTask::tick() {
    //misura la temperatura via arduino
    Svariable[id] = isTooHot();
}

int TemperatureTask::isTooHot() {
    int temp = (int)((analogRead(pin) * 0.00488 ) / 0.01);

    switch (state) {
      case 0:
        if (temp > MAX_TEMP) {
          timeReference = millis();
          state = 1;
        }
        temp *= 100;
        break;
      case 1:
        if (temp > MAX_TEMP && prevTemp > MAX_TEMP && (millis() - timeReference >= MAXTEMPTIME)) {
          temp *= 100;
          temp += 1;
          state = 2;
        } else if (!(temp > MAX_TEMP && prevTemp > MAX_TEMP)) {
          temp *= 100;
          state = 0;
        } else {
          temp *= 100;
        }
        break;
      case 2:
        if (temp > MAX_TEMP && prevTemp > MAX_TEMP) {
          temp *= 100;
          temp += 1;
        } else {
          temp *= 100;
          state = 0;
        }
        break;
    }
    prevTemp = temp;

    return temp;
}
