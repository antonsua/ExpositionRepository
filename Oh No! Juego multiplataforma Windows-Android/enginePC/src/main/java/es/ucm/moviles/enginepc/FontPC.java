package es.ucm.moviles.enginepc;

import es.ucm.moviles.engineinterface.FontInterface;

import java.awt.Font;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.concurrent.ExecutionException;

public class FontPC implements FontInterface
{
    // Publico acceso a la fuente
    private Font _font;

    /**
     * Constructora, establece el path a las fuentes cuando esta se crea.
     */
    void FontPC() {}

    /**
     * crea una nueva fuente del tamaño especificado
     * a partir de un fichero .ttf.
     * Se indica si se desea o no fuente en negrita.
     * @param filePath
     * @param size
     * @param style
     * @return
     */
    public boolean loadFont(String filePath, int size, int style)
    {
        //System.out.println("FontPC::loadFont()");
        // Variable que devolvemos.
        _font = null;

        try {
            //System.out.println("FontPC::loadFont() Archivo de fuente a cargar: " + filePath);

            // Importamos la fuente del archivo
            // Metodo 1
            //File fontFile = new File(filePath);
            //_f = Font.createFont(Font.TRUETYPE_FONT, fontFile);
            // Metodo 2
            _font = Font.createFont(Font.TRUETYPE_FONT, new File(filePath));

            // Aplicamos los cambios a la fuente (tamaño y negrita)
            // Derive genera una nueva fuente, no hay setters como tal para cambiar una fuente.
            Font f2;
            f2 = _font.deriveFont(style, size);

            // Almacenamos la fuente modificada en la variable que devolveremos.
            _font = f2;
            return true;
        }
        catch (Exception e)
        {
            System.err.println("Error: " + e.toString());
            System.err.println("FontPC::newFont() No se encontró la fuente");
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
    public Font getFont()
    {
        return _font;
    }

    /**
     * Indica si la fuente esta configurada en negrita.
     * @return boolean true si es negrita, false en caso contrario.
     */
    @Override
    public boolean isBold()
    {
        return _font.isBold();
    }

    /**
     * Devuelve si la fuente esta en modo cursiva.
     * @return boolean: true si lo esta, false en caso contrario.
     */
    @Override
    public boolean isItalic()
    {
        return _font.isItalic();
    }

    /**
     * Devuelve el tamaño configurado de la fuente en puntos.
     * @return int tamaño actual de la fuente.
     */
    @Override
    public int getSize()
    {
        return _font.getSize();
    }

    /**
     * Devuelve el identificador de la fuente.
     * @return string: nombre de la fuente.
     */
    @Override
    public String getFontName() {
        if (_font != null) return _font.getFontName();
        else
            return "Invalid";
    }

    /**
     * Devuelve un Int que representa el estilo de la fuente (Plain, Bold, Italyc)
     * @return int: Estilo.
     */
    @Override
    public int getStyle() {
        return _font.getStyle();
    }

    /* ------------------
     * SETTERS
     * ------------------
     */

    /**
     * Funcion para configurar la fuente para que escriba en su formato negrita.
     * @param b : boolean true para activar negrita, false para volver a formato plano.
     */
    @Override
    public void setBold(boolean b)
    {
        if (b)
        {
            _font.deriveFont(Font.BOLD);
        }
        else
        {
            _font.deriveFont(Font.PLAIN);
        }
    }

    /**
     * Cambia el estilo cursiva de la fuente.
     * @param b si activar (true) o desactivar (false) el modo cursiva.
     */
    @Override
    public void setItalic(boolean b)
    {
        if (b)
        {
            _font.deriveFont(Font.ITALIC);
        }
        else
        {
            _font.deriveFont(Font.PLAIN);
        }
    }

    /**
     * Establece el tamaño de la fuente en puntos.
     * @param s : float para establecer el tamaño en puntos de la fuente.
     */
    @Override
    public void setSize(float s)
    {
        _font.deriveFont(s);
    }


}
