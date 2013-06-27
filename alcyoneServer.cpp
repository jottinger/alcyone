#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <map>
#include <stdexcept>
#include "midi.h"
#include "web++.hpp"
#include "alcyoneServer.h"
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
    res->body << state->getChannel() << std::endl;
}

void runServer(MIDI *midi)
{
    state=midi;
    WPP::Server server;
    server.get("/", &handleRequest);
    server.start(ALCYONE_SERVER_PORT);
}
