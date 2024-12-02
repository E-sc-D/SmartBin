#include "BinTask.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ServoTimer2.h>

#define MIN_FREE_SPACE 1 //distanza minima in cm tra il sonar e il contenuto del bidone 
#define MAX_TEMP 60

LiquidCrystal_I2C lcd(0x27, 20, 4);
ServoTimer2 door;

BinTask::BinTask(int idTemperature, int idWaste, int idButtonOpen, int idButtonClose, int pin, int greenLedPin, int redLedPin) {
    this->pin = pin;
    this->greenLedPin = greenLedPin;
    this->redLedPin = redLedPin;
    this->idTemperature = idTemperature;
    this->idWaste = idWaste;
    this->idButtonOpen = idButtonOpen;
    this->idButtonClose = idButtonClose;
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
    Serial << "bintask " << id << '\n';
    switch (this->state) {
        case CLOSED_ON:
            if (Svariable[this->idWaste] < MIN_FREE_SPACE) {
                this->state = FULL_ON_ENTER;
            } else if (Svariable[this->idTemperature] > MAX_TEMP) {
                this->state = HOT_ON_ENTER;
            } else if (Svariable[this->idButtonOpen] == HIGH) {
                this->state = OPENED_ON_ENTER;
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
            // Logica per OPENED_ON
            break;
        case OPENED_ON_ENTER:
            this->state = OPENED_ON;
            open();
            resetScreen();
            lcd.setCursor(5, 1);
            lcd.print("PRESS CLOSE");
            lcd.setCursor(5, 2);
            lcd.print("WHEN DONE");
            break;
        case OPENED_ON_EXIT:
            resetScreen();
            lcd.setCursor(3, 1);
            lcd.print("WASTE RECEIVED");
            //Wait T2 seconds
            this->state = CLOSED_ON_ENTER;
            break;
        case OPENED_TRANS_CLOSED:
            // Logica per OPENED_TRANS_CLOSED
            break;

        case FULL_ON:
            Serial.println(Svariable[this->idWaste]);
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
            // Logica per FULL_ON_EXIT
            break;

        case EMPTYING_ON:
            // Logica per EMPTYING_ON
            break;
        case EMPTYING_ON_ENTER:
            this->state = EMPTYING_ON;
            digitalWrite(this->greenLedPin, HIGH);
            digitalWrite(this->redLedPin, LOW);
            empty();
            resetScreen();
            lcd.setCursor(1, 1);
            lcd.print("EMPTYING CONTAINER");
            break;
        case EMPTYING_ON_EXIT:
            // Logica per EMPTYING_ON_EXIT
            break;

        case HOT_ON:
            Serial.println(Svariable[this->idTemperature]);
            // Logica per HOT_ON
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
            // Logica per HOT_ON_EXIT
            break;

        case WRECEIVED_ON:
            // Logica per WRECEIVED_ON
            break;
        case WRECEIVED_ON_ENTER:
            // Logica per WRECEIVED_ON_ENTER
            break;

        default:
            break;
    }

    Svariable[this->idButtonOpen] = 0;//pulisco gli stati ogni volta
    Svariable[this->idButtonClose] = 0;
    Svariable[this->id] = this->state;
    Serial.println(Svariable[id]);
}

void BinTask::open() {
    door.write(90);
    Serial.println("open");
}

void BinTask::close() {
    door.write(0);
    Serial.println("close");
}

void BinTask::empty(){
    door.write(-90);
    Serial.println("empty");
}

//reset dello schermo
void BinTask::resetScreen() {
  lcd.backlight();
  lcd.display();
  lcd.setCursor(0, 0);
  lcd.clear();
}

bool BinTask::elapsed(unsigned long time){
    return (millis() - timeReference >= time);
}
