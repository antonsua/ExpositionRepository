package es.ucm.moviles.enginepc;

import java.util.HashMap;
import java.util.Map;

import es.ucm.moviles.engineinterface.ImageInterface;
import es.ucm.moviles.engineinterface.ResourceManagerInterface;
public class ImageManagerPC implements ResourceManagerInterface<ImageInterface> {

    private Map<String, ImageInterface> _imageMap;
    private String _imagesPath;

    public void Init(){
        _imageMap = new HashMap<String, ImageInterface>();
        _imagesPath = "recursos/sprites/";
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
    protected boolean load(String name,  int size, int style){

        String[] cutText = name.split("\\.");

        ImagePC _i = new ImagePC();

        // Añadimos el nombre de la fuente al path
        String filePath = _imagesPath + name;
        _i.loadImageFile(filePath);

        if(_i != null){
            addResource(_i, name);
            return true;
        }
        else
            return false;

    }
}
