#ifndef __GUITASK__  
#define __GUITASK__  

#include "Task.h"

class GUITask: public Task {
    private:
        int idWaste;
        int idTemperature;
        int idBin;
    public:
        GUITask(int idWaste, int idTemperature, int idBin);
        void init();
        void tick();
        void printTempAndWaste();
};

#endif
