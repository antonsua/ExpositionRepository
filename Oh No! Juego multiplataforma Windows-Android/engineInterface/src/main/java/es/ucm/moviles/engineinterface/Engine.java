package es.ucm.moviles.engineinterface;

public interface Engine
{
    /* -----------------------
     * GETTERS
     * -----------------------
     */
    /**
     * Devuelve la instancia dle gestor de recursos.
     * @return ResurcesInterface o null.
     */
    ResourcesInterface getResources();

    /**
     * Devuelve la instancia del motor de dibujado para utilizar sus métodos.
     * @return Graphics interfaz o null.
     */
    GraphicsInterface getGraphics();

    /**
     * Devuelve instancia del input interface.
     * @return InputInterface o null.
     */
    InputInterface getInput();

    /* ----------------------
     * SETTERS
     * ----------------------
     */

    /**
     * Devuelve instancia del audio interface.
     * @return AudioInterface o null.
     */
     ResourceManagerInterface getAudioManager();

    /**
     * Enlace con la clase Interfaz usado para que el bucle principal se pase a la lógica.
     * @param scn
     */
    void setScene(Scene scn);

    ResourceManagerInterface getFontManager();
    ResourceManagerInterface getImageManager();
}
