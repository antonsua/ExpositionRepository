package es.ucm.moviles.engineinterface;
import java.util.List;

public interface InputInterface {
    // OJO! Los eventos van con las coordenadas físicas de la ventana, no de la lógica.
    enum touchType{PRESSED, RELEASED, DRAGGED, INVALID}

    /**
     * Devuelve una copia de la lista de eventos generada desde la última vez
     * que se solicito esta con este metodo. Despues vacia la lista de eventos.
     * @return
     */
    List<TouchEvent> getTouchEvents();
}
