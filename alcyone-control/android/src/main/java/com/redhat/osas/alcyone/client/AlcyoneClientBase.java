package com.redhat.osas.alcyone.client;

import com.redhat.osas.alcyone.AlcyoneActivity;
import com.redhat.osas.alcyone.AlcyoneMessage;
import com.redhat.osas.alcyone.AlcyoneVector;

/**
 * User: jottinge
 * Date: 4/5/13
 * Time: 2:04 PM
 */
abstract class AlcyoneClientBase implements AlcyoneClient {
    final String host;
    final int port;
    final AlcyoneActivity activity;

    abstract void execute(AlcyoneMessage msg, int... values);

    AlcyoneClientBase(AlcyoneActivity activity, String host, int port) {
        this.host = host;
        this.activity = activity;
        this.port = port;
    }

    public void updateStatus() {
        execute(AlcyoneMessage.MSG_REQUEST_STATUS);
    }

    @Override
    public void midiReset() {
        execute(AlcyoneMessage.MSG_MIDI_RESET);
    }

    @Override
    public void reset() {
        execute(AlcyoneMessage.MSG_RESET);
    }

    @Override
    public void changeOctave(AlcyoneVector vector) {
        execute(AlcyoneMessage.MSG_MIDI_OCTAVE_CHANGE, vector.getMask());
    }

    @Override
    public void changeTransposition(AlcyoneVector vector) {
        execute(AlcyoneMessage.MSG_MIDI_TRANSPOSITION_CHANGE, vector.getMask());
    }

    @Override
    public void changeChannel(AlcyoneVector vector) {
        execute(AlcyoneMessage.MSG_MIDI_CHANNEL_CHANGE, vector.getMask());
    }
}
