#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Timer.h"
#include "Task.h"

#define MAX_TASKS 10

class Scheduler {
  
  int basePeriod;
  int nTasks = 0;
  int* Svariables;
  Task* taskList[MAX_TASKS];  
  Timer timer;

  public:
    void init(int basePeriod);  
    virtual bool addTask(Task* task);  
    virtual void schedule();
    Scheduler();
};

#endif

