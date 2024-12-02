#ifndef __BINTASK__
#define __BINTASK__

#include "Task.h"
#include <ServoTimer2.h>
#include <LiquidCrystal_I2C.h>

#define CLOSED_ON_ENTER 0
#define CLOSED_ON 1
#define CLOSED_ON_EXIT 2

#define OPENED_ON_ENTER 3
#define OPENED_ON 4
#define OPENED_ON_EXIT 5
#define OPENED_TRANS_CLOSED 6

#define FULL_ON_ENTER 7
#define FULL_ON 8
#define FULL_ON_EXIT 9

#define EMPTYING_ON_ENTER 10
#define EMPTYING_ON 11
#define EMPTYING_ON_EXIT 12

#define HOT_ON_ENTER 13
#define HOT_ON 14
#define HOT_ON_EXIT 15

#define WRECEIVED_ON 16
#define WRECEIVED_ON_ENTER 17

class BinTask : public Task{
    private:
        int pin;
        int greenLedPin;
        int redLedPin;
        int state;
        int idTemperature;
        int idWaste;
        int idButtonOpen;
        int idButtonClose;
        unsigned long timeReference;

        void open();
        void close();
        void empty();
        void resetScreen();

    public:
        void tick();
        void init(int period, int id) override;
        bool elapsed(unsigned long time);
        BinTask(int idTemperature, int idWaste, int idButtonOpen, int idButtonClose, int pin, int greenLedPin, int redLedPin);
};
#endif