#include <iostream>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <iomanip>
#include <stdlib.h>

#include "serial.h"
#include <wiringSerial.h>

SerialDevice::SerialDevice(std::string _device, int _baudRate):fd(0),baudRate(_baudRate),device(_device) {
    fd=serialOpen(const_cast<char *>(device.c_str()), baudRate);
    if(fd<0) {
        std::cout << "Error: serialOpen() failed." << std::endl
                  << strerror(errno) << std::endl;
        exit(-1);
    }
}

void SerialDevice::send(unsigned char value) {
    serialPutchar(fd, value);
}
unsigned char SerialDevice::read() {
    if(serialDataAvail(fd)>0) {
        return serialGetchar(fd);
    }
    return -1;
}
