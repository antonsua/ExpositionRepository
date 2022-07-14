package es.ucm.moviles.androidEngine;

import android.app.Application;
import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.media.MediaPlayer;
import android.os.Environment;

import es.ucm.moviles.engineinterface.AudioInterface;

public class AudioAndroid implements AudioInterface {
    private MediaPlayer _mp; //Entidad que gestiona el audio en Android
    private Context _context;

    AudioAndroid(){

    }

    public void Init(Context c) {
        _mp =new MediaPlayer();
        _context =c;
    }

    public boolean loadSource(String filename) {
        AssetFileDescriptor afd;
        try{
            afd = _context.getAssets().openFd(filename);
            _mp.setDataSource(afd.getFileDescriptor());
            _mp.prepare();
            return true;
        }
        catch (Exception e){
            System.err.println(e.getMessage());
        }
        return false;
    }

    @Override
    public void playAudio() {
        _mp.start();
    }

    @Override
    public boolean isPlaying() {
        return _mp.isPlaying();
    }

    @Override
    public void pauseAudio() {
        _mp.pause();
    }

    @Override
    public void stopPause() {
        _mp.stop();
    }

    @Override
    public void setLooping(boolean looping, int id) {
        _mp.setLooping(looping);
    }

    @Override
    public void setVolume(float leftVolume, float rightVolume) {
        _mp.setVolume(leftVolume,rightVolume);
    }

    @Override
    public void closeAudio() {
        _mp.release();
    }
    public MediaPlayer getMP(){return _mp;}
}
