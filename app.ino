
#include "temperatures.h";
#include "flow.h";
#include "pulse.h";
#include "thingspeak.h";

Temperatures temperatures;
Flow flow;
Pulse pulse;
ThingSpeak thingSpeak;


void setup() {
  flow.setup();
  pulse.setup();
  temperatures.setup();
}

void loop()  {
  flow.loop();
  temperatures.loop();

  // temperature Math
  float ElgaRetourT  = temperatures.sensors.getTempC(temperatures.ElgaRetourt);
  float ElgaAT = temperatures.sensors.getTempC(temperatures.ElgaAanvoert);
  float ElgaAanvoerT = (ElgaAT - 0.5);    //Calibratie ivm afwijking
  float DeltaT = (ElgaAanvoerT - ElgaRetourT);          // Temperatuur verschil van aanvoer en retour

  // flow::literPerUur
  float A = (literPerUur / 1000);                       // A = M3/per uur 
  float M3ps = ( A / 3600 );                            // M3ps = M3/per seconde
  float Afgifte = (( M3ps * 990 ) * ( DeltaT * 4.19));  // Vermogen  water:   Φ = qv x Ƥw x cw x ∆t
  // Qv = volumestroom  in m³/s                                      
  // Cw = soortelijke warmte in kJ/(kg.K)  (water 4,19…4,2)
  // ∆t = temperatuur verschil (kelvin)
  // ρw = soortelijke massa  in kg/m³  (water  981…1000)
  // Φ = Vermogen  in kW                                                                                                                                                                                                                                                  

  pulse.loop();
  // pulse::readKWHsinceLastCall();
  float KWH = readKWHsinceLastCall();                         // kw/u waarde omzetten in variable 
  float pulsenTotaal = 1000 * KWH;                            // kw/h terug rekenen naar gemeten pulsen 
  float msSinceLastCount = millis() - timesincelastpulse;     // tijd verstreken sinds dat we de laatste S0 pulsen hebben gelezen
  float WH = 1000 * KWH * (3600000 / msSinceLastCount);     // Formule Watt uur = gemeten MS in Loop tijd (+delay tijd!) / 3600000 MS in een uur * pulsen in loop tijd    
  //float SUM = readKWHcumulatief();

  float COP;
  
  if ( KWH > 0)
  {
     COP = Afgifte * 1000 / WH; //(KWH * 360);
  }

  timesincelastpulse = millis();

  thingSpeak.send(WH, Afgifte, ElgaAanvoerT, ElgaRetourT, COP);

  delay(120000);  // tijdelijk alleen voor test fase toepassen
}
