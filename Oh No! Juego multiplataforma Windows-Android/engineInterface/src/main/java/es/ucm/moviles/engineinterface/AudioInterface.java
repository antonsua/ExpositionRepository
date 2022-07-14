package es.ucm.moviles.engineinterface;

public interface AudioInterface {
    void playAudio();  //Comienza a reproducir el audio
    boolean isPlaying(); //Devuelve si hay una pista de audio sonando
    void pauseAudio(); //Pausa el audio
    void stopPause(); //Termina la cancion
    void setLooping(boolean looping, int id);  // Setea si el audio  de la pista 'id' se reproduce en loop o no
    void setVolume(float leftVolume, float rightVolume);  //Setea el volumen
    void closeAudio(); //Libera el recurso de cada plataforma. ESTO SOLO SE DEBE LLAMAR CUANDO NO SE VAYA USAR MAS AUDIO
}
