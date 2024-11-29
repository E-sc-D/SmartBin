#include "WasteDetectorTask.h"
#include <Arduino.h>
#define MIN_FREE_SPACE 5 //distanza minima in cm tra il sonar e il contenuto del bidone 

WasteDetectorTask::WasteDetectorTask(int trigPin, int echoPin, int binid){ //il bin deve dirgli se è aperto o no
    this->trigPin = trigPin;
    this->echoPin = echoPin;

    //pinmode e altri config di arduino
}
bool WasteDetectorTask::BinUsable() {
	/* digitalWrite(this->trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(this->trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(this->trigPin, LOW);
	//noInterrupts();
	float d = pulseIn(this->echoPin, HIGH, 23529.4);
    bool usable = true;
    if ((d / 58.8235) <= MIN_FREE_SPACE){
        usable = false;
    }
	//interrupts();
	return usable; */
    return true;
}

void WasteDetectorTask::tick(){
    if(Svariable[idBin]==1){//se il bidone è aperto
        Svariable[id] = 1;//misura il livello di scarti via arduino
    }
    
}