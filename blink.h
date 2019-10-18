

class Blink {       // The class
  public:             // Access specifier
    int pin;        // Attribute (int variable)
    uint8_t mode;  // Attribute (string variable)
    int blinkDelay;

    Blink() // default contructor
    { 
        pin = LED_BUILTIN;
        mode = OUTPUT;
        blinkDelay = 1000;
    } 

    void setup() {
        pinMode(pin, mode);
    }

    void loop(double delayMultiply = 0.5) {
        digitalWrite(Blink::pin, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(blinkDelay * delayMultiply);                       // wait for a second
        digitalWrite(Blink::pin, LOW);    // turn the LED off by making the voltage LOW
        delay(blinkDelay * delayMultiply); 
        
        if (blinkDelay > 50) {
            blinkDelay = blinkDelay - 50; 
        } 
    }
};