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

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <boost/thread.hpp>

#include "mcp23008.h"
#include "alcyoneServer.h"
#include "debounce.h"
#include "wiringPi.h"
#include "midi.h"

std::vector<MCP23008> mcps;
MIDI midi;
Debouncer debouncer[13];
int previousState[13];
int exitAlcyone=0;

void setup();
void shutdown();
void flare();
void loop();

int main(int argc, char **argv) {
    setup();

    boost::thread t(loop);
    boost::thread s(runServer,midi);
    t.join();
    s.join();
    shutdown();
    return 0;
}

void shutdown() {
}

void setup() {
    // initialize the socket

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
    for(int i=0; i<13; i++) {
        previousState[i]=0;
    }
}

void loop() {
    int data[2];
    data[0]=mcps[0].read();
    data[1]=mcps[1].read();
    for(int pin=0; pin<13; pin++) {
        int datum=data[pin/8];
        int state=debouncer[pin].debounce(decode(datum, pin%8));
        if(state!=previousState[pin]) {
            if(previousState[pin]) { // new state: OFF
                midi.noteOff(12-pin); // when wired, pin 0 is the HIGH C
            } else {
                midi.noteOn(12-pin);
            }
            previousState[pin]=state;
        }
    }
}


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

