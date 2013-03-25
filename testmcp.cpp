#include <iostream>
#include <vector>
#include <algorithm>
#include "mcp23008.h"
#include <wiringPi.h>
#include <unistd.h>

using namespace std;

void setMode(MCP23008 mcp) {
    mcp.modeAll(MODE_OUTPUT);
}

int state=0;

void invertState(MCP23008 mcp) {
    for(int i=10; i>0; i--) {
        mcp.writePin(0, 1);
        delay(i);
        mcp.writePin(0,0);
    }
    delay(10);
    for(int i=0; i<10;i++) {
        mcp.writePin(0, 1);
        delay(i);
        mcp.writePin(0,0);
    }
    }

int main(int argc, char **argv) {

    vector<MCP23008> mcps;
    mcps.push_back(MCP23008(0));
    mcps.push_back(MCP23008(1));
    mcps.push_back(MCP23008(2));

    for_each(mcps.begin(), mcps.end(), setMode);

    while(true) {
        for_each(mcps.begin(), mcps.end(), invertState);
        delay(100);
    }

    return 0;
}