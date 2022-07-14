package es.ucm.moviles.engineinterface;

public class Position {

    private int _x;
    private int _y;

    /* -----------------------
     * CONSTRUCTORAS
     * -----------------------
     */

    /**
     * Constructora por defecto.
     * Establece las coordenadas internas a 0,0
     */
    public Position() {
        _x = 0;
        _y = 0;
    }




    /**
     * Constructora con valores a establecer por parametro
     * @param x int valor para la coordenada x
     * @param y int valor para la coordenada y
     */
    public Position(int x, int y)
    {
        _x = x;
        _y = y;
    }

    /**
     * Copy constructor.
     * @param other Object to copy from. Must not bu null.
     */
    public Position(Position other) {
        if(other == null) throw new IllegalArgumentException();
       _x = other._x; _y = other._y;
    }

    public Position clone(){ return new Position(_x, _y);}


    /* -----------------------------
     * GETTERS
     * -----------------------------
     */

    /**
     * Devuelve la coordenada X almacenada
     * @return int con el valor para X
     */
    public int getX() { return _x;}

    /**
     * Devuelve la coordenada Y almacenada
     * @return int con el valor para Y
     */
    public int getY() { return _y;}


    /* -----------------------------
     * SETTERS
     * -----------------------------
     */
    /**
     * Modifica el valor interno para la coordenada X
     * @param value int con el valor a establecer
     */
    public void setX(int value) { _x = value;}

    /**
     * Modifica el valor interno para la coordenada X
     * @param value int con el valor a establecer
     */
    public void setY(int value) { _y = value;}


    public Position Add(Position rhs){ this._x += rhs._x; this._y += rhs._y; return this;}
}
