#include "mcp23008.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <iostream>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

static int initialized=0;

void MCP23008::initialize() {
  if(!initialized) {
    if(wiringPiI2CSetup(address)<0) {
      cout << "Error initializing I2C at address " << address << endl
        << strerror(errno) << endl;
    }  
  }
}