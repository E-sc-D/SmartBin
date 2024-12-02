#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Timer2.h"
#include "Task.h"

#define MAX_TASKS 10

class Scheduler {
  
  int basePeriod;
  int nTasks = 0;
  Task* taskList[MAX_TASKS];  
  Timer2 timer;

  public:
    int* Svariables;
    void init(int basePeriod);  
    virtual bool addTask(Task* task);  
    virtual void schedule();
};

#endif

