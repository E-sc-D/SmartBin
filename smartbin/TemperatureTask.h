#ifndef __TEMPERATURETASK__  
#define __TEMPERATURETASK__

#include "Task.h"

class TemperatureTask : public Task{
    private:
        int pin;
    public:
        void tick();    //serve per spostare lo scope da solo task a temperature task altrimenti non vede la variabile
        TemperatureTask(int pin);
};

#endif
