package es.ucm.moviles.androidEngine;

import android.content.Context;
import android.graphics.Paint;

import java.util.Dictionary;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;

import es.ucm.moviles.engineinterface.AudioInterface;
import es.ucm.moviles.engineinterface.FontInterface;
import es.ucm.moviles.engineinterface.ImageInterface;
import es.ucm.moviles.engineinterface.ResourcesInterface;

public class ResourcesAndroid implements ResourcesInterface
{
    private Context _context;
    private Paint _paint; //usado para darselo a la fuente, lo usara en ciertos metodos.

    Map<String, FontInterface> _fontMap;
    Map<String, ImageInterface> _imageMap;
    Map<String, AudioInterface> _audioMap;
    //Dictionary<String, FontInterface> soundMap;

    // Directorios de carga de recursos.
    private String _fontsPath;
    private String _imagesPath;
    //private String soundsPath;

    /**
     * Constructora vacia
     */
    ResourcesAndroid(Context c, Paint p)
    {
        _context = c;
        _paint = p;
    }

    /**
     * Metodo que inicializa las variables internas del gestor de recursos
     */
    public void init()
    {
        //System.out.println("ResourcesPC::Init()");

        // Inicializamos los diccionarios
        _fontMap = new HashMap<String, FontInterface>();
        _imageMap = new HashMap<String, ImageInterface>();
        _audioMap = new HashMap<String, AudioInterface>();
        //soundMap = new HashMap<String, SoundInterface>();

        // Establecemos la ruta de carga de los recursos.
        _fontsPath = "recursos/fonts/";
        _imagesPath = "recursos/sprites/";
    }

    /* ------------------------
     * Gestion de Diccionarios
     * ------------------------
     */
    /**
     * Metodo interno para añadir una fuente al su mapa
     * Como Key usaremos el string devuelto por la propia fuente al consultar su nombre.
     * @param f
     */
    private void addFont(String fontName, FontAndroid f)
    {
        _fontMap.put(fontName, f);
    }

    /**
     * Metodo interno para añadir una imagen a su mapa
     * @param imageName : nombre que usaremos como Key del map e identificador de la imagen.
     * @param i : instancia de ImagePC de la imagen.
     */
    private void addImage(String imageName, ImageAndroid i)
    {
        _imageMap.put(imageName, i);
    }

    /**
     * Metodo interno para añadir una pista de audio a su mapa
     * @param audioName : nombre que usaremos como Key del map e identificador de la pista de audio.
     * @param audio : instancia de AudioAndroid de la pista.
     */
    private void addAudio(String audioName, AudioAndroid audio){_audioMap.put(audioName,audio);}
    /* -----------------------------
     * FUENTES
     * -----------------------------
     */
    /**
     * Metodo que genera una nueva fuente y la añade al diccionario interno de fuentes.
     * @param filename : string, Nombre del archivo, usado como identificador.
     * @param size : int, tamaño de la fuente en puntos.
     * @param style : int, Formato de la fuente (0=plain, 1=negrita, 2=cursiva).
     */

    @Override
    public boolean loadFont(String filename, int size, int style)
    {
        //System.out.println("ResourcesAndroid::loadFont()");

        // Nos quedamos con el nombre del archivo sin la extension como identificador
        // Podría hacerse con el Font.getName() pero no tenemos un metodo similar en android
        // Y ambos deben poder identificarse igual a traves de la logica, por lo tanto
        // Cogeremos el nombre del archivo como referencia y no su nombre en metadatos de PC.
        // Cortamos la extension del nombre de la imagen
        String[] cutText = filename.split("\\.");

        if(!_fontMap.containsKey(cutText[0]))
        {
            // Generamos instancia de fuente especifica para PC
            FontAndroid _f = new FontAndroid();

            // Pasarle el context
            _f.setContext(_context);

            // Añadimos el nombre de la fuente al path
            String filePath = filename;

            // Cargamos la imagen del archivo en la instancia
            boolean result = _f.loadFont(filePath,size,style);
            _f.setName(cutText[0]);
            _f.setPaint(_paint);

            if (result)
            {
                // Si ha ido bien, metemos la instancia en el diccionario si no existe una con el mismo nombre.
                if (_f != null)
                {
                    addFont(cutText[0], _f);
                    return true;
                }
                else {
                    return false;
                }
            }
            else
            {
                System.err.println("No se ha cargado la imagen " + filename);
                return false;
            }
        }
        // Si la fuente solicitada ya esta en la lista de recursos, devolvemos true
        else
            return true;
    }

    /**
     * Devuelve una instancia de fuente con el nombre solicitado
     * @return FontInterface o null si no es encontrada.
     */
    @Override
    public FontInterface getFont(String fontName)
    {
        // Comprobamos si existe la fuente solicitada
        if (_fontMap.containsKey(fontName))
        {
            // Devolvemos el objeto fuente
            return _fontMap.get(fontName);
        }
        else
            return null;
    }

    /* -----------------------------
     * IMAGENES
     * -----------------------------
     */
    /**
     * Metodo que genera una nueva fuente y la añade al diccionario interno de fuentes.
     * @param filename : string, Nombre del archivo, usado como identificador.
     */
    @Override
    public boolean loadImage(String filename)
    {
        // Cortamos la extension del nombre de la imagen
        String[] cutText = filename.split("\\.");

        if (!_imageMap.containsKey(cutText[0]))
        {
            // Generamos una instancia de la imagen especifica de pc
            ImageAndroid i = new ImageAndroid();

            // Añadimos el nombre de la fuente al path
            String filePath = /*_imagesPath + */filename;

            // Intentamos cargar la imagen
            i.loadAndroidImage(filePath, _context);

            // Si ha ido bien, la añadimos al diccionario si no existe una con el mismo nombre.
            if (i != null)
            {
                // Usamos el nombre de la imagen como key.
                addImage(cutText[0], i);
                return true;
            }
            else
                return false;
        }
        else
            return true;
    }

    /**
     * Metodo para obtener una imagen en concreto con el nombre solicitado
     * @param imageName String con el identificador de la imagen
     * @return ImageInterface de la imagen solicitada o null si no es encontrada.
     */
    @Override
    public ImageInterface getImage(String imageName)
    {
        // Comprobamos si existe la fuente solicitada
        if (_imageMap.containsKey(imageName))
        {
            // Devolvemos el objeto fuente
            return _imageMap.get(imageName);
        }
        else
            return null;
    }

    @Override
    public boolean loadSourceAudio(String filename) {
        String[] cutText = filename.split("\\.");
        AudioAndroid _audioAnd = new AudioAndroid();
        _audioAnd.Init(_context);
        boolean result = _audioAnd.loadSource(filename);
        _audioAnd.setLooping(false,0);
        _audioAnd.setVolume(50,50);
        if(filename != null && !_audioMap.containsKey(filename)) {
            addAudio(cutText[0], _audioAnd);
            return true;
        }
        else
            return false;
    }

    @Override
    public AudioInterface getAudio(String name) {
        if(_audioMap.containsKey(name)){
            return _audioMap.get(name);
        }
        else return null;
    }
}
