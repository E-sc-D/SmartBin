#ifndef __WASTEDETECTORTASK__  
#define __WASTEDETECTORTASK__
#include "Task.h"

class WasteDetectorTask : public Task{
    private:
        int trigPin;
        int echoPin;
        int binState;
    public:
        WasteDetectorTask(int trigPin, int echoPin, int binState);
        bool BinUsable();
        void tick();
};
#endif