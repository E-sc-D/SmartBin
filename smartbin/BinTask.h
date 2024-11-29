#ifndef __BINTASK__
#define __BINTASK__

#include "Task.h"
#include <ServoTimer2.h>

#define STATUS_CLOSED 0
#define STATUS_OPENED 1
#define STATUS_FULL 2
#define STATUS_HOT 3

class BinTask : public Task{
    private:
        int pin;
        int state;
        int idTemperature;
        int idWaste;
        int idButtonOpen;
        int idButtonClose;
        ServoTimer2 door;

        void open();
        void close();
    public:
        void tick();
        BinTask(int idTemperature, int idWaste, int idButtonOpen, int idButtonClose );
};
#endif