package com.redhat.osas.alcyone;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class EditPreferencesActivity extends Activity {
    String host;
    int port;
    TextView txtPrefHost;
    TextView txtPrefPort;
    Button reset;
    Button resetToDefault;
    Button submit;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        setContentView(R.layout.preferences);
        txtPrefHost = (TextView) findViewById(R.id.txtPrefHost);
        txtPrefPort = (TextView) findViewById(R.id.txtPrefPort);
        reset = (Button) findViewById(R.id.btnPrefReset);
        resetToDefault = (Button) findViewById(R.id.btnPrefResetToDefault);
        submit = (Button) findViewById(R.id.btnPrefSubmit);

        reset.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                setTextViews();
            }
        });

        resetToDefault.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                host = "piui";
                port = 8090;
                setTextViews();
            }
        });

        submit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                host = txtPrefHost.getText().toString();
                port = Integer.parseInt(txtPrefPort.getText().toString().trim());
                SharedPreferences preferences = getSharedPreferences("alcyone", 0);
                SharedPreferences.Editor editor = preferences.edit();
                editor.putString("host", host);
                editor.putInt("port", port);
                editor.commit();
                Log.i("alcyonePrefs", "writing preferences host=" + host + " port=" + port + " " + editor);
                startActivity(new Intent(EditPreferencesActivity.this, AlcyoneActivity.class));
            }
        });
    }

    private void setTextViews() {
        txtPrefHost.setText(host);
        txtPrefPort.setText(Integer.toString(port));
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d("alcyone", "onResume");
        SharedPreferences preferences = getSharedPreferences("alcyone", 0);
        host = preferences.getString("host", "piui");
        port = preferences.getInt("port", 8090);
        setTextViews();
        Log.d("alcyone", "Setting host to '" + host + "', port to " + port);
    }
}