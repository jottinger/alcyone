package com.redhat.osas.alcyone;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class AlcyoneConnection {
    int port;
    String host;
    Socket socket = null;
    InputStream inputStream = null;
    OutputStream outputStream = null;


    public AlcyoneConnection(String host, int port) {
        this.host = host;
        this.port = port;
    }

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

    public void changeOctave(AlcyoneVector vector) throws IOException {
        verifyConnection();
        write(buildMessage(AlcyoneMessage.MSG_MIDI_OCTAVE_CHANGE,
                vector));
    }

    private void write(final byte[] bytes) {
        ExecutorService service = Executors.newSingleThreadExecutor();
        service.submit(new Runnable() {

            @Override
            public void run() {
                try {
                    outputStream.write(bytes);
                } catch (IOException ignored) { // probably shouldn't be ignored, actually
                }
            }
        });
        service.shutdown();
    }

    public void changeTransposition(AlcyoneVector vector) throws IOException {
        verifyConnection();
        write(buildMessage(
                AlcyoneMessage.MSG_MIDI_TRANSPOSITION_CHANGE, vector));
    }

    public void changeChannel(AlcyoneVector vector) throws IOException {
        verifyConnection();
        write(buildMessage(AlcyoneMessage.MSG_MIDI_CHANNEL_CHANGE,
                vector));
    }

    public void midiReset() throws IOException {
        verifyConnection();
        write(buildMessage(AlcyoneMessage.MSG_MIDI_RESET));
    }

    public void reset() throws IOException {
        verifyConnection();
        write(buildMessage(AlcyoneMessage.MSG_RESET));
    }

    public AlcyoneStatus getStatus() throws IOException {
        // since this is an exchange, we need to manage the thread differently\
        final byte[] buffer = new byte[3];
        ExecutorService service = Executors.newSingleThreadExecutor();
        service.submit(new Runnable() {
            @Override
            public void run() {
                try {
                    verifyConnection();
                    byte msg[] = new byte[]{(byte)AlcyoneMessage.MSG_REQUEST_STATUS.getMask()};
                    outputStream.write(msg);
                    if (inputStream.read(buffer, 0, 3) != 3) {
                        System.out.println("Couldn't read three characters back.");
                    }
                } catch (IOException ioe) {
                    ioe.printStackTrace();
                }
            }
        });
        try {
            service.awaitTermination(500, TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        service.shutdown();
        return new AlcyoneStatus(buffer[0], buffer[1], buffer[2]);
    }

    private byte[] buildMessage(AlcyoneMessage msg) {
        return new byte[]{(byte) (msg.getMask() & 0xf0)};
    }

    private byte[] buildMessage(AlcyoneMessage msg, AlcyoneVector vector) {
        return new byte[]{(byte) (msg.getMask() | vector.getMask())};
    }
}
