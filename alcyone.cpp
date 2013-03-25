#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "mcp23008.h"

#include "wiringPi.h"

std::vector<MCP23008> mcps;

int octave;

void setup();
void flare();
void loop();

int main(int argc, char **argv) {
    setup();
    loop();
    return 0;
}

void setup() {
// set up the two input I2C chips
    for(int i=0; i<2; i++) {
        MCP23008 mcp(i);
        mcp.modeAll(MODE_INPUT);
        mcps.push_back(mcp);
    }
    MCP23008 util(2);
    util.pinMode(0, MODE_OUTPUT);
    util.pinMode(1, MODE_OUTPUT);
    util.pinMode(2, MODE_OUTPUT);
    util.pinMode(3, MODE_INPUT);
    mcps.push_back(util);
    flare();
}

void loop() {
}

int state=1;

void flare() {
    MCP23008 mcp=mcps.at(2);
    for(int count=0; count<4; count++) {
        for(int state=1; state>-1; state--) {
            for(int pin=0; pin<3; pin++) {
                mcp.writePin(pin, state);
                delay(75);
            }
        }
    }
}