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

package com.redhat.osas.alcyone.impl;

import com.redhat.osas.alcyone.AlcyoneConnection;
import com.redhat.osas.alcyone.AlcyoneMessage;
import com.redhat.osas.alcyone.AlcyoneStatus;
import com.redhat.osas.alcyone.AlcyoneVector;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class AlcyoneConnectionImpl implements AlcyoneConnection {
    int port;
    String host;
    Socket socket = null;
    InputStream inputStream = null;
    OutputStream outputStream = null;


    public AlcyoneConnectionImpl(String host, int port) {
        this.host = host;
        this.port = port;
    }

    @Override
    public void connect() throws IOException {
        safeClose(outputStream);
        safeClose(inputStream);
        safeClose(socket);
        socket = new Socket(this.host, this.port);
        inputStream = socket.getInputStream();
        outputStream = socket.getOutputStream();
    }

    private void safeClose(AutoCloseable closeable) {
        try {
            if (closeable != null) {
                closeable.close();
            }
        } catch (Exception ignored) {
        }
    }

    private void verifyConnection() throws IOException {
        if (socket == null || socket.isClosed() || !socket.isConnected()
                || socket.isInputShutdown() || socket.isOutputShutdown()) {
            connect();
        }
    }

    @Override
    public void changeOctave(AlcyoneVector vector) throws IOException {
        verifyConnection();
        write(buildMessage(AlcyoneMessage.MSG_MIDI_OCTAVE_CHANGE,
                vector));
    }

    private void write(final byte[] bytes) throws IOException {
        outputStream.write(bytes);
    }

    @Override
    public void changeTransposition(AlcyoneVector vector) throws IOException {
        verifyConnection();
        write(buildMessage(
                AlcyoneMessage.MSG_MIDI_TRANSPOSITION_CHANGE, vector));
    }

    @Override
    public void changeChannel(AlcyoneVector vector) throws IOException {
        verifyConnection();
        write(buildMessage(AlcyoneMessage.MSG_MIDI_CHANNEL_CHANGE,
                vector));
    }

    @Override
    public void midiReset() throws IOException {
        verifyConnection();
        write(buildMessage(AlcyoneMessage.MSG_MIDI_RESET));
    }

    @Override
    public void reset() throws IOException {
        verifyConnection();
        write(buildMessage(AlcyoneMessage.MSG_RESET));
    }

    @Override
    public AlcyoneStatus getStatus() throws IOException {
        // since this is an exchange, we need to manage the thread differently\
        final byte[] buffer = new byte[3];
        try {
            verifyConnection();
            byte msg[] = new byte[]{(byte) AlcyoneMessage.MSG_REQUEST_STATUS.getMask()};
            outputStream.write(msg);
            if (inputStream.read(buffer, 0, 3) != 3) {
                System.out.println("Couldn't read three characters back.");
            }
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
        return new AlcyoneStatus(buffer[0], buffer[1], buffer[2]);
    }

    private byte[] buildMessage(AlcyoneMessage msg) {
        return new byte[]{(byte) (msg.getMask() & 0xf0)};
    }

    private byte[] buildMessage(AlcyoneMessage msg, AlcyoneVector vector) {
        return new byte[]{(byte) (msg.getMask() | vector.getMask())};
    }
}
