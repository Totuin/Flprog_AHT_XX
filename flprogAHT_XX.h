#pragma once
#include <stdint.h>
#include <math.h>
#include "Arduino.h"
#include "flprogUtilites.h"

#define FLPROG_AHT_WAITING_READ_STEP 0
#define FLPROG_AHT_WAITING_DELAY 1
#define FLPROG_AHT_CHECK_DEVICE_STATUS_STEP 2
#define FLPROG_AHT_READ_DATA_STEP 3

#define FLPROG_AHT_NOT_ERROR 0
#define FLPROG_AHT_DEVICE_NOT_READY_ERROR 1
#define FLPROG_AHT_DEVICE_NOT_FOUND_ERROR 2
#define FLPROG_AHT_DEVICE_NOT_CORRECT_BUS_NUMBER_ERROR 3
#define FLPROG_AHT_DEVICE_NOT_CORRECT_DEVICE_ADDRESS_ERROR 4
#define FLPROG_AHT_DEVICE_NOT_DEFINED_ERROR 5
#define FLPROG_AHT_DEVICE_NOT_CORRECT_DATA_ERROR 6

class FLProgAHT_XX
{
public:
    FLProgAHT_XX(FLProgI2C *device);
    void pool();
    float getHumidity() { return hum; };
    float getTemperature() { return temper; };
    uint8_t getError() { return codeError; };
    uint8_t readStatus();
    void readSensor();
    void reset(void);
    void read();

private:
    void checkDelay();
    void checkDeviceStatus();
    void prepareRead();
    void readData();
    void initDevice();
    void createError();
    FLProgI2C *i2cDevice;
    uint8_t codeError = FLPROG_AHT_DEVICE_NOT_READY_ERROR;
    uint8_t addres = 0x38;
    uint8_t step = FLPROG_AHT_WAITING_READ_STEP;
    uint32_t speed = FLPROG_I2CSPEED;
    float temper = 0;
    float hum = 0;
    bool isNeededRead = true;
    bool deviceIsInit = false;
    uint32_t startDelay;
    uint32_t sizeDelay;
    uint8_t stepAfterDelay;
};
