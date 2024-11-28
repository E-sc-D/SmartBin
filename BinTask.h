#ifndef __USERDETECTORTASK__
#define __USERDETECTORTASK__

#include "Task.h"

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
        int idButton;

        void open();
        void close();
    public:
        void init(int period, int pin, int idTemperature, int idWaste, int idButton);
        void tick();
};
#endif