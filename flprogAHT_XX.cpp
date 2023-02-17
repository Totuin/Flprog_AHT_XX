#include "flprogAHT_XX.h"

uint8_t eSensorCalibrateCmd[3] = {0xE1, 0x08, 0x00};
// uint8_t eSensorNormalCmd[3] = {0xA8, 0x00, 0x00};
uint8_t eSensorMeasureCmd[3] = {0xAC, 0x33, 0x00};
uint8_t eSensorResetCmd = 0xBA;

FLProgAHT_XX::FLProgAHT_XX(FLProgI2C *device)
{
    i2cDevice = device;
    codeError = FLPROG_SENSOR_NOT_READY_ERROR;
    addres = 0x38;
}

void FLProgAHT_XX::pool()
{
    checkReadPeriod();
    checkDelay();
    checkNeededRead();
    if (step == FLPROG_AHT_CHECK_DEVICE_STATUS_STEP)
    {
        checkDeviceStatus();
    }

    if (step == FLPROG_AHT_READ_DATA_STEP)
    {
        readData();
    }
}

void FLProgAHT_XX::initDevice()
{
    if (!(i2cDevice->findAddr(addres)))
    {
        codeError = FLPROG_SENSOR_DEVICE_NOT_FOUND_ERROR;
        createError();
        return;
    }
    codeError = i2cDevice->fullWrite(addres, eSensorCalibrateCmd, 3);
    if (codeError)
    {
        createError();
        return;
    }
    gotoStepWithDelay(FLPROG_AHT_CHECK_DEVICE_STATUS_STEP, 500);
}

void FLProgAHT_XX::createError()
{
    deviceIsInit = false;
    gotoStepWithDelay(FLPROG_SENSOR_WAITING_READ_STEP, 500);
}

void FLProgAHT_XX::checkDeviceStatus()
{
    if ((readStatus() & 0x68) == 0x08)
    {
        deviceIsInit = true;
        codeError = FLPROG_SENSOR_NOT_ERROR;
        readSensor();
    }
    else
    {
        deviceIsInit = false;
        codeError = FLPROG_SENSOR_NOT_READY_ERROR;
        createError();
    }
}

void FLProgAHT_XX::readSensor()
{
    if (!deviceIsInit)
    {
        initDevice();
        return;
    }
    prepareRead();
}

void FLProgAHT_XX::prepareRead()
{
    codeError = i2cDevice->fullWrite(addres, eSensorMeasureCmd, 3);
    if (codeError)
    {
        createError();
        return;
    }
    gotoStepWithDelay(FLPROG_AHT_READ_DATA_STEP, 150);
}

void FLProgAHT_XX::readData()
{
    uint32_t result;
    uint32_t temp[6];
    codeError = i2cDevice->fullRead(addres, temp, 6);
    if (codeError)
    {
        createError();
        return;
    }
    result = ((temp[1] << 16) | (temp[2] << 8) | temp[3]) >> 4;
    hum = result;
    if (hum == 0)
    {
        hum = 0;
    }
    else
    {
        hum = hum * 100 / 1048576;
    }
    result = ((temp[3] & 0x0F) << 16) | (temp[4] << 8) | temp[5];
    temper = result;
    temper = ((200 * temper) / 1048576) - 50;
    step = FLPROG_SENSOR_WAITING_READ_STEP;
}

uint8_t FLProgAHT_XX::readStatus()
{
    uint8_t result = 0;
    if (i2cDevice->fullRequestFrom(addres, 1))
    {
        createError();
        return 0;
    }
    result = i2cDevice->read();
    return result;
}

void FLProgAHT_XX::reset(void)
{
    codeError = i2cDevice->fullWrite(addres, eSensorResetCmd);
    if (codeError)
    {
        createError();
        return;
    }
    gotoStepWithDelay(FLPROG_SENSOR_WAITING_READ_STEP, 20);
}
