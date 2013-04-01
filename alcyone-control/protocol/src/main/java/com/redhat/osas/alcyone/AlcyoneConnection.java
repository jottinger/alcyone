package com.redhat.osas.alcyone;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

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
		System.out.println("Message: "
				+ Integer.toBinaryString(buildMessage(AlcyoneMessage.MSG_MIDI_CHANNEL_CHANGE, vector)[0]));
		outputStream.write(buildMessage(AlcyoneMessage.MSG_MIDI_OCTAVE_CHANGE,
				vector));
	}

	public void changeTransposition(AlcyoneVector vector) throws IOException {
		verifyConnection();
		outputStream.write(buildMessage(
				AlcyoneMessage.MSG_MIDI_TRANSPOSITION_CHANGE, vector));
	}

	public void changeChannel(AlcyoneVector vector) throws IOException {
		verifyConnection();
		outputStream.write(buildMessage(AlcyoneMessage.MSG_MIDI_CHANNEL_CHANGE,
				vector));
	}

	public void midiReset() throws IOException {
		verifyConnection();
		outputStream.write(buildMessage(AlcyoneMessage.MSG_MIDI_RESET));
	}

	public void reset() throws IOException {
		verifyConnection();
		outputStream.write(buildMessage(AlcyoneMessage.MSG_RESET));
	}

	public AlcyoneStatus getStatus() throws IOException {
		verifyConnection();
		outputStream.write(buildMessage(AlcyoneMessage.MSG_REQUEST_STATUS));
		byte[] buffer = new byte[3];
		if (inputStream.read(buffer, 0, 3) != 3) {
			// what happened to our input?
		}
		return new AlcyoneStatus(buffer[0], buffer[1], buffer[2]);
	}

	private byte[] buildMessage(AlcyoneMessage msg) {
		return new byte[] { (byte) (msg.getMask() & 0xf0) };
	}

	private byte[] buildMessage(AlcyoneMessage msg, AlcyoneVector vector) {
		return new byte[] { (byte) (msg.getMask() | vector.getMask()) };
	}
}
