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
