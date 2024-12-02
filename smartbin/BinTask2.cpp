#include "BinTask2.h"
#include <Arduino.h>


#define MIN_FREE_SPACE 1 //distanza minima in cm tra il sonar e il contenuto del bidone 
#define MAX_TEMP 60

BinTask2::BinTask2( int idTemperature, int idWaste, int idButtonOpen,int idButtonClose,int pin) {
    this->idTemperature = idTemperature;
    this->idWaste = idWaste;
    this->idButtonOpen = idButtonOpen;
    this->idButtonClose = idButtonClose;
    this->state = STATUS_CLOSED;
    this->pin = pin;
    this->door.attach(this->pin);
    this->timeReference = 0;
    Serial.println("here");
    //the led green starts on
    //lcd shows text for closed state
}

void BinTask2::init(int period, int id) {
    Task::init(period, id);
    fsm.add(timedTransitions, (sizeof(timedTransitions) / sizeof(transition)));
    fsm.setInitialState(&s[0]);
}

void BinTask2::tick() {
  Serial.println(millis());
  Serial.println(state);

    
    switch (state)
    {
        case STATUS_CLOSED:
            if (Svariable[idWaste] < MIN_FREE_SPACE) {  
                state = STATUS_FULL;
                //write containter full
            } else if (Svariable[idTemperature] > MAX_TEMP) {
                state = STATUS_HOT; 
            } else if (Svariable[idButtonOpen]) {
                state = STATUS_OPENED;
                timeReference = millis();//when the bin gets open, we need to count the time
                //write in LCD
                open();
            }
            break;

        case STATUS_OPENED:
            //check time, the bin closes after T time, 
            if (Svariable[idWaste] > MIN_FREE_SPACE ||
                    Svariable[idTemperature] > MAX_TEMP || 
                    Svariable[idButtonClose] || 
                    elapsed(5000)) {
                state = STATUS_CLOSED;
                //change text and wait for T2
                close();
                wait(3000);
            }
            break;

        case STATUS_FULL:
            if (Svariable[idTemperature] > MAX_TEMP) {
                state = STATUS_HOT;
            }
            //if segnale inviato da arduino si apre al contrario per T3 e poi si chiude
            break;

        case STATUS_EMPTYING:
            //il servo si apre al contrario
            //dopo T4 si richiude
            empty();
            wait(4);
            close();
            state = STATUS_CLOSED;
            break; 

        case STATUS_HOT:
            //Attendere GUI
            break;

        case STATUS_WAITING:
            if(elapsed(amountOfWait)){
                state = prevState;
            }
            break;

        default:
            break;
    }

    Svariable[idButtonOpen] = 0;//pulisco gli stati ogni volta
    Svariable[idButtonClose] = 0;
    Svariable[id] = state;
}

void BinTask2::open() {
    this->door.write(90);
    Serial.println("open");
}

void BinTask2::close() {
    this->door.write(0);
    Serial.println("close");
}

void BinTask2::empty(){
    this->door.write(-90);
    Serial.println("empty");
}

void BinTask2::wait(unsigned long amountOfWait){ 
    prevState = state;
    state = STATUS_WAITING;
    this->amountOfWait = amountOfWait;
    timeReference = millis();
}

bool BinTask2::elapsed(unsigned long time){
    return (millis() - timeReference >= time);      
}