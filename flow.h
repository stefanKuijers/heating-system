/*
    Flow Sensor Class
*/

byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin       = 2;

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 6.40;

volatile unsigned int FlowCount; 

float flowRate;
double literPerUur;
unsigned long oldTime;

class Flow {
    public:
        void setup() {
            pinMode(sensorPin, INPUT);
            digitalWrite(sensorPin, HIGH);

            flowRate          = 0.0;
            oldTime           = 0;
            attachInterrupt(sensorInterrupt, FlowCounter, FALLING);     // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
                                                            // Configured to trigger on a FALLING state change (transition from HIGH
                                                            // state to LOW state)
        }

        void loop() {
            
            if((millis() - oldTime) > 1000)    // Only process counters once per second
            { 
                // Disable the interrupt while calculating flow rate and sending the value to
                // the host
                detachInterrupt(sensorInterrupt);
                
                // Because this loop may not complete in exactly 1 second intervals we calculate
                // the number of milliseconds that have passed since the last execution and use
                // that to scale the output. We also apply the calibrationFactor to scale the output
                // based on the number of pulses per second per units of measure (litres/minute in
                // this case) coming from the sensor.
                flowRate = ((1000.0 / (millis() - oldTime)) * FlowCount) / calibrationFactor;

                // Note the time this processing pass was executed. Note that because we've
                // disabled interrupts the millis() function won't actually be incrementing right
                // at this point, but it will still return the value it was set to just before
                // interrupts went away.
                oldTime = millis();

                // Divide the flow rate in litres/minute by 60 to determine how many litres have
                // passed through the sensor in this 1 second interval, then multiply by 1000 to
                // convert to millilitres.
                literPerUur = flowRate * 60; //flowrate x 60 zodat we van liters per minuut naar liters per uur gaan

                // Reset the pulse counter so we can start incrementing again
                FlowCount = 0;

                // Enable the interrupt again now that we've finished sending output
                attachInterrupt(sensorInterrupt, FlowCounter, FALLING);
            }
        }
};

void FlowCounter()
{
  // Increment the flow counter
  FlowCount++;
}