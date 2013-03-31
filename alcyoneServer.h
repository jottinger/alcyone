#ifndef ALCYONESERVER_INCLUDED
#define ALCYONESERVER_INCLUDED

#include "midi.h"

const int ALCYONE_SERVER_ERROR=-1;
extern int ALCYONE_SERVER_PORT;

extern const unsigned char MSG_MIDI_RESET;
extern const unsigned char MSG_MIDI_CHANNEL_CHANGE;
extern const unsigned char MSG_MIDI_OCTAVE_CHANGE;
extern const unsigned char MSG_MIDI_TRANSPOSITION_CHANGE;
extern const unsigned char MSG_REQUEST_STATUS;
extern const unsigned char MSG_RESET;

void runServer(MIDI midi);

#endif // ALCYONESERVER_INCLUDED
