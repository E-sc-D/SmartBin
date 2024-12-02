#ifndef __TIMER__
#define __TIMER__

class Timer2 {
    
public:  
  Timer2();
  void setupFreq(int freq);  
  /* period in ms */
  void setupPeriod(int period);  
  void waitForNextTick();

};


#endif

