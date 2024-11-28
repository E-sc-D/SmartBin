#include "WasteDetectorTask.h"
#include "Arduino.h"
#define MIN_FREE_SPACE 5 //distanza minima in cm tra il sonar e il contenuto del bidone 

WasteDetectorTask::WasteDetectorTask(int trigPin, int echoPin, int n){
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->n = n;
    //pinmode e altri config di arduino
}
WasteDetectorTask::BinUsable(int n) {
	digitalWrite(this->trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(this->trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(this->trigPin, LOW);
	noInterrupts();
	float d = pulseIn(this->echoPin, HIGH, 23529.4);
    bool usable = true;
    if ((d / 58.8235) <= MIN_FREE_SPACE){
        usable = false
    }
	interrupts();
	return usable;
}

void WasteDetectorTask::tick(){
    Svariable[id] = 1;//misura la temperatura via arduino
}