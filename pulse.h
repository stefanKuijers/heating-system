/*
    Pulse Sensor Class
*/
volatile unsigned int pulseCount;  

volatile unsigned long rpk = 0;               // raw pulse KWH counter (private)
volatile unsigned long rpk_old = 0;           // value of last read (private)
volatile boolean CS_KWH = false;              // Critical Section for KWH meter (private)
float KWH;
unsigned long timesincelastpulse;           // S0 pulse counter in xx time so we can convert the pulse's into KWH  
float pulsenTotaal;
void Kirq()   // The interrupt routine
{
  rpk++;                    // just increment raw pulse counter.
  if (rpk > 1000000000)     // reset pulse counter after 10e9 pulse = 500.000 KW 
  {
    if (false == CS_KWH)    // in critical section?  // assumption IRQ-call is handled atomic on arduino.
    {
      rpk = rpk - rpk_old;  // rpk = rpk - rpk_old
      rpk_old = 0;
    }
  }
}


// returns KWH's since last reset
float readKWHcumulatief()
{
  return rpk/2000.0;       // one pulse = 0.5 watt.
}

// returns KWH's since last call
float readKWHsinceLastCall()
{
  CS_KWH = true;                // Start Critical Section - prevent interrupt Kirq() from changing rpk & rpk_old ;
  long pulses = rpk - rpk_old;  // subtract last measure to get delta
  rpk_old = rpk;                // remember old value
  CS_KWH = false;               // End Critical Section
  return pulses/2000.0;         // return delta, one pulse = 0.5 watt.
}

void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}

class Pulse {
    public:
        void setup() {
            pulseCount        = 0;
            attachInterrupt(1, Kirq, FALLING); 
        }

        void loop() {

        }
};
