#ifndef __BUTTONTASK__  
#define __BUTTONTASK__

#include "Task.h"
class ButtonTask: public Task{
    private:
        int pin;
        int precState;
    public:
        void tick();// serve per spostare lo scope di tick da solo task a Button task
        //altrimenti non vede la variabile precState
        ButtonTask(int pin);
        
};

#endif