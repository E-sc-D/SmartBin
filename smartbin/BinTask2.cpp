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
    fsm.add(timedTransitions, (sizeof(timedTransitions) / sizeof(TimedTransition)));
    fsm.setInitialState(&s[0]);
}

void BinTask2::tick() {
    fsm.run();

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

void BinTask2::closed_on() {

}

void BinTask2::closed_on_enter() {

}

void BinTask2::closed_on_exit() {

}

void BinTask2::opened_on() {

}

void BinTask2::opened_on_enter() {

}

void BinTask2::opened_on_exit() {

}

void BinTask2::opened_trans_closed() {

}

void BinTask2::full_on() {

}

void BinTask2::full_on_enter() {

}

void BinTask2::full_on_exit() {

}

void BinTask2::emptying_on() {

}

void BinTask2::emptying_on_enter() {

}

void BinTask2::emptying_on_exit() {

}

void BinTask2::hot_on() {

}

void BinTask2::hot_on_enter() {

}

void BinTask2::hot_on_exit() {

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
