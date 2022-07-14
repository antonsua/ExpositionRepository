package es.ucm.moviles.androidEngine;

import android.content.Context;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.widget.TextView;

import es.ucm.moviles.engineinterface.FontInterface;

/**
 * Clase que implementa la interfaz de Fuente para el motor Android.
 */
public class FontAndroid implements FontInterface {
    // Variable de Fuente especifica de Android
    String _fontName;
    Typeface _typeface;
    Context _context; // Usado para cargar la fuente
    Paint _paint;    // Usado cuando se pide el tamaño. No deberia hacerse desde aqui, esta comentado.
    int _style; // Tipo de fuente.

    /* ----------------------
     * Metodos de la interfaz
     * ---------------------
     */
    /**
     * Carga en la instancia actual una fuente desde un archivo
     * @param filename : Nombre del archivo de la fuente
     * @param size : tamaño al cargarlo
     * @param style : Estilo de carga 0: plain, 1: negrita, 2: cursiva
     */
    public boolean loadFont(String filename, int size, int style)
    {
        // API minima 26
        //Typeface.Builder builder = new Typeface.Builder(_context.getAssets(), filename);
        _fontName = filename;
        try {
            _typeface = Typeface.createFromAsset(_context.getAssets(), filename);
            _style = _typeface.getStyle();
            return true;
        }
        catch (Exception e){
            System.err.println(e.getMessage());
            return false;
        }
    }

    /* ---------------------------------------
     * GETTERS
     * ---------------------------------------
     */

    /**
     * Devuelve el objeto fuente del tipo especifico del motor
     * @return Font (awt.Font)
     */
    public Typeface getFont(){ return _typeface; }

    /**
     * Indica si la fuente esta configurada en negrita.
     * @return boolean true si es negrita, false en caso contrario.
     */
    @Override
    public boolean isBold()
    {
        return _typeface.isBold();
    }

    /**
     * Devuelve si la fuente esta en modo cursiva.
     * @return boolean: true si lo esta, false en caso contrario.
     */
    @Override
    public boolean isItalic()
    {
        return _typeface.isItalic();
    }

    /**
     * ATENCION: Este metodo hace referencia al tamaño establecido para TODAS las fuentes.
     * NO UTILIZAR getSize desde la fuente, llamar al _paint.getTextSize() desde el propio
     * GraphicsAndroid.
     * En Android la gestion del tamaño de la fuente no lo lleva cada fuente
     * sino el propio PAINT de Android, por lo tanto aquí devolvemos lo que tenga
     * establecido el paint.
     * Devuelve el tamaño configurado de la fuente en puntos.
     * @return int tamaño actual de la fuente.
     */
    @Override
    public int getSize()
    {
        return (int)_paint.getTextSize();
    }

    /**
     * Devuelve un Int que representa el estilo de la fuente (Plain, Bold, Italyc)
     * @return int: Estilo de TypeFace (No confundir con Style de Paint).
     */
    @Override
    public int getStyle()
    {
        return _typeface.getStyle();
    }

    /**
     * Devuelve el identificador de la fuente.
     * @return string: nombre de la fuente.
     */
    @Override
    public String getFontName()
    {
        return _fontName;
    }

    /* ------------------
     * SETTERS
     * ------------------
     */

    /**
     * Establece el context necesario para cargar las fuentes.
     * @param c
     */
    public void setContext(Context c)
    {
        _context = c;
    }

    /**
     * Al crear una fuente hay que darle el paint para que algunos de sus metodos
     * tengan sentido. Sin embargo es importante recordar que lo que los metodos
     * que utilicen el _paint afectan a toda fuente, pues modifican el _paint y no
     * una fuente en concreto.
     * @param p PAINT.
     */
    public void setPaint(Paint p) { _paint = p; }

    /**
     * Método que almacena el nombre de la fuente. Debe usarse al cargar la fuente,
     * dandole el nombre del archivo (sin extensión). Así el identificador dentro
     * del diccionario del gestor de recursos coincidira con el nombre de la fuente.
     * @param s
     */
    public void setName(String s) { _fontName = s;}

    /**
     * Funcion para configurar la fuente para que escriba en su formato negrita.
     * @param b : boolean true para activar negrita, false para volver a formato plano.
     */
    @Override
    public void setBold(boolean b)
    {
        //TODO
    }

    /**
     * Cambia el estilo cursiva de la fuente.
     * @param b si activar (true) o desactivar (false) el modo cursiva.
     */
    @Override
    public void setItalic(boolean b)
    {
        //TODO
    }

    /**
     * ATENCION: Este metodo altera TODAS las fuentes a partir del punto que es llamado.
     * NO UTILIZAR setSize desde la fuente, llamar al _paint.setTextSize() desde el propio
     * GraphicsAndroid.
     * Establece el tamaño de la fuente en puntos.
     * @param s : float para establecer el tamaño en puntos de la fuente.
     */
    @Override
    public void setSize(float s) {
        _paint.setTextSize(s);
    }

}
