#include "TemperatureTask.h"
#include <Arduino.h>

TemperatureTask::TemperatureTask(int pin) {
  this->pin = pin;
  this->state = STATE_1;
  this->prevTemp = 0;
}

void TemperatureTask::tick() {
  //misura la temperatura via arduino
  Svariable[this->id] = isTooHot();
}

int TemperatureTask::isTooHot() {
  int temp = (int)((analogRead(this->pin) * 0.00488 ) / 0.01);

  switch (this->state) {
    case STATE_1:
      if (temp > MAX_TEMP) {
        this->timeReference = millis();
        this->state = STATE_2;
      }
      temp *= 100;
      break;
    case STATE_2:
      if (temp > MAX_TEMP && this->prevTemp > MAX_TEMP && (millis() - this->timeReference >= MAXTEMPTIME)) {
        temp *= 100;
        temp += 1;
        this->state = STATE_3;
      } else if (!(temp > MAX_TEMP && this->prevTemp > MAX_TEMP)) {
        temp *= 100;
        this->state = STATE_1;
      } else {
        temp *= 100;
      }
      break;
    case STATE_3:
      if (temp > MAX_TEMP && this->prevTemp > MAX_TEMP) {
        temp *= 100;
        temp += 1;
      } else {
        temp *= 100;
        this->state = STATE_1;
      }
      break;
  }
  this->prevTemp = temp;

  return temp;
}
