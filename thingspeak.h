#include <UnoWiFiDevEd.h>

// #define CONNECTOR   ;
// #define SERVER_ADDR     "api.thingspeak.com";

class ThingSpeak {
    private:
        const char key = APIKEY_THINGSPEAK;
        const char* connector = "rest";
        const char* url = "api.thingspeak.com";

    public:
        ThingSpeak() {
            //
        }

        void setup() {
            Ciao.begin(); // ThingSpeak and WIFI console
        }

        void send(int WH, int Afgifte, int ElgaAanvoerT, int ElgaRetourT, int COP, int KWH) {
            String uri = "/update?api_key=";
            uri += APIKEY_THINGSPEAK;
            uri += "&field1=";
            uri += String(WH);            //Versturen van de waarde van stroom verbuik in WH
            uri += "&field2=";
            uri += String(Afgifte);       //Versturen van het geleverde vermogen
            uri += "&field3=";
            uri += String(ElgaAanvoerT);  //Versturen van aanvoer temperatuur van de Elga
            uri += "&field4=";
            uri += String(ElgaRetourT);   //Versturen van de retour temeratuur van de Elga
            uri += "&field5=";
            uri += String(COP);           //Versturen van de COP waarde van de Elga
            //  uri += "&field6=";            
            //  uri += String(SUM);   //Versturen van de flow

            Ciao.println(F("Sending data on ThingSpeak Channel"));
            CiaoData data = Ciao.write(connector, url, uri); 

            Ciao.println(WH);
            Ciao.println(Afgifte);
            Ciao.println(ElgaAanvoerT);
            Ciao.println(ElgaRetourT);
            Ciao.println(COP); 
            Ciao.print("KWH: ");    
            Ciao.println(KWH, 4);
            Ciao.print("WH");
            Ciao.println(WH);
            //Ciao.print("SUM");
            //Ciao.println(SUM);

            if (!data.isEmpty()){
                Ciao.println( "State: " + String (data.get(1)));
                Ciao.println( "Response: " + String (data.get(2)));
            }
            else{
                Ciao.println(F("Write Error"));       
            }
        }
};