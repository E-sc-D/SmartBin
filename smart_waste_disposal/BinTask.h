#ifndef __BINTASK__
#define __BINTASK__

#include "Task.h"

#define MIN_FREE_SPACE 5 //distanza minima in cm tra il sonar e il contenuto del bidone
#define T1 10000
#define T2 2000
#define T3 3000

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

#define SLEEP_ON_ENTER 17
#define SLEEP_ON 18

class BinTask : public Task {
    private:
        int pin;
        int greenLedPin;
        int redLedPin;
        int state;
        int idTemperature;
        int idUsr;
        int idWaste;
        int idButtonOpen;
        int idButtonClose;
        int idGui;
        unsigned long timeReference;
        int nextState;

        void open();
        void close();
        void empty();
        void resetScreen();
        void resetButtons();
        void sleepComponents();

    public:
        BinTask(int idTemperature, int idUsr, int idWaste, int idButtonOpen, int idButtonClose, int idGui, int pin, int greenLedPin, int redLedPin);
        void tick();
        void init(int period, int id) override;
        bool elapsed(unsigned long time);
};
#endif