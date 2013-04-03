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

#ifndef __MIDI_H_INCLUDED__
#define __MIDI_H_INCLUDED__ 1

#include <algorithm>
#include "serialdevice.h"

class MIDI:protected SerialDevice
{
private:
    int octave;
    int transposition;
    int channel;
    int velocity;
protected:
    inline int getVector(unsigned char v)
    {
        return (v&0x0f)?1:-1;
    }
    inline void change(int* var, int minVal, int maxVal, unsigned char x)
    {
        int v=getVector(x);
        *var+=v;
        *var=std::max(minVal, std::min(*var, maxVal));
    }
public:
    MIDI(std::string _device="/dev/ttyAMA0", int _baudRate=38400):
    SerialDevice(_device, _baudRate),
    octave(3),
    transposition(0),
    channel(1),
    velocity(127) {}
    void changeOctave(unsigned char direction)
    {
        change(&octave, 2, 8, direction);
    }
    void changeTransposition(unsigned char direction)
    {
        change(&transposition, -11, 11, direction);
    }
    void changeChannel(unsigned char direction)
    {
        change(&channel, 1, 16, direction);
    }
    void noteOn(unsigned char note);
    void noteOff(unsigned char note);
    inline unsigned getOctave() { return octave; }
    inline int getTransposition() { return transposition; }
    inline int getChannel() { return channel; }
    void reset();
    void resetToDefaults() {
        channel=1;
        transposition=0;
        octave=3;
        velocity=127;
        reset();
    }
};

#endif // __MIDI_H_INCLUDED__
