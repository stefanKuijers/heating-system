
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS    10

OneWire oneWire(ONE_WIRE_BUS);            // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensorRef(&oneWire);      // Pass our oneWire reference to Dallas Temperature. 

class Temperatures {
    public:
        DallasTemperature sensors = sensorRef;
        DeviceAddress ElgaAanvoert  = { 0x28, 0xAE, 0x68, 0x26, 0x00, 0x00, 0x80, 0x8B }; // arrays to hold device address
        DeviceAddress ElgaRetourt   = { 0x28, 0xFF, 0x01, 0x6A, 0xA3, 0x16, 0x05, 0x65 }; // DeviceAddress insideThermometer;

        void setup() {
            sensors.begin();                                       
            sensors.setResolution(ElgaRetourt, 9);    // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
            sensors.setResolution(ElgaAanvoert, 9);
        }

        void loop() {
            sensors.requestTemperatures(); // Send the command to get temperatures
        }
};