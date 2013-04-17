#include <vector>
#include <algorithm>
#include "wiringPi.h"
#include "mcp23008.h"
#include "flare.h"

extern std::vector<MCP23008> mcps;

void flare() {
    MCP23008 mcp=mcps.at(2);
    for(int i=0; i<3; i++) {
        for(int pin=0; pin<3; pin++) {
            mcp.writePin(pin, HIGH);
            delay(100);
            mcp.writePin(pin, LOW);
            delay(100);
        }
    }
}

