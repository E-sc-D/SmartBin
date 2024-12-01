#ifndef __WASTEDETECTORTASK__  
#define __WASTEDETECTORTASK__

#include "Task.h"

class WasteDetectorTask : public Task{
    private:
        int trigPin;
        int echoPin;
        int idBin;
    public:
        WasteDetectorTask(int trigPin, int echoPin, int binState);
        float BinUsable();
        void tick();
        void init(int period, int id) override;
};

#endif
