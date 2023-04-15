#include "flprogAHT_XX.h"

FLProgI2C wireDevice(0);
FLProgAHT_XX sensor(&wireDevice);
uint32_t startTime;
uint32_t counter = 0;

void setup()
{
    Serial.begin(9600);
    wireDevice.begin();
    startTime = millis();
}

void loop()
{

    sensor.pool();
    counter++;
    if (flprog::isTimer(startTime, 1000))
    {
        Serial.print("Temperatura - ");
        Serial.println(sensor.getTemperature());
        Serial.print("Hum - ");
        Serial.println(sensor.getHumidity());
        Serial.print("Error - ");
        Serial.println(sensor.getError());
        Serial.print("countCiclesOnSec - ");
        Serial.println(counter);
        Serial.println();
        startTime = millis();
        counter = 0;
        sensor.read();
    }
}
