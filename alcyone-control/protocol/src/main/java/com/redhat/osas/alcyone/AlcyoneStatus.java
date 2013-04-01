package com.redhat.osas.alcyone;

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
