#include <vector>
#include <algorithm>
#include "wiringPi.h"
#include "mcp23008.h"
#include "flare.h"

extern std::vector<MCP23008> mcps;

int flareTime=600;
const int minFlareTime=100;
const int maxFlareTime=2000;

void flare() {
    MCP23008 mcp=mcps.at(2);
    while(1==1) {
        flareTime=std::min(std::max(minFlareTime, flareTime), maxFlareTime);
        for(int pin=0; pin<3; pin++) {
            mcp.writePin(pin, HIGH);
            delay(flareTime);
            mcp.writePin(pin, LOW);
            delay(100);
        }
    }
}

