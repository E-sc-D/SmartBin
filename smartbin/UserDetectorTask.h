#ifndef __USERDETECTORTASK__
#define __USERDETECTORTASK__

#include "Task.h"

#define TSLEEP 3000

class UserDetectorTask : public Task {
    private:
        int pin;
        int idBin;
        int state;
        int prevRange;
        int timeReference;

        static void wakeUp();
        void isUserInRange();
    public:
        UserDetectorTask(int pin, int idBin);
        void tick();
};

#endif
