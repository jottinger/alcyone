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
package com.redhat.osas.alcyone;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

import java.io.IOException;

/**
 * User: jottinge
 * Date: 4/2/13
 * Time: 8:24 AM
 */
public class AlcyoneActivity extends Activity {
    AsyncAlcyoneConnection connection;
    String host = "192.168.1.108";
    int port = 8090;
    TextView txtOctave;
    TextView txtTransposition;
    TextView txtChannel;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        txtOctave = (TextView) findViewById(R.id.txtOctave);
        txtTransposition = (TextView) findViewById(R.id.txtTransposition);
        txtChannel = (TextView) findViewById(R.id.txtChannel);

        Log.d("alcyone", "We have initialized");
        connection = new AsyncAlcyoneConnection(host, port);
        updateStatus();
    }

    private void updateStatus() {
        AlcyoneStatus status = null;
        try {
            status = connection.getStatus();
        } catch (IOException e) {
            Log.e("alcyone", e.getMessage(), e);
        }
        txtOctave.setText(Integer.toString(status.getOctave()));
        txtTransposition.setText(Integer.toString(status.getTransposition()));
        txtChannel.setText(Integer.toString(status.getChannel()));
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.alcyone_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.mnuMIDIReset:
                try {
                    connection.midiReset();
                    updateStatus();
                } catch (IOException e) {
                    Log.e("alcyone", e.getMessage(), e);
                }
                return true;
            case R.id.mnuAlcyoneReset:
                try {
                    connection.reset();
                    updateStatus();
                } catch (IOException e) {
                    Log.e("alcyone", e.getMessage(), e);
                }
                return false;
            case R.id.mnuConfigure:
                /*
                   Note lack of preferences support here, thanks for 'splainin' so well, Android
                 */
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    public void octaveUp(View view) {
        try {
            connection.changeOctave(AlcyoneVector.UP);
            updateStatus();
        } catch (IOException e) {
            Log.e("alcyone", e.getMessage(), e);
        }
    }

    public void octaveDown(View view) {
        try {
            connection.changeOctave(AlcyoneVector.DOWN);
            updateStatus();
        } catch (IOException e) {
            Log.e("alcyone", e.getMessage(), e);
        }
    }

    public void transpositionUp(View view) {
        try {
            connection.changeTransposition(AlcyoneVector.UP);
            updateStatus();
        } catch (IOException e) {
            Log.e("alcyone", e.getMessage(), e);
        }
    }

    public void transpositionDown(View view) {
        try {
            connection.changeTransposition(AlcyoneVector.DOWN);
            updateStatus();
        } catch (IOException e) {
            Log.e("alcyone", e.getMessage(), e);
        }
    }

    public void channelUp(View view) {
        try {
            connection.changeChannel(AlcyoneVector.UP);
            updateStatus();
        } catch (IOException e) {
            Log.e("alcyone", e.getMessage(), e);
        }
    }

    public void channelDown(View view) {
        try {
            connection.changeChannel(AlcyoneVector.DOWN);
            updateStatus();
        } catch (IOException e) {
            Log.e("alcyone", e.getMessage(), e);
        }
    }
}