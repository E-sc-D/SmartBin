#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LowPower.h>
#include <PinChangeInterrupt.h>
#include "ButtonTask.h"
#include "TemperatureTask.h"
#include "UserDetectorTask.h"
#include "BinTask.h"

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

int green_led_status = LOW;
int red_led_status = LOW;

void setup() {
    Serial.begin(9600);  // attaches the servo on pin SERVO to the servo object
    
    pinMode(PIR, INPUT);
    pinMode(SONAR_TRIG, OUTPUT);
    pinMode(SONAR_ECHO, INPUT);
    pinMode(OPEN_BUTTON, INPUT_PULLUP);
    pinMode(CLOSE_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
}

void loop() {
    
}