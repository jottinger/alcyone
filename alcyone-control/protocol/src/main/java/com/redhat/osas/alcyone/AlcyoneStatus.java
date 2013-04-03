package com.redhat.osas.alcyone;
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

/**
 * User: jottinge
 * Date: 4/1/13
 * Time: 11:04 AM
 */
public final class AlcyoneStatus {
    final int octave;
    final int channel;
    final int transposition;

    public AlcyoneStatus(int octave, int transposition, int channel) {
        this.octave = octave;
        this.channel = channel;
        this.transposition = transposition;
    }

    public int getOctave() {
        return octave;
    }

    public int getChannel() {
        return channel;
    }

    public int getTransposition() {
        return transposition;
    }
}
