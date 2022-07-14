package es.ucm.moviles.androidEngine;

import android.content.Context;
import android.graphics.Paint;

import java.util.HashMap;
import java.util.Map;

import es.ucm.moviles.engineinterface.FontInterface;
import es.ucm.moviles.engineinterface.ResourceManagerInterface;
public class FontManagerAndroid implements ResourceManagerInterface<FontInterface> {

    private Context _context;
    private Paint _paint;

    private Map<String, FontInterface> _fontMap;
    private String _fontsPath;

    public void Init(Context c, Paint p){
        _fontMap = new HashMap<String, FontInterface>();
        _fontsPath = "recursos/fonts/";

        _context = c; _paint = p;
    }

    @Override
    public FontInterface getResource(String name, int size, int style) {
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

    private boolean load(String name, int size, int style) {
        String[] cutText = name.split("\\.");

        FontAndroid _f = new FontAndroid();

        // Pasarle el context
        _f.setContext(_context);

        // Añadimos el nombre de la fuente al path
        String filePath = name;

        boolean result = _f.loadFont(filePath,size,style);
        _f.setName(cutText[0]);
        _f.setPaint(_paint);
        if (_f != null)
        {
            addResource(_f, name);
            return true;
        }
        else {
            return false;
        }

    }
}
