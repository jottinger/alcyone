#include <iostream>

using namespace std;

#include "alcyone.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int serialFd;

int main() {
    setup();
    loop();
    return 0;
}

void setup() {
    if(wiringPiSetup()==-1) {
        cout << "Error: wiringPiSetup() failed." << endl
             << strerror(errno) << endl;
        exit(-1);
    }

    if( (serialFd = serialOpen("/dev/ttyAMA0", 38400))<0) {
        cout << "Error: serialOpen() failed." << endl
             << strerror(errno) << endl;
        exit(-1);
    }
}

void loop() {

}