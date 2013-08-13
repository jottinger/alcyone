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

#include "midi.h"
#include <iostream>
#include "log.h"

extern int verbose;

void MIDI::change(int* var, int minVal, int maxVal, unsigned char x)
{
    int v=getVector(x);

    if(verbose) {
        std::cout << std::endl << "old value " << *var << " min " << minVal << " max " << maxVal
                  << " vector " << v;

    }
    *var+=v;
    *var=std::max(minVal, std::min(*var, maxVal));
    if(verbose) {
        std::cout << " new value " << *var << std::endl;
    }
}

/**
 This sends the ACTUAL NOTE as a note-on. NOT calculated.
 If you want the offset note, use MIDI::getNote(), whose 
 purpose it is to calculate this value.
 */
void MIDI::noteOn(unsigned int _channel, unsigned int _note) {
    send(0x90 | _channel);
    send(_note);
    send(velocity & 127);
    if(verbose) {
        std::cout << "Note on: note " << _note
                  << ", velocity " << (velocity & 127) << std::endl;
    }
}

/**
 This sends the ACTUAL NOTE as a note-off. NOT calculated.
 */
void MIDI::noteOff(unsigned int _channel, unsigned int _note) {
    send(0x80 | _channel);
    send(_note);
    send(0);
    if(verbose) {
        std::cout << "Note off: note " << _note
                  << ", velocity " << (velocity & 127) << std::endl;
    }
}

/** 
 Sends system resets: all controllers, all sounds off, all notes off
*/
void MIDI::reset() {
    send(0xb0 | channel); // system reset for channel
    send(121); // reset all controllers
    send(0x00);

    send(0xb0 | channel); // system reset for channel
    send(120); // sound off
    send(0x00);

    send(0xb0 | channel); // system reset for channel
    send(123); // all notes off
    send(0x00);
}
