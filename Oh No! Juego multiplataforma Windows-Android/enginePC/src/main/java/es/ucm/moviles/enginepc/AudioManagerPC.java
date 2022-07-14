package es.ucm.moviles.enginepc;

import java.util.HashMap;
import java.util.Map;

import es.ucm.moviles.engineinterface.AudioInterface;
import es.ucm.moviles.engineinterface.ResourceManagerInterface;

public class AudioManagerPC implements ResourceManagerInterface<AudioInterface> {
    private Map<String, AudioInterface> _audioMap;
    private String _audioPath;

    public void Init(){
        _audioMap = new HashMap<String, AudioInterface>();
        _audioPath = "recursos/audio/";
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
        boolean result = false;
        String[] cutText = name.split("\\.");

        AudioPC audio = new AudioPC();
        String filePath = _audioPath + name;
        audio.loadSource(filePath);

        if(audio != null){
            addResource(audio, name);
            result = true;
        }


        return result;
    }
}
