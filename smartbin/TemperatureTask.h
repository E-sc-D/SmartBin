#ifndef __TEMPERATURETASK__  
#define __TEMPERATURETASK__

#include "Task.h"

#define MAX_TEMP 30
#define MAXTEMPTIME 3000

class TemperatureTask : public Task {
    private:
        int pin;
        int state = 0;
        int prevTemp;
        int timeReference;
    public:
        TemperatureTask(int pin);
        void tick();    //serve per spostare lo scope da solo task a temperature task altrimenti non vede la variabile
        int isTooHot();
};

#endif
