#ifndef __TEMPERATURETASK__  
#define __TEMPERATURETASK__

#include "Task.h"
class TemperatureTask : public Task{
    private:
        int pin;
    public:
        TemperatureTask(int pin);
        void tick();//serve per spostare lo scope da solo task a temperature task
        // altrimenti non vede la variabile
};
#endif