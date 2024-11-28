#ifndef __USERDETECTORTASK__
#define __USERDETECTORTASK__

#include "Task.h"

class UserDetectorTask : public Task{
    private:
        int pin;
    public:
        UserDetectorTask(int pin);
        void tick();
};
#endif