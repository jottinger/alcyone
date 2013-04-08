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
    private final int port;
    private final String host;
    private Socket socket = null;
    private InputStream inputStream = null;
    private OutputStream outputStream = null;


    public AlcyoneConnectionImpl(String host, int port) {
        this.host = host;
        this.port = port;
    }

    @Override
    public void connect() throws IOException {
        disconnect();
        socket = new Socket(this.host, this.port);
        inputStream = socket.getInputStream();
        outputStream = socket.getOutputStream();
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
    public AlcyoneStatus getStatus() {
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

    @Override
    public void disconnect() {
        safeClose(outputStream);
        safeClose(inputStream);
        safeClose(socket);
        outputStream = null;
        inputStream = null;
        socket = null;
    }

    private void safeClose(OutputStream outputStream) {
        if (outputStream != null) {
            try {
                outputStream.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void safeClose(InputStream inputStream) {
        if (inputStream != null) {
            try {
                inputStream.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void safeClose(Socket socket) {
        if (socket != null) {
            try {
                socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private byte[] buildMessage(AlcyoneMessage msg) {
        return new byte[]{(byte) (msg.getMask() & 0xf0)};
    }

    private byte[] buildMessage(AlcyoneMessage msg, AlcyoneVector vector) {
        return new byte[]{(byte) (msg.getMask() | vector.getMask())};
    }
}
