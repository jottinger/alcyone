package com.redhat.osas.alcyone;

import android.os.AsyncTask;
import android.util.Log;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Scanner;

/**
 * User: jottinge
 * Date: 4/4/13
 * Time: 1:07 PM
 */
public class AlcyoneClient {
    final String host;
    final int port;
    AlcyoneActivity activity;

    public AlcyoneClient(AlcyoneActivity activity, String host, int port) {
        this.activity = activity;
        this.host = host;
        this.port = port;
    }

    public void updateStatus() {
        execute(AlcyoneMessage.MSG_REQUEST_STATUS);
    }

    private void execute(AlcyoneMessage msg, int... values) {
        int value = msg.getMask();
        if (values.length > 0) {
            value += values[0];
        }
        String urlString = "http://" + host + ":" + port + "/?message=" + value;
        new AsyncTask<String, Integer, AlcyoneStatus>() {
            @Override
            protected void onPostExecute(AlcyoneStatus alcyoneStatus) {
                Log.d("alcyoneRequest", "onPostExecute "+alcyoneStatus);
                if (alcyoneStatus != null) {
                    activity.txtChannel.setText(Integer.toString(alcyoneStatus.getChannel()));
                    activity.txtOctave.setText(Integer.toString(alcyoneStatus.getOctave()));
                    activity.txtTransposition.setText(Integer.toString(alcyoneStatus.getTransposition()));
                }
                Log.d("alcyoneRequest", "onPostExecute() finished");
            }

            @Override
            protected AlcyoneStatus doInBackground(String... urls) {
                if (urls.length != 1) {
                    return null;
                }
                Log.d("alcyoneRequest", "Requesting url: " + urls[0]);
                AlcyoneStatus status = null;
                try {
                    URL url = new URL(urls[0]);
                    Log.d("alcyoneRequest", "looking for url: " + url.toString());

                    HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                    connection.setChunkedStreamingMode(128);
                    Log.d("alcyoneRequest", "connection built");
                    //Log.d("alcyoneRequest", "response code: "+connection.getResponseCode());
                    //if (connection.getResponseCode() == HttpURLConnection.HTTP_OK) {
                    InputStream inputStream = new BufferedInputStream(connection.getInputStream());
                    Log.d("alcyoneRequest", inputStream.toString());
                    Scanner scanner = new Scanner(inputStream);
                    status = new AlcyoneStatus(scanner.nextInt(),
                            scanner.nextInt(),
                            scanner.nextInt());
                    scanner.close();
                    inputStream.close();
                    //}
                    connection.disconnect();
                } catch (MalformedURLException e) {
                    Log.e("alcyoneRequest", e.getMessage(), e);
                } catch (IOException e) {
                    Log.e("alcyoneRequest", e.getMessage(), e);
                }
                Log.d("alcyoneRequest", "exiting doInBackground()");
                return status;
            }

        }.execute(urlString);
    }

    public void midiReset() {
        execute(AlcyoneMessage.MSG_MIDI_RESET);
    }

    public void reset() {
        execute(AlcyoneMessage.MSG_RESET);
    }

    public void changeOctave(AlcyoneVector vector) {
        execute(AlcyoneMessage.MSG_MIDI_OCTAVE_CHANGE, vector.getMask());
    }

    public void changeTransposition(AlcyoneVector vector) {
        execute(AlcyoneMessage.MSG_MIDI_TRANSPOSITION_CHANGE, vector.getMask());
    }

    public void changeChannel(AlcyoneVector vector) {
        execute(AlcyoneMessage.MSG_MIDI_CHANNEL_CHANGE, vector.getMask());
    }
}
