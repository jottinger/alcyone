#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "mcp23008.h"

std::vector<MCP23008> mcps;

void setup();

int main(int argc, char **argv) {
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
}