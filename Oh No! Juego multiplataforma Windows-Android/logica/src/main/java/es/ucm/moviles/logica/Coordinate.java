package es.ucm.moviles.logica;

import java.util.HashMap;
import java.util.Locale;

public class Coordinate
{
    private int _row, _col;

    /*********************
     * Constructores
     *********************/
    public Coordinate(){_row = 0; _col = 0;}
    public Coordinate(int row, int col ){_row = row; _col = col;}
    public Coordinate(Coordinate other ){_row = other._row; _col = other._col;}

    /*
     * Getters y setters
     */
    public int getRow() { return _row; }
    public int getCol() { return _col; }

    public void setRow(int value) { _row = value; }
    public void setCol(int value) { _col = value; }

    /*
     * Operaciones
     */

    /**
     * Suma el valor de una coordenada al valor de la instancia
     * @param other
     * @return
     */
    public Coordinate add(Coordinate other)
    {
        _col += other._col;
        _row += other._row;

        return this;
    }

    public Coordinate mult(Coordinate other)
    {
        _col *= other._col;
        _row *= other._row;
        return this;
    }
    public Coordinate mult(int v)
    {
        _col *= v;
        _row *= v;
        return  this;
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
        Coordinate other = (Coordinate)obj;
        return equals(other);
    }

    public boolean equals(Coordinate other)
    {
        if(other == null) return false;
        return this._row == other._row && this._col == other._col;
    }

    /**
     * Creates and returns a copy of this object.  The precise meaning
     * of "copy" may depend on the class of the object. The general
     * intent is that, for any object {@code x}, the expression:
     * <blockquote>
     * <pre>
     * x.clone() != x</pre></blockquote>
     * will be true, and that the expression:
     * <blockquote>
     * <pre>
     * x.clone().getClass() == x.getClass()</pre></blockquote>
     * will be {@code true}, but these are not absolute requirements.
     * While it is typically the case that:
     * <blockquote>
     * <pre>
     * x.clone().equals(x)</pre></blockquote>
     * will be {@code true}, this is not an absolute requirement.
     * <p>
     * By convention, the returned object should be obtained by calling
     * {@code super.clone}.  If a class and all of its superclasses (except
     * {@code Object}) obey this convention, it will be the case that
     * {@code x.clone().getClass() == x.getClass()}.
     * <p>
     * By convention, the object returned by this method should be independent
     * of this object (which is being cloned).  To achieve this independence,
     * it may be necessary to modify one or more fields of the object returned
     * by {@code super.clone} before returning it.  Typically, this means
     * copying any mutable objects that comprise the internal "deep structure"
     * of the object being cloned and replacing the references to these
     * objects with references to the copies.  If a class contains only
     * primitive fields or references to immutable objects, then it is usually
     * the case that no fields in the object returned by {@code super.clone}
     * need to be modified.
     * <p>
     * The method {@code clone} for class {@code Object} performs a
     * specific cloning operation. First, if the class of this object does
     * not implement the interface {@code Cloneable}, then a
     * {@code CloneNotSupportedException} is thrown. Note that all arrays
     * are considered to implement the interface {@code Cloneable} and that
     * the return type of the {@code clone} method of an array type {@code T[]}
     * is {@code T[]} where T is any reference or primitive type.
     * Otherwise, this method creates a new instance of the class of this
     * object and initializes all its fields with exactly the contents of
     * the corresponding fields of this object, as if by assignment; the
     * contents of the fields are not themselves cloned. Thus, this method
     * performs a "shallow copy" of this object, not a "deep copy" operation.
     * <p>
     * The class {@code Object} does not itself implement the interface
     * {@code Cloneable}, so calling the {@code clone} method on an object
     * whose class is {@code Object} will result in throwing an
     * exception at run time.
     *
     * @return a clone of this instance.
     * @throws CloneNotSupportedException if the object's class does not
     *                                    support the {@code Cloneable} interface. Subclasses
     *                                    that override the {@code clone} method can also
     *                                    throw this exception to indicate that an instance cannot
     *                                    be cloned.
     * @see Cloneable
     */
    @Override
    protected Object clone() {
        return new Coordinate(this);
    }

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
        return String.format(Locale.getDefault(), "(%d, %d)", _row, _col);
    }

    /**
     * Devuelve una nueva instancia con el resultado de la suma de los parámetros
     * @param lhs Una instancia
     * @param rhs Otra instancia
     * @return una nueva instancia
     */
    public static Coordinate add(Coordinate lhs, Coordinate rhs)
    {
        return new Coordinate(lhs).add(rhs);
    }
    public static Coordinate mult(Coordinate lhs, Coordinate rhs)
    {
        return new Coordinate(lhs).mult(rhs);
    }
    public static Coordinate mult(int lhs, Coordinate rhs)
    {
        return mult(rhs, lhs);
    }
    public static Coordinate mult(Coordinate lhs, int rhs)
    {
        return new Coordinate(lhs).mult(rhs);
    }

    public boolean is(int row, int col){ return this._row == row && this._col == col;}

    public static final Coordinate ZERO  = new Coordinate(0, 0);
    public static final Coordinate UP    = new Coordinate(-1, 0);
    public static final Coordinate DOWN  = new Coordinate(1, 0);
    public static final Coordinate RIGHT = new Coordinate(0, 1);
    public static final Coordinate LEFT  = new Coordinate(0, -1);

    public static final Coordinate[] DIRECTIONS = new Coordinate[]{UP, DOWN, RIGHT, LEFT};
}
