package es.ucm.moviles.logica;

import java.util.HashMap;

public class Tile
{
    public enum Kind implements IIterableEnum<Kind>
    {
        UNKNOWN,
        TILE,
        WALL;

        @Override
        public Kind next() {

            int i = (ordinal() + 1) % values().length;
            return values()[i];
        }
    }

    public static final int NOT_A_NUMBER_VALUE = -1;

    private final Coordinate _coord;
    private Kind _kind;
    private int _number;
    private boolean _locked;

    public Tile(Coordinate coord, Kind kind)
    {
        this._coord = coord;
        this._kind = kind;
        this._number = NOT_A_NUMBER_VALUE;
        this._locked = false;
    }

    public Tile(int row, int col, Kind kind)
    {
        this(new Coordinate(row, col), kind);
    }
    public Tile(Coordinate coord, int number)
    {
        this(coord, Kind.TILE);
        this._number = number;
    }

    public Tile(int row, int col, int number)
    {
        this(new Coordinate(row, col), number);
    }

    public Coordinate getCoord(){ return _coord;}
    public int getNumber()      { return _number;}
    public Kind getKind()       { return _kind; }

    public boolean isUndefined()    { return _kind   == Kind.UNKNOWN;}
    public boolean isWall()         { return _kind   == Kind.WALL;}
    public boolean isTile()         { return _kind   == Kind.TILE;}
    public boolean isNumber()       { return isTile() &&_number != NOT_A_NUMBER_VALUE;}
    public boolean isLocked()       { return  _locked;}

    public void lock()                  { _locked = true; }
    public void unlock()                { _locked = false;}
    public void setLock(boolean value)  { _locked = value;}

    public void setKind(Kind kind)   { _kind = kind;  _number = NOT_A_NUMBER_VALUE;}
    public void setAsUndefined()     { setKind(Kind.UNKNOWN); }
    public void setAsWall()          { setKind(Kind.WALL);    }
    public void setAsTile()          { setKind(Kind.TILE);    }
    public void setAsTile(int number)
    {
        setKind(Kind.TILE);
        _number = number == 0 ?
                NOT_A_NUMBER_VALUE :
                number;
    }


    /**
     * Returns a string representation of the object. In general, the
     * {@code toString} method returns a string that
     * "textually represents" this object. The result should
     * be a concise but informative representation that is easy for a
     * person to read.
     * It is recommended that all subclasses override this method.
     * <p>
     * @return a string representation of the object.
     */
    @Override
    public String toString() {
        return String.format("{%s: %s %s}",
                _coord.toString(),
                _kind.toString(),
                isNumber() ? "("+ _number +")" : ""
        );
    }

    @Override
    public Object clone() {
        Tile copy = new Tile((Coordinate) this._coord.clone(),this._kind);
        copy._locked = this._locked;
        copy._number = this._number;
        return copy;
    }

    /**
     * Indicates whether some other object is "equal to" this one.
     * <p>
     * The {@code equals} method implements an equivalence relation
     * on non-null object references:
     * <ul>
     * <li>It is <i>reflexive</i>: for any non-null reference value
     *     {@code x}, {@code x.equals(x)} should return
     *     {@code true}.
     * <li>It is <i>symmetric</i>: for any non-null reference values
     *     {@code x} and {@code y}, {@code x.equals(y)}
     *     should return {@code true} if and only if
     *     {@code y.equals(x)} returns {@code true}.
     * <li>It is <i>transitive</i>: for any non-null reference values
     *     {@code x}, {@code y}, and {@code z}, if
     *     {@code x.equals(y)} returns {@code true} and
     *     {@code y.equals(z)} returns {@code true}, then
     *     {@code x.equals(z)} should return {@code true}.
     * <li>It is <i>consistent</i>: for any non-null reference values
     *     {@code x} and {@code y}, multiple invocations of
     *     {@code x.equals(y)} consistently return {@code true}
     *     or consistently return {@code false}, provided no
     *     information used in {@code equals} comparisons on the
     *     objects is modified.
     * <li>For any non-null reference value {@code x},
     *     {@code x.equals(null)} should return {@code false}.
     * </ul>
     * <p>
     * The {@code equals} method for class {@code Object} implements
     * the most discriminating possible equivalence relation on objects;
     * that is, for any non-null reference values {@code x} and
     * {@code y}, this method returns {@code true} if and only
     * if {@code x} and {@code y} refer to the same object
     * ({@code x == y} has the value {@code true}).
     * <p>
     * Note that it is generally necessary to override the {@code hashCode}
     * method whenever this method is overridden, so as to maintain the
     * general contract for the {@code hashCode} method, which states
     * that equal objects must have equal hash codes.
     *
     * @param obj the reference object with which to compare.
     * @return {@code true} if this object is the same as the obj
     * argument; {@code false} otherwise.
     * @see #hashCode()
     * @see HashMap
     */
    @Override
    public boolean equals(Object obj) {
        if(obj == null) return false;
        if(this == obj) return true;
        if(obj.getClass() != this.getClass()) return false;
        return equals((Tile)obj);
    }

    public boolean equals(Tile other)
    {
        return this._kind   == other._kind
            && this._number == other._number
            && this._locked == other._locked
            && this._coord.equals(other._coord);
    }
}
