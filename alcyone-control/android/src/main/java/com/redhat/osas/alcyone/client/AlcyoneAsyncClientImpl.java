package com.redhat.osas.alcyone.client;

import android.os.AsyncTask;
import android.util.Log;
import com.redhat.osas.alcyone.AlcyoneActivity;
import com.redhat.osas.alcyone.AlcyoneMessage;
import com.redhat.osas.alcyone.AlcyoneStatus;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import java.io.IOException;
import java.net.MalformedURLException;
import java.util.Scanner;

/**
 * User: jottinge
 * Date: 4/4/13
 * Time: 1:07 PM
 */
class AlcyoneAsyncClientImpl extends AlcyoneClientBase implements AlcyoneClient {
    private static final HttpClient httpClient = new DefaultHttpClient();

    public AlcyoneAsyncClientImpl(AlcyoneActivity activity, String host, int port) {
        super(activity, host, port);
    }

    void execute(AlcyoneMessage msg, int... values) {
        int value = msg.getMask();
        if (values.length > 0) {
            value += values[0];
        }
        String urlString = "http://" + host + ":" + port + "/?message=" + value;
        new AsyncTask<String, Integer, AlcyoneStatus>() {
            @Override
            protected void onPostExecute(AlcyoneStatus alcyoneStatus) {
                Log.d("alcyoneRequest", "onPostExecute " + alcyoneStatus);
                if (alcyoneStatus != null) {
                    activity.updateStatus(alcyoneStatus);
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
                    Log.d("alcyoneRequest", "looking for url: " + urls[0]);

                    HttpGet get = new HttpGet(urls[0]);
                    HttpResponse response = httpClient.execute(get);
                    if (response.getStatusLine().getStatusCode() == 200) {
                        HttpEntity entity = response.getEntity();
                        Scanner scanner = new Scanner(entity.getContent());
                        status = new AlcyoneStatus(scanner.nextInt(),
                                scanner.nextInt(),
                                scanner.nextInt());
                        scanner.close();
                        entity.consumeContent();
                    }

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

}
