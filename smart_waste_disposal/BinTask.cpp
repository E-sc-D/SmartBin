#include "BinTask.h"
#include <Arduino.h>
#include <LowPower.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo door;

BinTask::BinTask(int idTemperature, int idUsr, int idWaste, int idButtonOpen, int idButtonClose, int idGui, int pin, int greenLedPin, int redLedPin) {
    this->pin = pin;
    this->greenLedPin = greenLedPin;
    this->redLedPin = redLedPin;
    this->idTemperature = idTemperature;
    this->idUsr = idUsr;
    this->idWaste = idWaste;
    this->idButtonOpen = idButtonOpen;
    this->idButtonClose = idButtonClose;
    this->idGui = idGui;
    this->state = CLOSED_ON_ENTER;
    this->timeReference = 0;
}

void BinTask::init(int period, int id) {
    Serial.println("INIT");
    Task::init(period, id);
    door.attach(this->pin);
    lcd.init();
    resetScreen();
}

void BinTask::tick() {
    switch (this->state) {
        case CLOSED_ON_ENTER:
            this->state = CLOSED_ON;
            digitalWrite(this->greenLedPin, HIGH);
            digitalWrite(this->redLedPin, LOW);
            close();
            resetScreen();
            lcd.setCursor(5, 1);
            lcd.print("PRESS OPEN");
            lcd.setCursor(4, 2);
            lcd.print("TO ENTER WASTE");
            break;

        case CLOSED_ON:
            if (Svariable[this->idWaste] < MIN_FREE_SPACE) {
                this->state = FULL_ON_ENTER;
            } else if (Svariable[this->idTemperature] % 2 != 0) {
                this->state = HOT_ON_ENTER;
            } else if (Svariable[this->idButtonOpen] == HIGH) {
                this->state = OPENED_ON_ENTER;
                resetButtons();
            } else if (Svariable[this->idUsr] == 1) {
                this->state = SLEEP_ON_ENTER;
            }
            break;

        case CLOSED_ON_EXIT:
            // Logica per CLOSED_ON_EXIT
            break;

        case OPENED_ON_ENTER:
            this->state = OPENED_ON;
            this->timeReference = millis();
            open();
            resetScreen();
            lcd.setCursor(5, 1);
            lcd.print("PRESS CLOSE");
            lcd.setCursor(5, 2);
            lcd.print("WHEN DONE");
            break;

        case OPENED_ON:
            if (Svariable[this->idWaste] < MIN_FREE_SPACE ||
                Svariable[this->idTemperature] % 2 != 0 || 
                Svariable[this->idButtonClose] == HIGH ||
                elapsed(T1))
            {
                this->state = OPENED_ON_EXIT;
                resetButtons();
            }
            break;

        case OPENED_ON_EXIT:
            close();
            resetScreen();
            lcd.setCursor(3, 1);
            lcd.print("WASTE RECEIVED");
            if (Svariable[this->idWaste] < MIN_FREE_SPACE) {
              this->nextState = FULL_ON_ENTER;
            } else if (Svariable[this->idTemperature] % 2 != 0) {
              this->nextState = HOT_ON_ENTER;
            } else {
              this->nextState = CLOSED_ON_ENTER;
            }
            this->state = WAITING_ON_ENTER;
            break;

        case FULL_ON_ENTER:
            this->state = FULL_ON;
            digitalWrite(this->greenLedPin, LOW);
            digitalWrite(this->redLedPin, HIGH);
            close();
            resetScreen();
            lcd.setCursor(3, 1);
            lcd.print("CONTAINER FULL");
            break;

        case FULL_ON:
            if(Svariable[this->idGui] == 1) {
                this->state = FULL_ON_EXIT;
            }
            break;

        case FULL_ON_EXIT:
            this->state = EMPTYING_ON_ENTER;
            break;

        case EMPTYING_ON_ENTER:
            this->state = EMPTYING_ON;
            empty();
            resetScreen();
            lcd.setCursor(1, 1);
            lcd.print("EMPTYING CONTAINER");
            this->timeReference = millis();
            break;

        case EMPTYING_ON:
            if(elapsed(T3)) {
                this->state = EMPTYING_ON_EXIT;
                Svariable[this->idWaste] = 100;
            }
            break;

        case EMPTYING_ON_EXIT:
            this->state = CLOSED_ON_ENTER;
            Svariable[this->idGui] = 0;
            break;

        case HOT_ON_ENTER:
            this->state = HOT_ON;
            digitalWrite(this->greenLedPin, LOW);
            digitalWrite(this->redLedPin, HIGH);
            close();
            resetScreen();
            lcd.setCursor(2, 1);
            lcd.print("PROBLEM DETECTED");
            break;

        case HOT_ON:
            if(Svariable[this->idGui] == 2) {
                this->state = HOT_ON_EXIT;
            }
            break;

        case HOT_ON_EXIT:
            this->state = CLOSED_ON_ENTER;
            Svariable[this->idGui] = 0;
            break;

        case WAITING_ON_ENTER:
            this->timeReference = millis();
            this->state = WAITING_ON;
            break;

        case WAITING_ON:
            if(elapsed(T2)) {
                this->state = this->nextState;
            }
            break;

        case SLEEP_ON_ENTER:
            this->state = SLEEP_ON;
            sleepComponents();
            LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
            break;

        case SLEEP_ON:
            if (Svariable[this->idUsr] == 0) {
                this->state = CLOSED_ON_ENTER;
            }
            break;

        default:
            break;
    }

    //pulisco gli stati ogni volta
    Svariable[this->id] = this->state;
}

void BinTask::open() {
    door.write(90);
}

void BinTask::close() {
    door.write(0);
}

void BinTask::empty() {
    door.write(180);
}

//reset dello schermo
void BinTask::resetScreen() {
    lcd.backlight();
    lcd.display();
    lcd.setCursor(0, 0);
    lcd.clear();
}

void BinTask::sleepComponents() {
    lcd.noBacklight();
    lcd.noDisplay();
}

void BinTask::resetButtons() {
    Svariable[this->idButtonOpen] = LOW;
    Svariable[this->idButtonClose] = LOW;
}

bool BinTask::elapsed(unsigned long time) {
    return (millis() - this->timeReference >= time);
}
