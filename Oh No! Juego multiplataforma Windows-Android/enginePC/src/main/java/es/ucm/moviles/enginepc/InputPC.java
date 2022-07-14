package es.ucm.moviles.enginepc;

// Clases a importar para escuchar al ratón y el teclado
import java.awt.event.KeyListener;
import java.awt.event.MouseListener;
// Imports con la informacion de los eventos del teclado y raton
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
// Imports de contenedores
import java.util.ArrayList;
// Import de la clase para gestionar la ventana
import javax.swing.JFrame;

// Import de la clase interfaz que gestiona los eventos
import es.ucm.moviles.engineinterface.InputInterface;
import es.ucm.moviles.engineinterface.TouchEvent;

/**
 * Esta clase es la que se encarga de gestionar el input de pc.
 * Responde tanto a teclado como a raton
 */
public class InputPC implements InputInterface, MouseListener, KeyListener
{
    // Variables de clase
    private TouchEvent _event;

    // Necesita exclusión mutua
    // La hebra swing/Renderizado es la que añade los eventos
    // La hebra lógica es la que vaciará la lista.
    // Por eso los métodos que trabajan con esta tienen el marcador syncronized en la definición de estos.
    private ArrayList<TouchEvent> _eventList;

    /**
     * Constructora de la clase
     * Recibe la ventana y se registra como listener de los eventos
     * de teclado y ratón para responder a ellos.
     * @param viewport
     */
    InputPC(JFrame viewport)
    {
        // Inicializamos las listas
        _eventList = new ArrayList<>();

        // Registramos esta clase como listener de eventos de la ventana.
        viewport.addMouseListener(this);
        viewport.addKeyListener(this);
    }

    /* -----------------------------
     * Gestión de evento singular
     * -----------------------------
     */
    /**
     * Esta clase convierte un evento de ratón en un evento de lógica genérico.
     * Al terminar lo mete en la cola de eventos.
     * @param mouseEvent
     * @param tt
     */
    public void addEvent(MouseEvent mouseEvent, InputInterface.touchType tt)
    {
        // Convertimos el MouseEvent en un touchEvent generico de la interfaz.
        _event = new TouchEvent();

        // Pasamos los datos del evento a la interfaz
        //_event.setButtonId(mouseEvent.getButton());
        //_event.setFingerId(mouseEvent.getID());
        _event.setPosX(mouseEvent.getX());
        _event.setPosY(mouseEvent.getY());
        _event.setActionPerfomed(tt);

        // Agregamos el evento a la cola de eventos de touchEvent con el método heredado
        addEventToList(_event);
    }

    /**
     * Clase sincronizada con getTouchEvents para evitar problemas entre lectura y escritura
     * de variables entre hilos. Ver getTouchEvents más abajo.
     * @param tE : Touch Event generado y listo para ser añadido a la lista.
     */
    public synchronized void addEventToList(TouchEvent tE)
    {
        _eventList.add(_event);
    }

    //------------------------------
    // METODOS DEL INTERFAZ DE INPUT
    //------------------------------
    /**
     * Manda la lista de eventos a la lógica.
     * Este metodo es synchronized e impide que se ejecute a la vez que otros eventos synchronized
     * Por ello addEventToList y getTouchEvents() tienen exclusión mutua gracias a este método de
     * marcado por parte del monitor que viene con todos los objetos JAVA.
     * @return ArrayList<TouchEvents> Lista de eventos desde la última vez que se solicitaron.
     */
    @Override
    public synchronized ArrayList<TouchEvent> getTouchEvents()
    {
        // Creamos una copia de  la lista de eventos
        ArrayList<TouchEvent> listToSend = new ArrayList<>();
        listToSend = (ArrayList)_eventList.clone();

        // Vaciamos la lista actual
        _eventList.clear();

        // Devolvemos la copia
        return listToSend;
    }


    //------------------------------
    // EVENTOS DE TECLADO
    //------------------------------

    @Override
    public synchronized void keyPressed(KeyEvent keyEvent)
    {
        // Añadir aqui si se quiere generar un evento de teclado.
    }

    @Override
    public synchronized void keyReleased(KeyEvent keyEvent)
    {
        // Añadir aqui si se quiere generar un evento de teclado.
    }

    @Override
    public void keyTyped(KeyEvent keyEvent)
    {
        // Este metodo debe overridearse pero no le daremos uso.
    }

    //------------------------------
    // EVENTOS DE RATON
    //------------------------------

    /**
     * Callback del click de ratón en la ventana.
     * Llama a registrar el evento PRESSED.
     * OJO! Esto da coordenadas físicas de la ventana, no lógicas
     * @param mouseEvent
     */
    @Override
    public synchronized void mousePressed(MouseEvent mouseEvent)
    {
        //System.out.println("InputPC::mousePressed (x:" + mouseEvent.getX() + ", y: " + mouseEvent.getY() + ")");
        addEvent(mouseEvent, touchType.PRESSED);
    }

    /**
     * Callback del click de ratón en la ventana.
     * Llama a registrar el evento RELEASED.
     * OJO! Esto da coordenadas físicas de la ventana, no lógicas
     * @param mouseEvent
     */
    @Override
    public synchronized void mouseReleased(MouseEvent mouseEvent)
    {
        //System.out.println("InputPC::mouseReleased (x: " + mouseEvent.getX() + ", y: " + mouseEvent.getY() + ")");
        addEvent(mouseEvent, touchType.RELEASED);
    }

    @Override
    public synchronized void mouseClicked(MouseEvent mouseEvent)
    {
        // Este metodo debe overridearse pero no le daremos uso.
    }

    @Override
    public void mouseEntered(MouseEvent mouseEvent)
    {
        // Este metodo debe overridearse pero no le daremos uso.
    }

    @Override
    public void mouseExited(MouseEvent mouseEvent)
    {
        // Este metodo debe overridearse pero no le daremos uso
    }

}
