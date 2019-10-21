/*
  Main file
*/

// inlcudes
#include "blink.h"

// construct and assign
Blink blink;

void setup() {
    Serial.begin(115200);

    // 

    blink.setup();
}

void loop() {
    blink.loop(0.5);  
    blink.loop(2);

    Serial.println(blink.blinkDelay);

    delay(200);
}
