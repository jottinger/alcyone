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

void MIDI::noteOn(unsigned char note) {
    send(0x90+channel-1);
    send(note+octave*12+transposition);
    send(velocity & 127);
}

void MIDI::noteOff(unsigned char note) {
    send(0x80+channel-1);
    send(note+octave*12+transposition);
    send(0);
}

void MIDI::reset() {
    send(0xb0+channel-1); // system reset for channel
    send(121); // not sure why 121 is recommended here.
    send(0x00);
}
