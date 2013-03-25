#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <iostream>
#include <iomanip>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void loadGPIOI2C() {
    int r=system("gpio load i2c");
    if(r!=0) {
        cout << "gpio returned " << r << ": exiting (" << strerror(errno) << ")" << endl;
        exit(1);
    }
}

int main(int argc, char **argv) {

    cout << "Raw MCP" << endl;
    loadGPIOI2C();
    cout << "GPIO loaded" << endl;
    if(wiringPiSetup()<0) {
        return 1;
    }
    int fd=wiringPiI2CSetup(0x20);
    if(fd<0) {
        cout << "failure opening i2C:exiting (" << strerror(errno) << ")" << endl;
        exit(1);
    }    
    cout << "fd: " << fd << endl;
    // turn on INPUT for all registers

    int ret=wiringPiI2CWriteReg8(fd, 0x00, 0xff);

    cout << "retval for setting IODIR: "<< ret << endl;
    for(int i=0; i<100; i++) {
        cout << "counter: "<< setw(3) << i << " read value: " << hex 
        << wiringPiI2CReadReg8(fd, 0x09) << dec << endl;
        sleep(1);
    }    
    return 0;
}