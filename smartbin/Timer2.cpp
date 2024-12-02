#include "Timer2.h"
#include "Arduino.h"

volatile bool timerFlag2;

ISR(TIMER2_COMPA_vect){
  timerFlag2 = true;
}

Timer2::Timer2(){
  timerFlag2 = false;  
}

void Timer2::setupFreq(int freq){
  
  cli();  // Disabilita gli interrupt
  
  TCCR2A = 0;   // Resetta TCCR2A
  TCCR2B = 0;   // Resetta TCCR2B
  TCNT2 = 0;    // Resetta il contatore
  
  // Calcola il valore OCR2A per TIMER2 (TIMER2 è a 8 bit)
  OCR2A = 16*1024/freq;  // F_CPU = 16MHz
  
  TCCR2A |= (1 << WGM21);        // Modalità CTC
  TCCR2B |= (1 << CS22) | (1 << CS20); // Prescaler 1024
  TIMSK2 |= (1 << OCIE2A);       // Abilita l'interrupt di confronto

  sei();  // Abilita gli interrupt
  
}

/* period in ms */
void Timer2::setupPeriod(int period){
  
  cli();
  
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;

  OCR2A = 16.384*period;   // Periodo in ms
  TCCR2A |= (1 << WGM21);
  TCCR2B |= (1 << CS22) | (1 << CS20);
  TIMSK2 |= (1 << OCIE2A);
  
  sei();
  
}

void Timer2::waitForNextTick(){
  /* wait for timer signal */
  while (!timerFlag2){}
  timerFlag2 = false;
  
}
