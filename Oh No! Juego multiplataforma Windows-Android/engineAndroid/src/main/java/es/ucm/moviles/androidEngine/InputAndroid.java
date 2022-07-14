package es.ucm.moviles.androidEngine;

import android.view.MotionEvent;
import android.view.SurfaceView;
import android.view.View;

import java.util.ArrayList;
import java.util.List;

import es.ucm.moviles.engineinterface.InputInterface;
import es.ucm.moviles.engineinterface.TouchEvent;

public class InputAndroid implements InputInterface, View.OnTouchListener
{
    // Variables de clase
    private ArrayList<TouchEvent> _eventList;

    /**
     * Constructora de la clase
     * Recibe la ventana y se registra como listener de los eventos
     * de teclado y ratón para responder a ellos.
     * @param surf Surfaceview: Superficie de ventana que recibe eventos.
     */
    InputAndroid(SurfaceView surf)
    {
        _eventList = new ArrayList<>();
        try
        {
            surf.setOnTouchListener(this);
        }
        catch(Exception e)
        {
            System.err.printf(e.getMessage());
        }
    }

    /* -----------------------------
     * Gestión de evento singular
     * -----------------------------
     */

    /**
     * Clase sincronizada con getTouchEvents para evitar problemas entre lectura y escritura
     * de variables entre hilos. Ver getTouchEvents más abajo.
     * @param tE : Touch Event generado y listo para ser añadido a la lista.
     */
    public synchronized void addEventToList(TouchEvent tE)
    {
        _eventList.add(tE);
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
    public synchronized List<TouchEvent> getTouchEvents()
    {
        // Creamos una copia de  la lista de eventos
        ArrayList<TouchEvent> listToSend = new ArrayList<>();
        listToSend = (ArrayList)_eventList.clone();

        // Vaciamos la lista actual
        _eventList.clear();

        // Devolvemos la copia
        return listToSend;
    }

    /**
     * Callback del surface al recibir un evento.
     * Los eventos se almacenan en la coordenada ventana.
     * @param view
     * @param motionEvent
     * @return
     */
    @Override
    public boolean onTouch(View view, MotionEvent motionEvent) {

            //System.out.println("Input añadido en: " + motionEvent.getX() + ", " + motionEvent.getY() );

        // Generamos un nuevo evento del tipo interfaz
        TouchEvent e = new TouchEvent();

        // Segun el tipo de evento...
        switch (motionEvent.getAction())
        {
            case MotionEvent.ACTION_DOWN:
                e.setActionPerfomed(touchType.PRESSED);
                e.setPosX((int) motionEvent.getX());
                e.setPosY((int) motionEvent.getY());
                break;
            case MotionEvent.ACTION_UP:
                e.setActionPerfomed(touchType.RELEASED);
                e.setPosX((int) motionEvent.getX());
                e.setPosY((int) motionEvent.getY());
                break;
        }

        // Llamada al Metodo sincronizado para añadir eventos en la lista.
        addEventToList(e);

        return true;
    }
}
