#include "BinTask2.h"
#include <Arduino.h>

#define MIN_FREE_SPACE 1 //distanza minima in cm tra il sonar e il contenuto del bidone 
#define MAX_TEMP 60

BinTask2::BinTask2(int idTemperature, int idWaste, int idButtonOpen, int idButtonClose, int pin, int greenLedPin, int redLedPin) {
    this->pin = pin;
    this->greenLedPin = greenLedPin;
    this->redLedPin = redLedPin;
    this->state = STATUS_CLOSED;
    this->idTemperature = idTemperature;
    this->idWaste = idWaste;
    this->idButtonOpen = idButtonOpen;
    this->idButtonClose = idButtonClose;
    this->timeReference = 0;
    this->door.attach(this->pin);
    //the led green starts on
    //lcd shows text for closed state
}

void BinTask2::init(int period, int id) {
    Task::init(period, id);
    lcd.init();
    resetScreen();
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
    state = STATUS_CLOSED;
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    close();
    resetScreen();
    lcd.setCursor(5, 1);
    lcd.print("PRESS OPEN");
    lcd.setCursor(4, 2);
    lcd.print("TO ENTER WASTE");
}

void BinTask2::closed_on_exit() {

}

void BinTask2::opened_on() {

}

void BinTask2::opened_on_enter() {
    state = STATUS_OPENED;
    open();
    resetScreen();
    lcd.setCursor(5, 1);
    lcd.print("PRESS CLOSE");
    lcd.setCursor(5, 2);
    lcd.print("WHEN DONE");
}

void BinTask2::opened_on_exit() {
    resetScreen();
    lcd.setCursor(3, 1);
    lcd.print("WASTE RECEIVED");
    //Wait T2 seconds
}

void BinTask2::opened_trans_closed() {

}

void BinTask2::full_on() {

}

void BinTask2::full_on_enter() {
    state = STATUS_FULL;
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    close();
    resetScreen();
    lcd.setCursor(3, 1);
    lcd.print("CONTAINER FULL");
}

void BinTask2::full_on_exit() {

}

void BinTask2::emptying_on() {

}

void BinTask2::emptying_on_enter() {
    state = STATUS_EMPTYING;
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    empty();
    resetScreen();
    lcd.setCursor(1, 1);
    lcd.print("EMPTYING CONTAINER");
}

void BinTask2::emptying_on_exit() {

}

void BinTask2::hot_on() {

}

void BinTask2::hot_on_enter() {
    state = STATUS_HOT;
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    close();
    resetScreen();
    lcd.setCursor(2, 1);
    lcd.print("PROBLEM DETECTED");
}

void BinTask2::hot_on_exit() {

}

//reset dello schermo
void resetScreen() {
  lcd.backlight();
  lcd.display();
  lcd.setCursor(0, 0);
  lcd.clear();
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
