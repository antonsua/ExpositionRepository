package es.ucm.moviles.enginepc;

import java.util.HashMap;
import java.util.Map;

import es.ucm.moviles.engineinterface.FontInterface;
import es.ucm.moviles.engineinterface.ResourceManagerInterface;
public class FontManagerPC implements ResourceManagerInterface<FontInterface> {

    private Map<String, FontInterface> _fontMap;
    private String _fontsPath;

    public void Init(){
        _fontMap = new HashMap<String, FontInterface>();
        _fontsPath = "recursos/fonts/";
    }

    @Override
    public FontInterface getResource(String name, int size, int style) {
        // Comprobamos si existe la fuente solicitada
        if (_fontMap.containsKey(name))
        {
            // Devolvemos el objeto fuente
            return _fontMap.get(name);
        }
        else {
            if(load(name, size, style)){
                return _fontMap.get(name);
            }
            else
                return  null;
        }
    }

    @Override
    public FontInterface getResource(String name) {
        return null;
    }

    @Override
    public void removeResource(String name) {
        if(_fontMap.containsKey((name))){
            _fontMap.remove(_fontMap.get(name));
        }
    }

    @Override
    public void addResource(FontInterface res, String identifier) {
       _fontMap.put(identifier,res);
    }

    protected boolean load(String name,  int size, int style){

        String[] cutText = name.split("\\.");

        FontPC _f = new FontPC();

        // Añadimos el nombre de la fuente al path
        String filePath = _fontsPath + name;
        _f.loadFont(filePath,size,style);

        if(_f != null){
            addResource(_f, name);
            return true;
        }
        else
            return false;

    }
}
