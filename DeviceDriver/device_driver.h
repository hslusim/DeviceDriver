#pragma once
#include "flash_memory_device.h"
#include <exception>

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);
    void preconditionCheck(long address);
    void postConditionCheck(int ret, long address);

protected:
    FlashMemoryDevice* m_hardware;
    const int TEST_TRY_CNT = 4;
};

class ReadFiveTimeFail : public std::exception {};
class WriteFailException : public std::exception {};