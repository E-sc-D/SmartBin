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
        static int pin;
        static int greenLedPin;
        static int redLedPin;
        static int state;
        static int idTemperature;
        static int idWaste;
        static int idButtonOpen;
        static int idButtonClose;
        static unsigned long timeReference;
        static ServoTimer2 door;

        enum Triggers{};
        enum EventId{};
        SimpleFSM fsm;

        static void open();
        static void close();
        static void empty();
        static void resetScreen();

        static bool buttonOpen();
        static bool buttonClose();
        static bool temperature();
        static bool isFull();


    public:
        void tick();
        void init(int period, int id) override;
        BinTask2(int idTemperature, int idWaste, int idButtonOpen, int idButtonClose, int pin, int greenLedPin, int redLedPin);
        
        static void closed_on();
        static void closed_on_enter();
        static void closed_on_exit();
 
        static void opened_on();
        static void opened_on_enter();
        static void opened_on_exit();
        static void opened_trans_closed();
 
        static void full_on();
        static void full_on_enter();
        static void full_on_exit();
 
        static void emptying_on();
        static void emptying_on_enter();
        static void emptying_on_exit();//spesso exit potrebbe non servire, ma lo usiamo per "pulire" effetti di questo stato, come il led rosso
 
        static void hot_on();
        static void hot_on_enter();
        static void hot_on_exit();
 
        static void wreceived_on();
        static void wreceived_on_enter();
};
#endif