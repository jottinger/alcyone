package com.redhat.osas.alcyone.client;

import com.redhat.osas.alcyone.AlcyoneVector;

/**
 * User: jottinge
 * Date: 4/5/13
 * Time: 2:01 PM
 */
public interface AlcyoneClient {
    void midiReset();

    void reset();

    void changeOctave(AlcyoneVector vector);

    void changeTransposition(AlcyoneVector vector);

    void changeChannel(AlcyoneVector vector);

    void updateStatus();
}
