#include <BH1750.h>
#include <Wire.h>

BH1750 lightMeter(0x23);

void setup()
{

    Serial.begin(115200);
    Wire.begin();

    if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE))
    {
        Serial.println(F("BH1750 Advanced begin"));
    }
    else
    {
        Serial.println(F("Error initialising BH1750"));
    }
}

void loop()
{
    if (lightMeter.measurementReady())
    {
        float lux = lightMeter.readLightLevel();
        Serial.print("Light: ");
        Serial.print(lux);
        Serial.println(" lx");
    }
}