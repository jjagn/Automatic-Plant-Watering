#include <Arduino.h>
#include "debug.h"
#include <LiquidCrystal.h>

// defining states for state machine
#define IDLE 0
#define READING_MOISTURE 1
#define PRINTING_TO_SCREEN 2

// constants
const int inputPin = A0;
const int buttonPin = 7;

// initialise LCD library
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// vars
int state = IDLE;
int buttonState;
int reading;
int readingPct;

// bone dry is 1023
// dry soil around ~600-700
// just watered is ~250-400

void setup() {
    // put your setup code here, to run once:
    initSerial();
    debug("initialisation complete");

    pinMode(buttonPin, INPUT);
    pinMode(inputPin, INPUT);

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    delay(50);
    lcd.print("initialising");
}
    

void loop() {
    // put your main code here, to run repeatedly:
    debugln("looping");
    debugln(state);
    switch (state)
    {
    case IDLE:
        lcd.clear();
        lcd.noDisplay();
        buttonState = digitalRead(buttonPin);
        if (buttonState == HIGH) {
            state = READING_MOISTURE;
        }
        debugln("state idle");

        break;

    case READING_MOISTURE:
        debugln("reading moisture");
        reading = analogRead(inputPin);
        readingPct = map(reading, 800, 200, 0, 100);
        debugln("read moisture value");
        debug("moisture value: ");
        state = PRINTING_TO_SCREEN;
        break;

    case PRINTING_TO_SCREEN:
        debugln("printing");
        lcd.display();
        lcd.print("watered: ");
        lcd.print(readingPct);
        lcd.println("%");
        delay(3000);
        lcd.clear();
        lcd.noDisplay(); 
        state = IDLE;
        break;
  }
}