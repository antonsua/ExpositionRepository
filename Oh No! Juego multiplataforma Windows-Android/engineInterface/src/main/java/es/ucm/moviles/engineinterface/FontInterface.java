package es.ucm.moviles.engineinterface;

public interface FontInterface
{

    /* ---------------------------------------
     * GETTERS
     * ---------------------------------------
     */

    /**
     * Devuelve si la fuente esta en modo negrita.
     * @return boolean: true si lo esta, false en caso contrario.
     */
    boolean isBold();

    /**
     * Devuelve si la fuente esta en modo cursiva.
     * @return boolean: true si lo esta, false en caso contrario.
     */
    boolean isItalic();

    /**
     * Devuelve el tamaño de la fuente en puntos.
     * @return int: tamaño.
     */
    int getSize();

    /**
     * Devuelve el identificador de la fuente.
     * @return string: nombre de la fuente.
     */
    String getFontName();

    /**
     * Devuelve un Int que representa el estilo de la fuente (Plain, Bold, Italyc)
     * @return int: Estilo.
     */
    int getStyle();

    /**
     * Cambia el estilo negrita de la fuente.
     * @param b si activar (true) o desactivar (false) el modo negrita.
     */
    void setBold(boolean b);

    /**
     * Cambia el estilo cursiva de la fuente.
     * @param b si activar (true) o desactivar (false) el modo cursiva.
     */
    void setItalic(boolean b);

    /**
     * Cambia el tamaño de la fuente.
     * Puede que necesite llamar al motor de pintado para establecer el tamaño.
     * @param s float tamaño en puntos.
     */
    void setSize(float s);

}
