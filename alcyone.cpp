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
#include <boost/program_options.hpp>

#include "mcp23008.h"
#include "alcyoneServer.h"
#include "debounce.h"
#include "wiringPi.h"
#include "midi.h"
#include "flare.h"
#include "log.h"

namespace options = boost::program_options;

std::vector<MCP23008> mcps;
options::options_description desc("Allowed options");
options::variables_map vm;
MIDI midi;
Debouncer debouncer[13];
int previousState[13];
int exitAlcyone=0;
bool verbose;
extern int ALCYONE_SERVER_PORT;
void setup();
void shutdown();
void loop();

int main(int argc, char **argv) {
    desc.add_options()
    ( "help", "produce help message")
    ( "verbose", options::value<bool>(&verbose)->default_value(true),
      "verbose mode" )
    ( "port", options::value<int>(&ALCYONE_SERVER_PORT)->default_value(8090),
      "server port" )
    ;
    options::store(options::parse_command_line(argc, argv, desc), vm);
    options::notify(vm);

    if(vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    setup();

    boost::thread t(loop);
    boost::thread s(runServer,&midi);
    boost::thread u(flare);

    t.join();
    s.join();

    shutdown();
    return 0;
}

void shutdown() {
}

void setup() {
    // set up syslog
    std::clog.rdbuf(new Log("alcyone", LOG_LOCAL0));
    
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
    for(int i=0; i<13; i++) {
        previousState[i]=0;
    }
}

void loop() {
    int counter=0;
    while(true) {
        int data[2];
        data[0]=mcps[0].read();
        data[1]=mcps[1].read();
        counter++;
        if(counter%1276==0) {
            flareTime++;
            std::clog << kLogNotice << "new flare time: " << flareTime << std::endl;
        }
        for(int pin=0; pin<13; pin++) {
            int datum=data[pin/8];
            int state=debouncer[pin].debounce(decode(datum, pin%8));
            if(verbose==2) {
                std::cout << state;
            }
            if(state!=previousState[pin]) {
                flareTime-=2;
                std::clog << kLogNotice << "new flare time: " << flareTime << std::endl;
                if(previousState[pin]) { // new state: OFF
                    midi.noteOff(12-pin); // when wired, pin 0 is the HIGH C
                } else {
                    midi.noteOn(12-pin);
                }
                previousState[pin]=state;
            }
        }
        if(verbose==2) {
            std::cout << std::endl;
        }
    }
}



