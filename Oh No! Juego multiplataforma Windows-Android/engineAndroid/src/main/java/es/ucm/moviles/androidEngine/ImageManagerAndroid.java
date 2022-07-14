package es.ucm.moviles.androidEngine;

import android.content.Context;

import java.util.HashMap;
import java.util.Map;

import es.ucm.moviles.engineinterface.ImageInterface;
import es.ucm.moviles.engineinterface.ResourceManagerInterface;

public class ImageManagerAndroid implements ResourceManagerInterface<ImageInterface> {

    private Context _context;

    private Map<String, ImageInterface> _imageMap;
    private String _imagesPath;

    public void Init(Context c){
        _imageMap = new HashMap<String, ImageInterface>();
        _imagesPath = "recursos/sprites/";
        _context = c;
    }

    @Override
    public ImageInterface getResource(String name, int size, int style) {
        if (_imageMap.containsKey(name))
        {
            // Devolvemos el objeto fuente
            return _imageMap.get(name);
        }
        else {
            if(load(name, size, style)){
                return _imageMap.get(name);
            }
            else
                return null;
        }
    }

    @Override
    public ImageInterface getResource(String name) {
        return getResource(name,0,0);
    }

    @Override
    public void removeResource(String name) {
        if(_imageMap.containsKey((name))){
            _imageMap.remove(_imageMap.get(name));
        }
    }

    @Override
    public void addResource(ImageInterface res, String identifier) {
        _imageMap.put(identifier,res);
    }

    private boolean load(String name, int size, int style){
        String[] cutText = name.split("\\.");

        ImageAndroid i = new ImageAndroid();

        // Añadimos el nombre de la fuente al path
        String filePath = /*_imagesPath + */name;

        // Intentamos cargar la imagen
        i.loadAndroidImage(filePath, _context);

        // Si ha ido bien, la añadimos al diccionario si no existe una con el mismo nombre.
        if (i != null)
        {
            // Usamos el nombre de la imagen como key.
            addResource(i, name);
            return true;
        }
        else
            return false;
    }
}
