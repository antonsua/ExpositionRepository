package es.ucm.moviles.engineinterface;

/**
 * Clase que gestiona los recursos.
 * Se comunicara con el Graphics, para establecer la fuente actual en su motor de pintado.
 * Contendrá una serie de diccionarios internos para cada tipo de recursos (Fuente, Imagen, Sonido)
 * El engine se encarga de gestionar la instancia del resource manager.
 */
public interface ResourcesInterface
{
    /* -----------------------------
     * FUENTES
     * -----------------------------
     */
    /**
     * Metodo que genera una nueva fuente y la añade al diccionario interno de fuentes.
     * @param filename : string, Nombre del archivo, usado como identificador.
     * @param size : int, tamaño de la fuente en puntos.
     * @param style : int, Formato de la fuente (0=plain, 1=negrita, 2=cursiva).
     * @return boolean true si la fuente se ha cargado correctamente o existía, false en caso contrario.
     */
    boolean loadFont(String filename, int size, int style);

    /**
     * Devuelve una instancia de fuente con el nombre solicitado
     * @return FontInterface o null si no es encontrada.
     */
    FontInterface getFont(String fontName);

    /* -----------------------------
     * IMAGENES
     * -----------------------------
     */
    /**
     * Metodo que genera una nueva fuente y la añade al diccionario interno de fuentes.
     * @param filename : string, Nombre del archivo, usado como identificador.
     * @return boolean true si la imagen se ha cargado correctamente o existía, false en caso contrario.
     */
    boolean loadImage(String filename);

    /**
     * Metodo para obtener una imagen en concreto con el nombre solicitado
     * @param name String con el identificador de la imagen
     * @return ImageInterface de la imagen solicitada o null si no es encontrada.
     */
    ImageInterface getImage(String name);

    /* -----------------------------
     * SONIDO
     * -----------------------------
     */
    /**
     * Metodo que genera una nueva instancia de audio y la añade al diccionario interno de pistas de audio.
     * @param filename : string, Nombre del archivo, usado como identificador.
     * @return boolean true si la pista se ha cargado correctamente o existía, false en caso contrario.
     */
    boolean loadSourceAudio(String filename);

    /**
     * Metodo para obtener una pista de audio en concreto con el nombre solicitado
     * @param name String con el identificador de la pista de audio
     * @return AudioInterface de la pista solicitada o null si no es encontrada.
     */
    AudioInterface getAudio(String name);
}
