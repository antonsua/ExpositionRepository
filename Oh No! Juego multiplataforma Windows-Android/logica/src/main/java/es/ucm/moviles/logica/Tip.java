package es.ucm.moviles.logica;

import java.util.HashMap;
import java.util.Map;

public class Tip
{
    public enum Kind
    {
        /**
         *  Si un número tiene ya visibles el número de celdas que dice, entonces se puede
         * “cerrar”, es decir, poner paredes en los extremos.
         */
        CAN_BE_CLOSED,
        /**
         * Si pusiéramos un punto azul en una celda vacía, superaríamos el número de visibles
         * del número, y por tanto, debe ser una pared.
         */
        MUST_BE_WALL,
        /**
         * Si no ponemos un punto en alguna celda vacía, entonces es imposible alcanzar el
         * número.
         */
        MUST_BE_TILE,
        /**
         * Un número tiene más casillas azules visibles de las que debería.
         */
        ERROR_TOO_MANY_TILES,
        /**
         * Un número tiene una cantidad insuficiente de casillas azules visibles y sin embargo
         * ya está “cerrada” (no puede ampliarse más por culpa de paredes)
         */
        ERROR_NOT_ENOUGH_TILES_BUT_CLOSED,

        /**
         * En sentido opuesto, una celda de tipo número no está cerrada pero si se ponen en
         * punto el resto de celdas vacías que tiene alcanzables no llegará a su valor, por lo
         * que es un futuro error. Si no se incluye esta pista, el programa dará incorrectamente
         * varias veces la pista 3 para al final terminar indicando el error de la 5.
         */
        ERROR_NOT_ENOUGH_TILES_BUT_OPEN,
        /**
         * Si una celda está vacía y cerrada y no ve ninguna celda azul, entonces es pared (todos
         * los puntos azules deben ver al menos a otro).
         * En sentido opuesto, si hay una celda punto puesta por el usuario que está cerrada
         * y no ve a ninguna otra, entonces se trata de un error por el mismo motivo
         */
        CLOSED_MUST_BE_WALL,

    }
    private Kind _kind;
    private Tile _tile;

    public Tip(Kind kind, Tile tile){ _kind = kind; _tile = tile;}

    public Tile getTile() {
        return _tile;
    }

    public Kind getKind() {
        return _kind;
    }

    public boolean isError()
    {
        return _kind == Kind.ERROR_NOT_ENOUGH_TILES_BUT_CLOSED
            || _kind == Kind.ERROR_NOT_ENOUGH_TILES_BUT_OPEN
            || _kind == Kind.ERROR_TOO_MANY_TILES;

    }

    public String getMessage() { return _msgs.get(_kind);}

    /**
     * Returns a string representation of the object. In general, the
     * {@code toString} method returns a string that
     * "textually represents" this object. The result should
     * be a concise but informative representation that is easy for a
     * person to read.
     * It is recommended that all subclasses override this method.
     * <p>
     * The {@code toString} method for class {@code Object}
     * returns a string consisting of the name of the class of which the
     * object is an instance, the at-sign character `{@code @}', and
     * the unsigned hexadecimal representation of the hash code of the
     * object. In other words, this method returns a string equal to the
     * value of:
     * <blockquote>
     * <pre>
     * getClass().getName() + '@' + Integer.toHexString(hashCode())
     * </pre></blockquote>
     *
     * @return a string representation of the object.
     */
    @Override
    public String toString() {
        return String.format("{Kind: %s, Tile: %s}", _kind, _tile);
    }

    private static final Map<Kind, String> _msgs;
    static
    {
        _msgs = new HashMap<>();
        _msgs.put(Kind.CAN_BE_CLOSED, "Esta casilla ya ve todas sus casillas");
        _msgs.put(Kind.MUST_BE_WALL, "Esta debería de ser fácil...");
        _msgs.put(Kind.MUST_BE_TILE, "Esta casilla debe ser azul");
        _msgs.put(Kind.ERROR_TOO_MANY_TILES, "Esta casilla ve demasiado");
        _msgs.put(Kind.ERROR_NOT_ENOUGH_TILES_BUT_CLOSED, "Esta casilla no puede ver lo necesario");
        _msgs.put(Kind.ERROR_NOT_ENOUGH_TILES_BUT_OPEN, "Esta casilla no va a poder ver lo necesario, algo falla...");
        _msgs.put(Kind.CLOSED_MUST_BE_WALL, "Todos los puntos azules deben ver al menos otro");

    }
}
