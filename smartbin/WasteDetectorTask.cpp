#include "WasteDetectorTask.h"
#include <Arduino.h>

WasteDetectorTask::WasteDetectorTask(int trigPin, int echoPin, int idBin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->idBin = idBin;
}

void WasteDetectorTask::init(int period, int id) {
    Task::init(period, id);
    Svariable[id] = 100;
}

float WasteDetectorTask::BinUsable() {
	digitalWrite(this->trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(this->trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(this->trigPin, LOW);

	float d = pulseIn(this->echoPin, HIGH, 23529.4);

  return (d / 58.8235);
}

void WasteDetectorTask::tick() {
    //se il bidone è aperto, misura il livello di scarti via arduino
    if(Svariable[idBin] == 4){
        Svariable[id] = (int)BinUsable();
    }
}