package com.redhat.osas.alcyone;

import java.io.IOException;

/**
 * User: jottinge
 * Date: 4/3/13
 * Time: 10:00 AM
 */
public interface AlcyoneConnection {
    void connect() throws IOException;

    void changeOctave(AlcyoneVector vector) throws IOException;

    void changeTransposition(AlcyoneVector vector) throws IOException;

    void changeChannel(AlcyoneVector vector) throws IOException;

    void midiReset() throws IOException;

    void reset() throws IOException;

    AlcyoneStatus getStatus() throws IOException;
}
