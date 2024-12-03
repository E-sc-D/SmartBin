#include "BinTask.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define MIN_FREE_SPACE 5 //distanza minima in cm tra il sonar e il contenuto del bidone 

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
    /*switch (state)
    {
        case STATUS_CLOSED:
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
                //wait(3000);
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
            //wait(4);
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
    }*/

    switch (this->state) {
        case CLOSED_ON:
            if (Svariable[this->idWaste] < MIN_FREE_SPACE) {
                this->state = FULL_ON_ENTER;
            } else if (Svariable[this->idTemperature] % 2 != 0) {
                this->state = HOT_ON_ENTER;
            } else if (Svariable[this->idButtonOpen] == HIGH) {
                this->state = OPENED_ON_ENTER;
                resetButtons();
            }
            break;

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

        case CLOSED_ON_EXIT:
            // Logica per CLOSED_ON_EXIT
            break;

        case OPENED_ON:
            if (Svariable[this->idWaste] < MIN_FREE_SPACE ||
                Svariable[this->idTemperature] % 2 != 0 || 
                Svariable[this->idButtonClose] == HIGH ||
                elapsed(5000))
            {
                this->state = OPENED_ON_EXIT;
                resetButtons();
            }
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

        case FULL_ON:
            if(Svariable[idGui] == 1) {
                this->state = FULL_ON_EXIT;
            }
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

        case FULL_ON_EXIT:
            this->state = EMPTYING_ON_ENTER;
            break;

        case EMPTYING_ON:
            if(elapsed(3000)) {
                this->state = EMPTYING_ON_EXIT;
                Svariable[idWaste] = 100;
            }
            break;

        case EMPTYING_ON_ENTER:
            this->state = EMPTYING_ON;
            empty();
            resetScreen();
            lcd.setCursor(1, 1);
            lcd.print("EMPTYING CONTAINER");
            break;

        case EMPTYING_ON_EXIT:
            this->state = CLOSED_ON_ENTER;
            break;

        case HOT_ON:
            if(Svariable[idGui] == 2) {
                this->state = HOT_ON_EXIT;
            }
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

        case HOT_ON_EXIT:
            this->state = CLOSED_ON_ENTER;
            break;

        case WAITING_ON_ENTER:
            this->timeReference = millis();
            this->state = WAITING_ON;
            break;

        case WAITING_ON:
            if(elapsed(2000)) {
                this->state = this->nextState;
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

void BinTask::empty(){
    door.write(-90);
}

//reset dello schermo
void BinTask::resetScreen() {
  lcd.backlight();
  lcd.display();
  lcd.setCursor(0, 0);
  lcd.clear();
}

void BinTask::resetButtons() {
    Svariable[this->idButtonOpen] = LOW;
    Svariable[this->idButtonClose] = LOW;
}

bool BinTask::elapsed(unsigned long time){
    return (millis() - timeReference >= time);
}
