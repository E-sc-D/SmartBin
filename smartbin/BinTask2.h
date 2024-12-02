#ifndef __BINTASK__
#define __BINTASK__

#include "Task.h"
#include <ServoTimer2.h>
#include <SimpleFSM.h>

#define STATUS_CLOSED 0
#define STATUS_OPENED 1
#define STATUS_FULL 2
#define STATUS_EMPTYING 3
#define STATUS_HOT 4
#define STATUS_WAITING 5

class BinTask2 : public Task{
    private:
        int pin;
        int state;
        int idTemperature;
        int idWaste;
        int idButtonOpen;
        int idButtonClose;
        ServoTimer2 door;
        unsigned long timeReference;

        enum Triggers{};
        SimpleFSM fsm;
        State s[];
        Transition transition[];
        TimedTransition timedTransitions[]

        void open();
        void close();
        void empty();
        void wait(unsigned long amountOfWait);

    public:
        void tick();
        bool elapsed(unsigned long time);
        void init(int period, int id) override;
        BinTask(int idTemperature, int idWaste, int idButtonOpen, int idButtonClose, int pin );

        void closed_on();
        void closed_on_enter();
        void closed_on_exit();

        void opened_on();
        void opened_on_enter();
        void opened_on_exit();
        void opened_trans_closed();

        void full_on();
        void full_on_enter();
        void full_on_exit();

        void emptying_on();
        void emptying_on_enter();
        void emptying_on_exit();//spesso exit potrebbe non servire, ma lo usiamo per "pulire" effetti di questo stato, come il led rosso

        void hot_on();
        void hot_on_enter();
        void hot_on_exit();
};
#endif