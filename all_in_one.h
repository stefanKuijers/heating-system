
// // ThingSpeak
// #include <UnoWiFiDevEd.h>

// #define CONNECTOR     "rest"
// #define SERVER_ADDR   "api.thingspeak.com"
// #define APIKEY_THINGSPEAK  "RG3WGCNATYZLGW73" //Insert your API Key


// //*******************Temperatuur sensoren*************\

// // Include the libraries we need
// #include <OneWire.h>
// #include <DallasTemperature.h>
// #define ONE_WIRE_BUS 10                    // Data wire is plugged into port 10 on the Arduino
// OneWire oneWire(ONE_WIRE_BUS);            // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
// DallasTemperature sensors(&oneWire);      // Pass our oneWire reference to Dallas Temperature. 
// DeviceAddress ElgaAanvoert  = { 0x28, 0xAE, 0x68, 0x26, 0x00, 0x00, 0x80, 0x8B }; // arrays to hold device address
// DeviceAddress ElgaRetourt   = { 0x28, 0xFF, 0x01, 0x6A, 0xA3, 0x16, 0x05, 0x65 }; // DeviceAddress insideThermometer;
          

//               //*******************S0 pulse part*******************\\
              
// volatile unsigned long rpk = 0;               // raw pulse KWH counter (private)
// volatile unsigned long rpk_old = 0;           // value of last read (private)
// volatile boolean CS_KWH = false;              // Critical Section for KWH meter (private)
// float KWH;
// unsigned long timesincelastpulse;           // S0 pulse counter in xx time so we can convert the pulse's into KWH  
// float pulsenTotaal;
// void Kirq()   // The interrupt routine
// {
//   rpk++;                    // just increment raw pulse counter.
//   if (rpk > 1000000000)     // reset pulse counter after 10e9 pulse = 500.000 KW 
//   {
//     if (false == CS_KWH)    // in critical section?  // assumption IRQ-call is handled atomic on arduino.
//     {
//       rpk = rpk - rpk_old;  // rpk = rpk - rpk_old
//       rpk_old = 0;
//     }
//   }
// }

// // returns KWH's since last reset
// float readKWHcumulatief()
// {
//   return rpk/2000.0;       // one pulse = 0.5 watt.
// }

// // returns KWH's since last call
// float readKWHsinceLastCall()
// {
//   CS_KWH = true;                // Start Critical Section - prevent interrupt Kirq() from changing rpk & rpk_old ;
//   long pulses = rpk - rpk_old;  // subtract last measure to get delta
//   rpk_old = rpk;                // remember old value
//   CS_KWH = false;               // End Critical Section
//   return pulses/2000.0;         // return delta, one pulse = 0.5 watt.
// }


//             //******************Flow sensor part******************\\
            
// byte sensorInterrupt = 0;  // 0 = digital pin 2
// byte sensorPin       = 2;

// // The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// // litre/minute of flow.
// float calibrationFactor = 6.40;

// volatile unsigned int pulseCount;  
// volatile unsigned int FlowCount; 

// float flowRate;
// double literPerUur;
// unsigned long oldTime;

// void setup() {

//   Ciao.begin(); // ThingSpeak and WIFI console
    
//                 //*******************S0 pulse  part*******************\\
              
//   attachInterrupt(1, Kirq, FALLING); //We use pin number 3 on the board

//             //*******************Temperatuur sensoren*************\\

//   sensors.begin();                                       
//   sensors.setResolution(ElgaRetourt, 9);    // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
//   sensors.setResolution(ElgaAanvoert, 9);
        
//                 //************* Flow sensor part**************\\
                

//   pinMode(sensorPin, INPUT);
//   digitalWrite(sensorPin, HIGH);

//   pulseCount        = 0;
//   flowRate          = 0.0;
//   oldTime           = 0;
//   attachInterrupt(sensorInterrupt, FlowCounter, FALLING);     // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
//                                                              // Configured to trigger on a FALLING state change (transition from HIGH
//                                                               // state to LOW state)
// }

// void loop()  {

//     // ********* Flow sensor part*********\\
  
//   if((millis() - oldTime) > 1000)    // Only process counters once per second
//   { 
//     // Disable the interrupt while calculating flow rate and sending the value to
//     // the host
//     detachInterrupt(sensorInterrupt);
        
//     // Because this loop may not complete in exactly 1 second intervals we calculate
//     // the number of milliseconds that have passed since the last execution and use
//     // that to scale the output. We also apply the calibrationFactor to scale the output
//     // based on the number of pulses per second per units of measure (litres/minute in
//     // this case) coming from the sensor.
//     flowRate = ((1000.0 / (millis() - oldTime)) * FlowCount) / calibrationFactor;
    
//     // Note the time this processing pass was executed. Note that because we've
//     // disabled interrupts the millis() function won't actually be incrementing right
//     // at this point, but it will still return the value it was set to just before
//     // interrupts went away.
//     oldTime = millis();
    
//     // Divide the flow rate in litres/minute by 60 to determine how many litres have
//     // passed through the sensor in this 1 second interval, then multiply by 1000 to
//     // convert to millilitres.
//     literPerUur = flowRate * 60; //flowrate x 60 zodat we van liters per minuut naar liters per uur gaan
    
//     // Reset the pulse counter so we can start incrementing again
//     FlowCount = 0;
    
//     // Enable the interrupt again now that we've finished sending output
//     attachInterrupt(sensorInterrupt, FlowCounter, FALLING);
//   }
//          //*******************Temperatuur sensoren*************\\

//           // call sensors.requestTemperatures() to issue a global temperature 
//           // request to all devices on the bus
//   sensors.requestTemperatures(); // Send the command to get temperatures
  
  
//   // It responds almost immediately. Let's print out the data
//   float ElgaRetourT  = sensors.getTempC (ElgaRetourt);
//   float ElgaAT = sensors.getTempC (ElgaAanvoert);
//   float ElgaAanvoerT = (ElgaAT - 0.5);    //Calibratie ivm afwijking
//   float DeltaT = (ElgaAanvoerT - ElgaRetourT);          // Temperatuur verschil van aanvoer en retour
//   float A = (literPerUur / 1000);                       // A = M3/per uur 
//   float M3ps = ( A / 3600 );                            // M3ps = M3/per seconde
//   float Afgifte = (( M3ps * 990 ) * ( DeltaT * 4.19));  // Vermogen  water:   Φ = qv x Ƥw x cw x ∆t
//                                                        // Qv = volumestroom  in m³/s                                      
//                                                       // Cw = soortelijke warmte in kJ/(kg.K)  (water 4,19…4,2)
//                                                     // ∆t = temperatuur verschil (kelvin)
//                                                          // ρw = soortelijke massa  in kg/m³  (water  981…1000)
//                                                          // Φ = Vermogen  in kW                                                                                                                                                                                                                                                  

//   //********S0 pulse part **********\\
  
//     //float pulsenTotaal = readKWHsinceLastCall();
//     float KWH = readKWHsinceLastCall();                         // kw/u waarde omzetten in variable 
//     float pulsenTotaal = 1000 * KWH;                            // kw/h terug rekenen naar gemeten pulsen 
//     float msSinceLastCount = millis() - timesincelastpulse;     // tijd verstreken sinds dat we de laatste S0 pulsen hebben gelezen
//     float WH = 1000 * KWH * (3600000 / msSinceLastCount);     // Formule Watt uur = gemeten MS in Loop tijd (+delay tijd!) / 3600000 MS in een uur * pulsen in loop tijd    
                                                                  
//     //float SUM = readKWHcumulatief();


// float COP;
  
//   if ( KWH > 0)
//   {
//      COP = Afgifte * 1000 / WH; //(KWH * 360);
//   }

// timesincelastpulse = millis();

//         //*********************ThingSpeak*********************\\

// String uri = "/update?api_key=";
//   uri += APIKEY_THINGSPEAK;
//   uri += "&field1=";
//   uri += String(WH);            //Versturen van de waarde van stroom verbuik in WH
//   uri += "&field2=";
//   uri += String(Afgifte);       //Versturen van het geleverde vermogen
//   uri += "&field3=";
//   uri += String(ElgaAanvoerT);  //Versturen van aanvoer temperatuur van de Elga
//   uri += "&field4=";
//   uri += String(ElgaRetourT);   //Versturen van de retour temeratuur van de Elga
//   uri += "&field5=";
//   uri += String(COP);           //Versturen van de COP waarde van de Elga
// //  uri += "&field6=";            
// //  uri += String(SUM);   //Versturen van de flow


//   Ciao.println(F("Sending data on ThingSpeak Channel"));
//   CiaoData data = Ciao.write(CONNECTOR, SERVER_ADDR, uri); 
  



// Ciao.println(WH);
// Ciao.println(Afgifte);
// Ciao.println(ElgaAanvoerT);
// Ciao.println(ElgaRetourT);
// Ciao.println(COP); 
// Ciao.print("KWH: ");    
// Ciao.println(KWH, 4);
// Ciao.print("WH");
// Ciao.println(WH);
// //Ciao.print("SUM");
// //Ciao.println(SUM);

//   if (!data.isEmpty()){
//     Ciao.println( "State: " + String (data.get(1)));
//     Ciao.println( "Response: " + String (data.get(2)));
//   }
//   else{
//     Ciao.println(F("Write Error"));       
//   }

 
// delay(120000);  // tijdelijk alleen voor test fase toepassen

// }

//       //*******************S0 pulse part******************\\
     
// void pulseCounter()
// {
//   // Increment the pulse counter
//   pulseCount++;
// }
//     // ********* Flow sensor part*********\\
    
// void FlowCounter()
// {
//   // Increment the flow counter
//   FlowCount++;
// }