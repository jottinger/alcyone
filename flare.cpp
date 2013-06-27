/*
    Copyright 2012- by Joseph B. Ottinger.

    This file is part of Alcyone.

    Alcyone is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Alcyone is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Alcyone.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <vector>
#include <algorithm>
#include "config.h"
#include "wiringPi.h"
#include "mcp23008.h"
#include "flare.h"

extern std::vector<MCP23008> mcps;

int flareTime=DEFAULT_FLARE_TIME;
const int minFlareTime=MIN_FLARE_TIME;
const int maxFlareTime=MAX_FLARE_TIME;

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

