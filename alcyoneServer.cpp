#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include "alcyoneServer.h"
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
extern bool verbose;

int ALCYONE_SERVER_PORT=8090;

int readBuffer(int socketFd, unsigned char* buffer)
{
    int r=recv(socketFd, buffer, 1, 0);
    if(r==0)
    {
        return ALCYONE_SERVER_ERROR;
    }
    return 0;
}

void runServer(MIDI midi)
{
    int sd, newSd;
    socklen_t cliLen;

    struct sockaddr_in cliAddr, servAddr;


    /* create socket */
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd<0)
    {
        std::cerr << "cannot open socket " << std::endl;
        exit(-1);
    }

    /* bind server port */
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(ALCYONE_SERVER_PORT);

    if(bind(sd, (struct sockaddr *) &servAddr, sizeof(servAddr))<0)
    {
        std::cerr << "cannot bind port " << ALCYONE_SERVER_PORT << std::endl;
        exit(-1);
    }

    listen(sd,5);

    while(1)
    {
        if(verbose) {
            std::cout << "Alcyone: waiting for data on TCP/IP port: " 
                << ALCYONE_SERVER_PORT << std::endl;
        }
        cliLen = sizeof(cliAddr);
        newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen);
        if(newSd<0)
        {
            std::cerr << "cannot accept connection " << std::endl;
            exit(-1);
        }

        unsigned char buffer;

        /* receive segments */
        unsigned char statusBuffer[3];
        while(readBuffer(newSd, &buffer)!=ALCYONE_SERVER_ERROR)
        {
            if(verbose==true) {
                std::cout << "Received message: " << std::setbase(16)
                          << (int)buffer << std::setbase(10);
            }
            switch(buffer & 0xf0)
            {
            case MSG_RESET:
                if(verbose==true) {
                    std::cout << "(MSG_RESET)";
                }
                midi.resetToDefaults();
                break;
            case MSG_MIDI_RESET:
                if(verbose==true) {
                    std::cout << "(MSG_MIDI_RESET)";
                }
                midi.reset();
                break;
            case MSG_REQUEST_STATUS:
                if(verbose==true) {
                    std::cout << "(MSG_REQUEST_STATUS)";
                }
                statusBuffer[0]=midi.getOctave();
                statusBuffer[1]=midi.getTransposition();
                statusBuffer[2]=midi.getChannel();
                send(newSd, &statusBuffer, 3, 0);
                break;
            case MSG_MIDI_OCTAVE_CHANGE:
                if(verbose==true) {
                    std::cout << "(MSG_MIDI_OCTAVE_CHANGE)";
                }
                midi.changeOctave(buffer);
                break;
            case MSG_MIDI_CHANNEL_CHANGE:
                if(verbose==true) {
                    std::cout << "(MSG_MIDI_CHANNEL_CHANGE)";
                }
                midi.changeChannel(buffer);
                break;
            case MSG_MIDI_TRANSPOSITION_CHANGE:
                if(verbose==true) {
                    std::cout << "(MSG_MIDI_TRANSPOSITION_CHANGE)";
                }
                midi.changeTransposition(buffer);
                break;
            default:
                /* unknown message type, say so */
                std::cerr << "Unknown message received from controller: "
                          << std::setbase(1) << buffer << std::setbase(10)
                          << std::endl;
                break;
            }
            if(verbose==true) {
                std::cout << std::endl;
            }
        } /* while(read_line) */

    } /* while (1) */

}
