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
#include <iomanip>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "mcp23008.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

static int initialized=0;

void MCP23008::initialize() {
    if(!initialized) {
        if((fd=wiringPiI2CSetup(address))<0) {
            std::cout << "Error initializing I2C at address 0x"
                      << std::hex << address << std::endl
                      << std::dec
                      << strerror(errno) << std::endl;
        }
    }
}

void MCP23008::modeAll(MODE mode) {
    int val=(mode!=MODE_INPUT)?0:0xff;
    wiringPiI2CWriteReg8(fd, MCP_IODIR, val);
}

int MCP23008::read() {
    return (lastRead=wiringPiI2CReadReg8(fd, MCP_GPIO));
}

void MCP23008::writeRegister(MCP_REGISTER _register, int bit, int state) {
    if(bit>7) {
        return;
    }
    int val=read();
    if(state) {
        // we want to turn it on
        val=val | (1<<bit);
    } else {
        val= val & (255-(1<<bit));
    }
    wiringPiI2CWriteReg8(fd, _register, val);
}

void MCP23008::writePin(int bit, int state) {
    writeRegister(MCP_GPIO, bit, state);
}

void MCP23008::pinMode(int pin, MODE mode) {
    writeRegister(MCP_IODIR, pin, mode);
}

int MCP23008::readPin(int pin) {
    if(pin>7) {
        return 0;
    }
    return bit(read(), pin);
}
