package es.ucm.moviles.enginepc;

import java.io.File;
import java.net.URL;

import es.ucm.moviles.engineinterface.AudioInterface;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;

public class AudioPC implements AudioInterface {
    Clip audio;

    public boolean loadSource(String filename) {
        audio = null;
        try{

            AudioInputStream audioIn = AudioSystem.getAudioInputStream(new File(filename));
            audio = AudioSystem.getClip();
            audio.open(audioIn);
            return true;
        }
        catch (Exception e){
            System.err.println(e.getMessage());
        }
        return false;
    }

    @Override
    public void playAudio() {
        audio.start();
    }

    @Override
    public boolean isPlaying() {
        return audio.isActive();
    }

    @Override
    public void pauseAudio() {
        audio.stop();
    }

    @Override
    public void stopPause() {
        audio.stop();
        audio.setFramePosition(0);
    }

    @Override
    public void setLooping(boolean looping, int id) {
        audio.loop(5); //Se supone que se repite i veces con esto. 5 de momento
    }

    @Override
    public void setVolume(float leftVolume, float rightVolume) {

    }

    @Override
    public void closeAudio() {
        audio.close();
    }
}
