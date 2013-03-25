#include "mcp23008.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <iostream>
#include <iomanip>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

static int initialized=0;

void MCP23008::initialize() {
    if(!initialized) {
        if((fd=wiringPiI2CSetup(address))<0) {
            cout << "Error initializing I2C at address 0x" << hex << address << endl
                 << dec
                 << strerror(errno) << endl;
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

void MCP23008::writeBit(int bit, int state) {
    if(bit>7) {
        return;
    }
    int val=read();
    if(state) {
        // we want to turn it on
        val=val | (1<<bit);
    } else {
        val= val & !(1<<bit);
    }
    wiringPiI2CWriteReg8(fd, MCP_GPIO, val);
}