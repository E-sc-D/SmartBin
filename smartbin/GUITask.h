#ifndef __GUITASK__  
#define __GUITASK__  

#include "Task.h"

class GUITask: public Task{
    private:
        int idWaste;
        int idTemperature;
    public:
        void init();
        void tick();
        void printTempAndWaste();
        GUITask(int idWaste, int idTemperature);
};

#endif
