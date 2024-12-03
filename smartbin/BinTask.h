#ifndef __BINTASK__
#define __BINTASK__

#include "Task.h"

#define CLOSED_ON_ENTER 0
#define CLOSED_ON 1
#define CLOSED_ON_EXIT 2

#define OPENED_ON_ENTER 3
#define OPENED_ON 4
#define OPENED_ON_EXIT 5

#define FULL_ON_ENTER 6
#define FULL_ON 7
#define FULL_ON_EXIT 8

#define EMPTYING_ON_ENTER 9
#define EMPTYING_ON 10
#define EMPTYING_ON_EXIT 11

#define HOT_ON_ENTER 12
#define HOT_ON 13
#define HOT_ON_EXIT 14

#define WAITING_ON_ENTER 15
#define WAITING_ON 16

class BinTask : public Task{
    private:
        int pin;
        int greenLedPin;
        int redLedPin;
        int state;
        int idTemperature;
        int idGui;
        int idWaste;
        int idButtonOpen;
        int idButtonClose;
        unsigned long timeReference;
        int nextState;

        void open();
        void close();
        void empty();
        void resetScreen();

    public:
        void tick();
        void init(int period, int id) override;
        bool elapsed(unsigned long time);
        BinTask(int idTemperature, int idGui, int idWaste, int idButtonOpen, int idButtonClose, int pin, int greenLedPin, int redLedPin);
};
#endif