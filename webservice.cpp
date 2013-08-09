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

#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <map>
#include <stdexcept>
#include "midi.h"
#include "web++.hpp"
#include "webservice.h"
#include "log.h"

extern bool verbose;

int ALCYONE_SERVER_PORT=8090;

MIDI* state;

void logHttpRequest(WPP::Request* req, WPP::Response* res)
{
    std::cout << req->method << " " << req->path << std::endl;

    std::cout << "Headers:" << std::endl;

    std::map<std::string, std::string>::iterator iter;
    for (iter = req->headers.begin(); iter != req->headers.end(); ++iter)
    {
        std::cout << iter->first << " = " << iter->second << std::endl;
    }

    std::cout << "Query:" << std::endl;

    for (iter = req->query.begin(); iter != req->query.end(); ++iter)
    {
        std::cout << iter->first << " = " << iter->second << std::endl;
    }

    std::cout << "Cookies: " << req->cookies.size() << std::endl;

    for (iter = req->cookies.begin(); iter != req->cookies.end(); ++iter)
    {
        std::cout << iter->first << " = " << iter->second << std::endl;
    }
}

/**
 This method handles all external requests.

 First, it checks the length of the message; we only handle a 
 message that can be represented in a single byte presently,
 so if it's too long, we know we can discard it out of hand.

 If it's small enough, and it's a number, we pass the header
 (the first nybble) through a switch case, dispatching the
 argument as necessary.

 Regardless of error condition, we return the status as a set
 of three lines: octave, transposition, then channel. Channel is
 incremented by one, because the internal values are 0-15 and 
 the MIDI spec refers to channels 1-16 -- a lot like how days of
 the month are handled, with an offset.
 */
void handleRequest(WPP::Request* req, WPP::Response* res)
{
    if(verbose==true) {
        logHttpRequest(req, res);
    }

    const char *data=req->query.at("message").c_str();
    if(strlen(data)<6) {
        int message=atoi(data);
        try
        {

            switch(message & 0xf0)
            {
            case MSG_RESET:
                if(verbose==true)
                {
                    std::cout << "(MSG_RESET)" << std::endl;
                }
                state->resetToDefaults();
                break;
            case MSG_MIDI_RESET:
                if(verbose==true)
                {
                    std::cout << "(MSG_MIDI_RESET)" << std::endl;
                }
                state->reset();
                break;
            case MSG_REQUEST_STATUS:
                if(verbose==true)
                {
                    std::cout << "(MSG_REQUEST_STATUS)" << std::endl;
                }
                break;
            case MSG_MIDI_OCTAVE_CHANGE:
                if(verbose==true)
                {
                    std::cout << "(MSG_MIDI_OCTAVE_CHANGE)" << message << std::endl;
                }
                state->changeOctave(message);
                break;
            case MSG_MIDI_CHANNEL_CHANGE:
                if(verbose==true)
                {
                    std::cout << "(MSG_MIDI_CHANNEL_CHANGE)" << message << std::endl;
                }
                state->changeChannel(message);
                break;
            case MSG_MIDI_TRANSPOSITION_CHANGE:
                if(verbose==true)
                {
                    std::cout << "(MSG_MIDI_TRANSPOSITION_CHANGE) " << message << std::endl;
                }
                state->changeTransposition(message);
                break;
            default:
                /* unknown message type, say so */
                std::cerr << "Unknown message received from controller: "
                          << std::setbase(1) << message << std::setbase(10)
                          << std::endl;
                break;
            }
        }
        catch(const std::out_of_range& e)
        {
            // write an error
            if(verbose)
            {
                std::cerr << "Error: invalid request (no 'message')" << std::endl;
            }
        }
    }
// respond with the current status, no matter what
    res->body << state->getOctave() << std::endl;
    res->body << state->getTransposition() << std::endl;
    res->body << state->getChannel()+1 << std::endl;
}

void runServer(MIDI *midi)
{
    state=midi;
    WPP::Server server;
    server.get("/", &handleRequest);
    server.start(ALCYONE_SERVER_PORT);
}
