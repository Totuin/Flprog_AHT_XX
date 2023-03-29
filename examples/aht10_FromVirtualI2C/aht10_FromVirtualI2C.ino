#include "flprogAHT_XX.h"

FLProgI2C wireDevice;
FLProgTCA9548A commutator(&wireDevice);
FLProgVirtualI2C virtualWire(&commutator, 6);
FLProgVirtualI2C virtualWire1(&commutator, 2);


FLProgAHT_XX sensor(&virtualWire);
FLProgAHT_XX sensor1(&virtualWire1);
uint32_t startTime;
uint32_t startTime1;
uint32_t maxCicleTime = 0;
uint32_t startCicleTime = 0;
uint32_t cicleTime = 0;

void setup()
{
  Serial.begin(9600);
  wireDevice.begin();
  virtualWire.begin();
  virtualWire1.begin();
  startTime = millis();
  startTime1 = millis();
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
    Serial.println();
    Serial.print("Temperatura1 - ");
    Serial.println(sensor1.getTemperature());
    Serial.print("Hum1 - ");
    Serial.println(sensor1.getHumidity());
    Serial.print("Error1 - ");
    Serial.println(sensor1.getError());
    Serial.print("maxCicleTime - ");
    Serial.println(maxCicleTime);
    Serial.println();
    Serial.println();
    Serial.println();
    startTime = millis();
    sensor.read();
    sensor1.read();
  }
  else
  {
    if (flprog::isTimer(startTime1, 2000))
    {
      startCicleTime = micros();
      sensor.pool();
      sensor1.pool();
      cicleTime = micros() - startCicleTime;
      maxCicleTime = max(maxCicleTime, cicleTime);
    }
    else
    {
      sensor.pool();
      sensor1.pool();
    }
  }
}