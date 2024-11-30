#include "Scheduler.h"
#include <stdlib.h>

Scheduler::Scheduler(){
  this->nTasks = 0;
}
void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timer.setupPeriod(basePeriod);  
  Svariables = (int*)calloc(nTasks, sizeof(int));
  Svariables[2] = 10;
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    task->SetSvariable(Svariables);
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false; 
  }
}
  
void Scheduler::schedule(){
  timer.waitForNextTick();
  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->updateAndCheckTime(basePeriod)){
      taskList[i]->tick();
    }
  }
}

