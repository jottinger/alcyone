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

import android.os.AsyncTask;
import android.util.Log;
import android.util.Pair;
import com.redhat.osas.alcyone.impl.AlcyoneConnectionImpl;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutionException;

/**
 * User: jottinge
 * Date: 4/3/13
 * Time: 6:49 AM
 */
@SuppressWarnings("unchecked")
public class AsyncAlcyoneConnection implements AlcyoneConnection {
    AlcyoneConnection delegate;
    AlcyoneStatus lastStatus = null;

    public AlcyoneStatus getLastStatus() {
        return lastStatus;
    }

    public void setLastStatus(AlcyoneStatus lastStatus) {
        this.lastStatus = lastStatus;
    }

    AsyncAlcyoneConnection(String host, int port) {
        delegate = new AlcyoneConnectionImpl(host, port);
    }

    @Override
    public void connect() throws IOException {
        delegate.connect();
    }

    @Override
    public void changeOctave(AlcyoneVector vector) throws IOException {
        new AsyncChangeClass(delegate).execute(new Pair<String, AlcyoneVector>("octave", vector));
    }

    @Override
    public void changeTransposition(AlcyoneVector vector) throws IOException {
        new AsyncChangeClass(delegate).execute(new Pair<String, AlcyoneVector>("transposition", vector));
    }

    @Override
    public void changeChannel(AlcyoneVector vector) throws IOException {
        new AsyncChangeClass(delegate).execute(new Pair<String, AlcyoneVector>("channel", vector));
    }

    @Override
    public void midiReset() throws IOException {
        new AsyncChangeClass(delegate).execute(new Pair<String, AlcyoneVector>("midireset", null));
    }

    @Override
    public void reset() throws IOException {
        new AsyncChangeClass(delegate).execute(new Pair<String, AlcyoneVector>("reset", null));
    }

    @Override
    public AlcyoneStatus getStatus() throws IOException {
        AsyncChangeClass c = new AsyncChangeClass(delegate);
        try {
            return c.execute(new Pair<String, AlcyoneVector>("status", null)).get();
        } catch (InterruptedException e) {
            Log.e("alcyone", e.getMessage(), e);
        } catch (ExecutionException e) {
            Log.e("alcyone", e.getMessage(), e);
        }
        return new AlcyoneStatus(-1, -1, -1);
    }

    private class AsyncChangeClass extends AsyncTask<Pair<String, AlcyoneVector>, Integer, AlcyoneStatus> {
        AlcyoneConnection delegate;
        Map<String, Integer> commandMap = new HashMap<String, Integer>() {
            {
                put("octave", 1);
                put("transposition", 2);
                put("channel", 3);
                put("reset", 4);
                put("midireset", 5);
                put("status", 6);
            }
        };

        AsyncChangeClass(AlcyoneConnection delegate) {
            this.delegate = delegate;
        }

        @Override
        protected AlcyoneStatus doInBackground(Pair<String, AlcyoneVector>... pairs) {
            AlcyoneStatus status = null;
            if (commandMap.containsKey(pairs[0].first)) {
                try {
                    switch (commandMap.get(pairs[0].first)) {
                        case 1: // octave
                            delegate.changeOctave(pairs[0].second);
                            break;
                        case 2: // transposition
                            delegate.changeTransposition(pairs[0].second);
                            break;
                        case 3: // channel
                            delegate.changeChannel(pairs[0].second);
                            break;
                        case 4: // reset all
                            delegate.reset();
                            break;
                        case 5: // midi reset
                            delegate.midiReset();
                            break;
                        case 6: // status, happens normally anyway
                            status = lastStatus = delegate.getStatus();
                            break;
                        default:
                            Log.e("alcyone", "AlcyoneChangeClass command map failed to handle: " + pairs[0].first);
                            break;
                    }
                } catch (IOException e) {
                    Log.e("alcyone", e.getMessage(), e);
                }
            } else {
                Log.e("alcyone", "AlcyoneChangeClass invoked with invalid method: " + pairs[0].first);
            }

            return status;
        }
    }
}
