#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <iostream>
#include <iomanip>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv) {

    cout << "Raw MCP" << endl;
    if(wiringPiSetup()<0) {
        return 1;
    }
    int fd=wiringPiI2CSetup(0x20);
    if(fd<0) {
        cout << "failure opening i2C:exiting (" << strerror(errno) << ")" << endl;
        exit(1);
    }
    cout << "fd: " << fd << endl;
    int fd1=wiringPiI2CSetup(0x21);
    if(fd1<0) {
        cout << "failure opening i2C:exiting (" << strerror(errno) << ")" << endl;
        exit(1);
    }
    cout << "fd1: " << fd1 << endl;
    // turn on OUTPUT for all registers

    int ret=wiringPiI2CWriteReg8(fd, 0x00, 0x00); // all output
    if(ret<<0) {
        cout << "Error writing 8 bits: " << ret << endl
             << strerror(errno) << endl;
        exit(1);
    }
    ret=wiringPiI2CWriteReg8(fd1, 0x00, 0x00);
    if(ret<<0) {
        cout << "Error writing 8 bits: " << ret << endl
             << strerror(errno) << endl;
        exit(1);
    }
    int state=0;
    while(true) {
        state=1-state;
        wiringPiI2CWriteReg8(fd, 0x09, state*255);
        delay(50);
        wiringPiI2CWriteReg8(fd1, 0x09, state*255);
        delay(50);
    }
    return 0;
}