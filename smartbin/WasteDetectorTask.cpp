#include "WasteDetectorTask.h"
#include <Arduino.h>

WasteDetectorTask::WasteDetectorTask(int trigPin, int echoPin, int idBin){ //il bin deve dirgli se è aperto o no
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->idBin = idBin;
    //pinmode e altri config di arduino
}
float WasteDetectorTask::BinUsable() {
	digitalWrite(this->trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(this->trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(this->trigPin, LOW);
	//noInterrupts();
	float d = pulseIn(this->echoPin, HIGH, 23529.4);
    return (d / 58.8235);
	//interrupts();
}

void WasteDetectorTask::tick(){
    //se il bidone è aperto
    if(Svariable[idBin] == 1){
      Svariable[id] = (int)BinUsable(); //misura il livello di scarti via arduino
    }
}