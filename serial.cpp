#include <iostream>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <iomanip>

#include "serial.h"
#include <wiringSerial.h>

SerialDevice::SerialDevice(std::string _device, int _baudRate):fd(0),baudRate(_baudRate),device(_device) {
}
