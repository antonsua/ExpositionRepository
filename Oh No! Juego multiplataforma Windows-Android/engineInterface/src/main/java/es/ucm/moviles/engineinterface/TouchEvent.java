package es.ucm.moviles.engineinterface;

/**
 * Clase Interfaz que almacenará los valores característicos de un evento
 * generado por la interacción del usuario con la pantalla de la aplicación.
 */
public class TouchEvent
{
    Position _position;// Posición de la accion

    /* Estos atributos seran requeridos por el Engine de cada plataforma, requiriendo _fingerId
    en Android y _buttonId en PC*/
    // No son utilizados en esta práctica por lo que no se ha programado su getter/setter
    int _fingerId; //Identificador del dedo detectado
    int _buttonId; //Identificador del boton pulsado

    InputInterface.touchType _actionPerformed;  //Identificador de la accion realizada

    /**
     * Constructor por defecto sin parametros
     * Crea un evento en una posición (0,0)
     */
    public TouchEvent()
    {
        _position = new Position();
    }

    /**
     * Constructor con parametros de tipo y coordenadas separadas.
     * @param type touchType enum. Tipo de interacción del evento.
     * @param x int coordenadas en el eje X
     * @param y int coordenadas en el eje Y
     */
    public TouchEvent(InputInterface.touchType type, int x, int y){  //Crea un nuevo evento con su tipo y posicion
        this(type, new Position(x, y));
    }

    /**
     * Constructor con parametros de tipo y coordenadas a traves
     * del tipo Position.
     * @param type touchType enum. Tipo de interacción del evento.
     * @param position Position con las coordenadas del evento.
     */
    public TouchEvent(InputInterface.touchType type, Position position)
    {
        this._actionPerformed = type;
        _position = position;
    }

    /* -------------------------------------------
     * GETTERS
     * -------------------------------------
     */
    /**
     * Devuelve la posición donde se ha generado el evento
     * a través de un tipo Position.
     * @return Position que contiene las coordenadas
     */
    public Position getPosition(){ return _position; }

    /**
     *
     * @return
     */
    public int getPosX(){ return _position.getX(); }

    /**
     *
     * @return
     */
    public int getPosY(){ return _position.getY(); }

    /**
     *
     * @return
     */
    public InputInterface.touchType getTouchType()
    {
        if (_actionPerformed != null) return _actionPerformed;
        else return InputInterface.touchType.INVALID;
    }

    /* ---------------------------------------------------
     * SETTERS
     * ---------------------------------------------------
     */
    /**
     *
     * @param x
     */
    public void setPosX(int x)
    {
        _position.setX(x);
    }

    /**
     *
     * @param y
     */
    public void setPosY(int y)
    {
        _position.setY(y);
    }

    /**
     * Cambia el valor de interno de la interacción que representa el evento.
     * @param tt enum touchType con el tipo de interacción a establecer
     */
    public void setActionPerfomed(InputInterface.touchType tt)
    {
        _actionPerformed = tt;
    }
}
