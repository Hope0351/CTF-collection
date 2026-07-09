package com.pizza.integritycheckjava;

import android.content.Context;
import android.database.ContentObserver;
import android.media.AudioManager;
import android.os.Handler;
import android.util.Log;
import android.widget.Toast;
import android.widget.VideoView;

public class VolumeObserver extends ContentObserver {
    private final Context context;
    private final AudioManager audioManager;
    private final VideoView videoView;
    private final int minVolume;
    private final int maxVolume;
    public VolumeObserver(Context context, Handler handler, VideoView videoView, int minVolume, int maxVolume) {
        super(handler);
        this.context = context;
        this.audioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
        this.videoView = videoView;
        this.minVolume = minVolume;
        this.maxVolume = maxVolume;
    }

    @Override
    public void onChange(boolean selfChange) {
        super.onChange(selfChange);

        int currentVolume = audioManager.getStreamVolume(AudioManager.STREAM_MUSIC);

        int maximumVolume = audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);

        int volumePercent = (int) ((currentVolume / (float) maximumVolume) * 100);
//        Log.d("VolumeObserver", "Volume changed to: " + currentVolume);

        if (volumePercent >= minVolume && volumePercent <= maxVolume) {
            if (!videoView.isPlaying()) {
                videoView.resume();
//                Log.d("VolumeObserver", "Volume OK, starting video");
            }
        } else {
            if (videoView.isPlaying()) {
                Toast.makeText(context, "Incorrect Volume Level", Toast.LENGTH_SHORT).show();
                videoView.stopPlayback(); // or stopPlayback() if you want a hard stop
//                Log.d("VolumeObserver", "Volume out of range, stopping video");
            }
        }
    }
}
