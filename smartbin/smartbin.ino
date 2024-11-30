#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LowPower.h>
#include <PinChangeInterrupt.h>
#include "ButtonTask.h"
#include "TemperatureTask.h"
#include "UserDetectorTask.h"
#include "BinTask.h"
#include "WasteDetectorTask.h"
#include "Scheduler.h"


//digital pin
#define PIR 2
#define SERVO 3
#define SONAR_TRIG 4
#define SONAR_ECHO 5
#define OPEN_BUTTON 6
#define CLOSE_BUTTON 7
#define GREEN_LED 8
#define RED_LED 9

//analog pin
#define TEMP_SENSOR A3
#define TEMP_ID 0
#define USRD_ID 1
#define WSTD_ID 2
#define BTN1_ID 3
#define BTN2_ID 4
#define BIN_ID  5

int green_led_status = LOW;
int red_led_status = LOW;
Scheduler* scheduler;

void setup() {
    Serial.begin(9600);  // attaches the servo on pin SERVO to the servo object
    
    pinMode(PIR, INPUT);
    pinMode(SONAR_TRIG, OUTPUT);
    pinMode(SONAR_ECHO, INPUT);
    pinMode(OPEN_BUTTON, INPUT_PULLUP);
    pinMode(CLOSE_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    
    scheduler = new Scheduler();
    Task* t0 = new TemperatureTask(TEMP_SENSOR);
    Task* t1 = new UserDetectorTask(PIR);
    Task* t2 = new WasteDetectorTask(SONAR_TRIG,SONAR_ECHO,BIN_ID);
    Task* t3 = new ButtonTask(OPEN_BUTTON);
    Task* t4 = new ButtonTask(CLOSE_BUTTON);
    Task* t5 = new BinTask(TEMP_ID,WSTD_ID,BTN1_ID,BTN2_ID,SERVO);

    t0->init(1000,TEMP_ID);
    t1->init(2000,USRD_ID);
    t2->init(500,WSTD_ID);
    t3->init(100,BTN1_ID);
    t4->init(100,BTN2_ID);
    t5->init(200,BIN_ID);

    scheduler->addTask(t0);
    scheduler->addTask(t1);
    scheduler->addTask(t2);
    scheduler->addTask(t3);
    scheduler->addTask(t4);
    scheduler->addTask(t5);

    scheduler->init(50);
    
}

void loop() {
    scheduler->schedule();
}