package com.redhat.osas.alcyone.client;

import com.redhat.osas.alcyone.AlcyoneActivity;

/**
 * User: jottinge
 * Date: 4/5/13
 * Time: 1:59 PM
 */
public class AlcyoneClientFactory {
    public static AlcyoneClient build(AlcyoneActivity activity, String host, int port) {
        return new AlcyoneAsyncClientImpl(activity, host, port);
    }
}
