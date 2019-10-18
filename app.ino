/*
  Main file
*/

// inlcudes
#include "blink.h"

// construct and assign
Blink blink;


void setup() {
    Serial.begin(9600);

    blink.setup();
}

void loop() {
    blink.loop(1);      
    Serial.println(blink.blinkDelay); 

    delay(200);
}
