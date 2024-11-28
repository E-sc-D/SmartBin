#ifndef __TASK__
#define __TASK__

class Task {
  int myPeriod;
  int timeElapsed;
  protected:
    int* Svariable;
    int id;
  
public:
  virtual void init(int period,int id){
    myPeriod = period; 
    this->id = id; 
    timeElapsed = 0;
  }

  void SetSvariable(int* var){
    Svariable = var;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod){
      timeElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }

  int getId(){
    return id;
  }
  
};

#endif

