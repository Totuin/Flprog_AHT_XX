#include "flprogAHT_XX.h"

FLProgI2C wireDevice(0);
FLProgAHT_XX sensor(&wireDevice);
uint32_t startTime;
uint32_t maxCicleTime = 0;
uint32_t startCicleTime = 0;
uint32_t cicleTime = 0;

void setup()
{
    Serial.begin(9600);
    wireDevice.begin();
    startTime = millis() + 3000;
}

void loop()
{

    if (flprog::isTimer(startTime, 1000))
    {
        Serial.print("Temperatura - ");
        Serial.println(sensor.getTemperature());
        Serial.print("Hum - ");
        Serial.println(sensor.getHumidity());
        Serial.print("Error - ");
        Serial.println(sensor.getError());
        Serial.print("maxCicleTime - ");
        Serial.println(maxCicleTime);
        Serial.println();
        startTime = millis();
    }
    else
    {

        startCicleTime = micros();
        sensor.read();
        sensor.pool();
        cicleTime = micros() - startCicleTime;
        maxCicleTime = max(maxCicleTime, cicleTime);
    }
}