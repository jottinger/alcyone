package com.redhat.osas.alcyone;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;

/**
 * User: jottinge
 * Date: 4/2/13
 * Time: 8:24 AM
 */
public class AlcyoneActivity extends Activity {
    String host = "192.168.1.108";
    int port = 8090;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
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
                return false;
            case R.id.mnuAlcyoneReset:
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
    }

    public void octaveDown(View view) {
    }

    public void transpositionUp(View view) {
    }

    public void transpositionDown(View view) {
    }

    public void channelUp(View view) {
    }

    public void channelDown(View view) {
    }
}