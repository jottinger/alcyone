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

/**
This device is a serial device that defaults to a system baud rate of 38400;
note that for the Raspberry Pi, the serial bus MUST be underclocked such that
the actual baud rate is 31250, the required baud rate for MIDI over Din5.
*/
class MIDI:protected SerialDevice
{
private:    
    int octave;
    int transposition;
    int channel;
    int velocity;
    const int defaultOctave;
    const int defaultTransposition;
    const int defaultChannel;
    const int defaultVelocity;
protected:
    /** 
    This method returns the signum value for a four-bit vector.
    If the value is 0, then -1 is returned; otherwise, it's 1.
    This is how the messages' vector is calculated:
    Strip the lower four bits, and if 0, it's negative.
    */
    inline int getVector(unsigned char v)
    {
        return (v&0x0f)?1:-1;
    }
    /** 
    This method applies a vector to a value, where the value
    will not be higher or lower than the provided boundaries.
    The vector is calculated via getVector(), so the actual 
    message is acceptable.
    */
    void change(int* var, int minVal, int maxVal, unsigned char x);
public:
    /**
    This constructs a serial device conforming to the MIDI spec
    <em>presuming the serial device is underclocked</em>. It also
    sets the current octave and transposition value, the default
    velocity (127), and the default MIDI channel (1).
    */
    MIDI(std::string _device="/dev/ttyAMA0", int _baudRate=38400,
        int _defaultOctave=3,
        int _defaultTransposition=0,
        int _defaultChannel=0,
        int _defaultVelocity=127):
        SerialDevice(_device, _baudRate),
        defaultOctave(_defaultOctave),
        octave(_defaultOctave),
        defaultTransposition(_defaultTransposition),
        transposition(_defaultTransposition),
        defaultChannel(_defaultChannel)
        channel(_defaultChannel),
        defaultVelocity(_defaultVelocity)
        velocity(_defaultVelocity) {}
    /**
    Externally-exposed method to modify the current octave.
    */
    inline void changeOctave(unsigned char direction)
    {
        change(&octave, 2, 8, direction);
    }
    /**
    Externally-exposed method to modify the current transposition
    */
    inline void changeTransposition(unsigned char direction)
    {
        change(&transposition, -11, 11, direction);
    }
    /**
    Externally-exposed method to modify the current channel.
    The channel is internally represented as 0-15, even though
    MIDI refers to channels as being from 1 to 16. The offset
    is applied ONLY for representational purposes. This saves a 
    few nanoseconds here and there by not decrementing the channel
    when it's being used in message construction.
    */
    inline void changeChannel(unsigned char direction)
    {
        change(&channel, 0, 15, direction);
    }
    void noteOn(unsigned int channel, unsigned int note);
    void noteOff(unsigned int channel, unsigned int note);
    /**
    This converts a pedal reference to the adjusted MIDI note.
    */
    inline unsigned int getNote(unsigned int pedal) {
        return pedal+getOctave()*12+getTransposition();
    }
    /**
    This exposes the current octave setting.
    */
    inline int getOctave() {
        return octave;
    }
    /**
    This exposes the current transposition setting.
    */
    inline int getTransposition() {
        return transposition;
    }
    /**
    This exposes the current MIDI channel setting.
    */

    inline int getChannel() {
        return channel;
    }
    void reset();
    /**
    This resets all of the default MIDI settings,
    configured via the constructor.
    */
    void resetToDefaults() {
        channel=defaultChannel;
        transposition=defaultTransposition;
        octave=defaultOctave;
        velocity=defaultVelocity;
        reset();
    }
};

#endif // __MIDI_H_INCLUDED__
