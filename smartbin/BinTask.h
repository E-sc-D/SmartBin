#ifndef __BINTASK__
#define __BINTASK__

#include "Task.h"
#include <ServoTimer2.h>

#define STATUS_CLOSED 0
#define STATUS_OPENED 1
#define STATUS_FULL 2
#define STATUS_EMPTYING 3
#define STATUS_HOT 4
#define STATUS_WAITING 5

class BinTask : public Task{
    private:
        int pin;
        int state;
        int idTemperature;
        int idWaste;
        int idButtonOpen;
        int idButtonClose;
        ServoTimer2 door;
        unsigned long timeReference;
        int amountOfWait;
        int prevState;

        void open();
        void close();
        void empty();
        void wait(int amountOfWait);
    public:
        void tick();
        bool elapsed(int time);
        BinTask(int idTemperature, int idWaste, int idButtonOpen, int idButtonClose );
};
#endif