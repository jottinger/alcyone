/*
    Copyright 2012- by Joseph B. Ottinger.

    This file is part of Alcyone.

    Alcyone is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Alcyone is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Alcyone.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <iomanip>
#include <stdlib.h>

#include "serialdevice.h"
#include <wiringSerial.h>

SerialDevice::SerialDevice(std::string _device, int _baudRate):fd(0),baudRate(_baudRate),device(_device) {
    fd=serialOpen(const_cast<char *>(device.c_str()), baudRate);
    if(fd<0) {
        std::cerr << "Error: serialOpen() failed." << std::endl
                  << strerror(errno) << std::endl;
        exit(-1);
    }
    std::cout << "Serial file descriptor: " << fd << std::endl;
}

void SerialDevice::send(unsigned char value) {
//    std::cout << "writing 0x" << std::hex << (int)value << std::dec << std::endl;
    serialPutchar(fd, value);
    serialFlush(fd);
}

unsigned char SerialDevice::read() {
    if(serialDataAvail(fd)>0) {
        return serialGetchar(fd);
    }
    return -1;
}
