package es.ucm.moviles.engineinterface;

public interface Scene
{
    // El motor conoce el interfaz
    /**
     * Recibe el motor de juego especifico de la plataforma que lo ejecuta
     * y recoge en variables internas las instancias importantes de este.
     * Llama a cargar los recursos necesarios para esta escena.
     * @param e Motor de juego de la plataforma que lo ha lanzado.
     */
    void init(Engine e);

    /**
     * Metodo para llamar al update de los objetos.
     * @param deltaTime float con el tiempo transcurrido desde el anterior ciclo de ejecución.
     */
    void onUpdate(float deltaTime);

    /**
     * Metodo para llamar a los renders
     * @param g motor grafico que contiene los metodos de renderizado.
     */
    void onRender(GraphicsInterface g); // Se pasa el graphics desde el bucle principal en el EnginePC
}
