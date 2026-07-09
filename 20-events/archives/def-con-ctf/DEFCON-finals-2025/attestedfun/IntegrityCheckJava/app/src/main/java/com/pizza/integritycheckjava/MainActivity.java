package com.pizza.integritycheckjava;

import android.content.Context;
import android.content.pm.ActivityInfo;
import android.graphics.Color;
import android.media.AudioManager;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkInfo;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.provider.Settings;
import android.util.Log;
import android.content.Intent;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.VideoView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.google.android.gms.tasks.Task;
import com.google.android.play.core.integrity.IntegrityManagerFactory;
import com.google.android.play.core.integrity.StandardIntegrityManager;

public class MainActivity extends AppCompatActivity {

    private StandardIntegrityManager.StandardIntegrityTokenProvider integrityTokenProvider;
    private String intentData;

    EditText challengeInput;
    TextView challengeDisplay;

    VolumeObserver volumeObserver;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
//        Intent intent = getIntent();
//        String data = intent.getStringExtra("extra_data");
//        if (data == null) {
//            data = "No data received";
//        }
//        Log.i("mobisys",data);
//        intentData = data;
        View mainLayout = findViewById(R.id.main);

        challengeInput = findViewById(R.id.challengeInput);
        challengeDisplay = findViewById(R.id.challengeDisplay);


        // Start the integrity token preparation process
        findViewById(R.id.myButton).setOnClickListener(v -> {

            if (!isNetworkAvailable()) {
                Toast.makeText(this, "No internet connection", Toast.LENGTH_SHORT).show();
            }
            else {
                    // Safe to perform online operations

    //            mainLayout.setBackgroundColor(Color.parseColor("#FFCDD2"));


                AudioManager audioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);


                int currentVolume = audioManager.getStreamVolume(AudioManager.STREAM_MUSIC);


                int maxVolume = audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);

                VideoView videoView = findViewById(R.id.videoView);


                int volumePercent = (int) ((currentVolume / (float) maxVolume) * 100);

                volumeObserver = new VolumeObserver(this, new Handler(), videoView, 90, 99);
                getContentResolver().registerContentObserver(Settings.System.CONTENT_URI, true, volumeObserver);


                if (volumePercent >= 90 && volumePercent <= 99) {

    //                Log.i("mobisys","Playing Video");
                    String input = challengeInput.getText().toString();
                    challengeInput.setVisibility(View.GONE);
                    intentData = input;

                    videoView.setVisibility(View.VISIBLE);
                    int result = (int) (Math.random() * 2);
                    Uri videoUri;
                    if (result == 1) {
                        videoUri = Uri.parse("android.resource://" + getPackageName() + "/" + R.raw.g1);

                    } else {
                        videoUri = Uri.parse("android.resource://" + getPackageName() + "/" + R.raw.m1_improved);
                    }

                    videoView.setVideoURI(videoUri);
                    videoView.setOnPreparedListener(mp -> {
                        //mp.setLooping(true); // Optional
                        videoView.start();
                    });

                    videoView.setOnCompletionListener(mp -> {
                        // This runs when the video finishes playing
    //                    Toast.makeText(this, "Video ended!", Toast.LENGTH_SHORT).show();

                        // Example: Hide the video view
                        videoView.setVisibility(View.GONE);

                        // You can also start another activity or show a dialog here
                    });

                    prepareIntegrityToken();
                }
                else{
                    Toast.makeText(this, "Incorrect Volume Level", Toast.LENGTH_SHORT).show();
                }

            }


        });
    }

    private void prepareIntegrityToken() {
        StandardIntegrityManager standardIntegrityManager =
                IntegrityManagerFactory.createStandard(getApplicationContext());

        long cloudProjectNumber = 848729417193L;

        standardIntegrityManager.prepareIntegrityToken(
                        StandardIntegrityManager.PrepareIntegrityTokenRequest.builder()
                                .setCloudProjectNumber(cloudProjectNumber)
                                .build())
                .addOnSuccessListener(tokenProvider -> {
                    integrityTokenProvider = tokenProvider;
//                    Log.i("mobisys", "Token provider ready.");
                    requestIntegrityToken(); // Now safe to call
                })
                .addOnFailureListener(this::handleError);
    }

    private void requestIntegrityToken() {
        if (integrityTokenProvider == null) {
            handleError(new IllegalStateException("Token provider is not initialized"));
            return;
        }
        String requestHash;

//        String requestHash = "test123test";
        try {
            byte[] pizzaSauce = hexStringToByteArray(intentData);
            byte[] key = new byte[]{(byte) 0x42, (byte) 0xCA, (byte) 0x7E, (byte) 0x13};
            byte[] pizzaCrust = xorWithRepeatingKey(pizzaSauce, key);
            requestHash = byteArrayToHexString(pizzaCrust);
        } catch (Exception e) {
            requestHash = "Invalid Hex String";
        }


//        Log.i("Request Hash: ",requestHash);

        Task<StandardIntegrityManager.StandardIntegrityToken> integrityTokenResponse =
                integrityTokenProvider.request(
                        StandardIntegrityManager.StandardIntegrityTokenRequest.builder()
                                .setRequestHash(requestHash)
                                .build());

        integrityTokenResponse
                .addOnSuccessListener(response -> sendToServer(response.token()))
                .addOnFailureListener(this::handleError);
    }

    private void sendToServer(String token) {

        challengeDisplay.setText(token);
        challengeDisplay.setTranslationY(1);
        challengeDisplay.setTextColor(Color.BLACK);
        challengeDisplay.setVisibility(View.VISIBLE);
        challengeDisplay.requestLayout();
//        Log.i("mobisys", "IntegrityTokenXLPizza: " + token);
//        Toast.makeText(this, "VERIFIED", Toast.LENGTH_LONG).show();

        // TODO: send token to your backend server
    }

    private void handleError(Exception exception) {
        Log.e("mobisys", "Error occurred", exception);
        // Optionally show a user-friendly message or retry
    }

    public static byte[] hexStringToByteArray(String hex) {
        int len = hex.length();
        byte[] data = new byte[len / 2];

        for (int i = 0; i < len; i += 2) {
            data[i / 2] = (byte) ((Character.digit(hex.charAt(i), 16) << 4)
                    + Character.digit(hex.charAt(i+1), 16));
        }

        return data;
    }

    public static byte[] xorWithRepeatingKey(byte[] data, byte[] key) {
        byte[] result = new byte[data.length];
        for (int i = 0; i < data.length; i++) {
            result[i] = (byte) (data[i] ^ key[i % key.length]);
        }
        return result;
    }

    public static String byteArrayToHexString(byte[] bytes) {
        StringBuilder hex = new StringBuilder();
        for (byte b : bytes) {
            hex.append(String.format("%02X", b)); // Uppercase hex
        }
        return hex.toString();
    }

    public boolean isNetworkAvailable() {
        ConnectivityManager cm = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);

        if (cm != null) {
            Network network = cm.getActiveNetwork();
            if (network == null) return false;

            NetworkCapabilities capabilities = cm.getNetworkCapabilities(network);
            return capabilities != null &&
                    capabilities.hasCapability(NetworkCapabilities.NET_CAPABILITY_INTERNET) &&
                    capabilities.hasCapability(NetworkCapabilities.NET_CAPABILITY_VALIDATED);
        }
        return false;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        getContentResolver().unregisterContentObserver(volumeObserver);
    }


}