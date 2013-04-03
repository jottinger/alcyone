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

package com.redhat.osas.alcyone;

/**
 * User: jottinge
 * Date: 4/1/13
 * Time: 9:38 AM
 */
public enum AlcyoneMessage {
    MSG_MIDI_RESET(0x10),
    MSG_MIDI_CHANNEL_CHANGE(0x20),
    MSG_REQUEST_STATUS(0x30),
    MSG_MIDI_OCTAVE_CHANGE(0x40),
    MSG_MIDI_TRANSPOSITION_CHANGE(0x80),
    MSG_RESET(0xf0);

    private int mask;

    AlcyoneMessage(int value) {
        this.mask = value;
    }

    public int getMask() {
        return mask;
    }
}
