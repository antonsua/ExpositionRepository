package es.ucm.moviles.androidEngine;

import android.content.Context;

import java.util.HashMap;
import java.util.Map;

import es.ucm.moviles.engineinterface.AudioInterface;
import es.ucm.moviles.engineinterface.ResourceManagerInterface;

public class AudioManagerAnd implements ResourceManagerInterface<AudioInterface> {
    private Context _context;
    private Map<String, AudioInterface> _audioMap;
    private String _audioPath;

    public void Init(Context c){
        _audioMap = new HashMap<String, AudioInterface>();
        _audioPath = "recursos/audio/";

        _context = c;
    }
    @Override
    public AudioInterface getResource(String name, int size, int style) {
        if(_audioMap.containsKey(name)){
            return _audioMap.get(name);
        }
        else {
            if(load(name)){
                return _audioMap.get(name);
            }
            else
                return null;
        }
    }

    @Override
    public AudioInterface getResource(String name) {
        return getResource(name,0,0);
    }

    @Override
    public void removeResource(String name) {
        if(_audioMap.containsKey(name))
            _audioMap.remove(_audioMap.get(name));
    }

    @Override
    public void addResource(AudioInterface res, String identifier) {
        _audioMap.put(identifier,res);
    }

    private boolean load(String name){
        String[] cutText = name.split("\\.");
        AudioAndroid audio =new AudioAndroid();
        audio.Init(_context);

        String filePath = _audioPath+name;
        boolean result = audio.loadSource(name);
        if(audio.getMP() != null){
            //Cargar en mapa
            addResource(audio,name);
        }
        return result;
    }
}
