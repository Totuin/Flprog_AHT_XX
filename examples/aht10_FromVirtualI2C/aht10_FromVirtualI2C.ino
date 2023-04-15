#include "flprogAHT_XX.h"

FLProgI2C wireDevice;
FLProgTCA9548A commutator(&wireDevice);
FLProgVirtualI2C virtualWire(&commutator, 2);
FLProgVirtualI2C virtualWire1(&commutator, 6);


FLProgAHT_XX sensor(&virtualWire);
FLProgAHT_XX sensor1(&virtualWire1);
uint32_t startTime = 0;
uint32_t  counter = 0;


void setup()
{
  Serial.begin(9600);
  wireDevice.begin();
  virtualWire.begin();
  virtualWire1.begin();
  startTime = millis();

}

void loop()
{

  sensor.pool();
  sensor1.pool();
  counter++;

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
    Serial.print("countCiclesOnSec - ");
    Serial.println(counter);
    Serial.println();
    Serial.println();
    Serial.println();
    startTime = millis();
    sensor.read();
    sensor1.read();
    counter = 0;
  }
}