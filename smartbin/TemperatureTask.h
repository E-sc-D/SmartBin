#ifndef __TEMPERATURETASK__  
#define __TEMPERATURETASK__

#include "Task.h"

#define MAX_TEMP 27
#define MAXTEMPTIME 3000

class TemperatureTask : public Task{
    private:
        int pin;
        int state = 0;
        int prevTemp;
        int timeReference;
    public:
        void tick();    //serve per spostare lo scope da solo task a temperature task altrimenti non vede la variabile
        int isTooHot();
        TemperatureTask(int pin);
};

#endif
