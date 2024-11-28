#ifndef __WASTEDETECTORTASK__  
#define __WASTEDETECTORTASK__
#include "Task.h"

class WasteDetectorTask : public Task{
    private:
        int trigPin;
        int echoPIn;
        int n;
    public:
        WasteDetectorTask(int pin);
        bool  BinUsable(int n);
        void tick();
};
#endif