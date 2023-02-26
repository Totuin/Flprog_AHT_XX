#pragma once
#include <stdint.h>
#include <math.h>
#include "Arduino.h"
#include "flprogUtilites.h"
#include "flprogI2C.h"

#define FLPROG_AHT_CHECK_DEVICE_STATUS_STEP 10
#define FLPROG_AHT_READ_DATA_STEP 11

class FLProgAHT_XX : public FLProgI2cStepWorkSensor
{
public:
    FLProgAHT_XX(FLProgI2C *device);
    void pool();
    float getHumidity() { return hum; };
    float getTemperature() { return temper; };
    void reset(void);

protected:
    virtual void readSensor();

private:
    void checkDeviceStatus();
    void prepareRead();
    void readData();
    void initDevice();
    void createError();
    uint8_t readStatus();
    float temper = 0;
    float hum = 0;
    bool deviceIsInit = false;
};
