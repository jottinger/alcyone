#ifndef ALCYONESERVER_INCLUDED
#define ALCYONESERVER_INCLUDED
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

const int ALCYONE_SERVER_ERROR=-1;
extern int ALCYONE_SERVER_PORT;

/*
const unsigned char MSG_MIDI_RESET=0x10;
const unsigned char MSG_MIDI_CHANNEL_CHANGE=0x20;
const unsigned char MSG_MIDI_OCTAVE_CHANGE=0x40;
const unsigned char MSG_MIDI_TRANSPOSITION_CHANGE=0x80;
const unsigned char MSG_REQUEST_STATUS=0x30;
const unsigned char MSG_RESET=0xf0;
*/
enum ALCYONE_MESSAGE {
    MSG_MIDI_RESET=0x10,
    MSG_MIDI_CHANNEL_CHANGE=0x20,
    MSG_REQUEST_STATUS=0x30,
    MSG_MIDI_OCTAVE_CHANGE=0x40,
    MSG_MIDI_TRANSPOSITION_CHANGE=0x80,
    MSG_RESET=0xf0};

void runServer(MIDI midi);

#endif // ALCYONESERVER_INCLUDED
