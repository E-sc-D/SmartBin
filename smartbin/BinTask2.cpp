#include "BinTask2.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define MIN_FREE_SPACE 1 //distanza minima in cm tra il sonar e il contenuto del bidone 
#define MAX_TEMP 60

LiquidCrystal_I2C lcd(39, 20, 4);

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
    lcd.begin(20, 4);
    resetScreen();
    State s[] = {
            State("opened",    opened_on_enter,    opened_on,    opened_on_exit,   false),
            State("closed",    closed_on_enter,    closed_on,    closed_on_exit,   false),
            State("full",      full_on_enter,      full_on,      full_on_exit,     false),
            State("emptying",  emptying_on_enter,  emptying_on,  emptying_on_exit, false),
            State("hot",       hot_on_enter,       hot_on,       hot_on_exit,      false),
            State("wreceived", wreceived_on_enter, wreceived_on, NULL ,            false)
    };
    Transition transition[];
    TimedTransition timedTransitions[] = {
            TimedTransition(&s[1], &s[0], 6000), //da aperto a chiuso
            TimedTransition(&s[3], &s[1], 6000), //da aperto a chiuso
    };
    fsm.add(timedTransitions, (sizeof(timedTransitions []) / sizeof(TimedTransition)));
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

//reset dello schermo
void BinTask2::resetScreen() {
  lcd.backlight();
  lcd.display();
  lcd.setCursor(0, 0);
  lcd.clear();
}

void BinTask2::closed_on() {

}

void BinTask2::closed_on_enter() {
    this->state = STATUS_CLOSED;
    digitalWrite(this->greenLedPin, HIGH);
    digitalWrite(this->redLedPin, LOW);
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
    this->state = STATUS_OPENED;
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
    this->state = STATUS_FULL;
    digitalWrite(this->greenLedPin, LOW);
    digitalWrite(this->redLedPin, HIGH);
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
    this->state = STATUS_EMPTYING;
    digitalWrite(this->greenLedPin, HIGH);
    digitalWrite(this->redLedPin, LOW);
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
    this->state = STATUS_HOT;
    digitalWrite(this->greenLedPin, LOW);
    digitalWrite(this->redLedPin, HIGH);
    close();
    resetScreen();
    lcd.setCursor(2, 1);
    lcd.print("PROBLEM DETECTED");
}

void BinTask2::hot_on_exit() {

}
