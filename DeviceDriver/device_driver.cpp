#include "device_driver.h"

class exceptionFive : public std::exception {};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int result = (int)(m_hardware->read(address));
    for (int turn = 0; turn < TEST_TRY_CNT; turn++) {
        int testvalue = (int)(m_hardware->read(address));
        if (result != testvalue) throw exceptionFive();
    }
    return (int)(m_hardware->read(address));
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}