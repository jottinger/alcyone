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
