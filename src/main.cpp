#include <Arduino.h>
#include "debug.h"

const int input = A0;
int reading;

// bone dry is 1023
// dry soil around ~600-700
// just watered is ~250-400


void setup() {
    // put your setup code here, to run once:
    initSerial();
    debug("initialisation complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  reading = analogRead(input);
  debug("Current reading:");
  debugln(reading);
}