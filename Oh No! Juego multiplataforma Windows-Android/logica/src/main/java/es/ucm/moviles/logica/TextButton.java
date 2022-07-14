package es.ucm.moviles.logica;

import es.ucm.moviles.engineinterface.FontInterface;
import es.ucm.moviles.engineinterface.GraphicsInterface;
import es.ucm.moviles.engineinterface.Position;

/**
 * Gameobject que modela un botón que consiste solo en un texto.
 */
public class TextButton
{
    protected Position _position;
    protected FontInterface _font;
    protected float _fontSize;
    protected StringBuilder _textBuilder1; // Texto único o para la primera linea
    protected StringBuilder _textBuilder2; // Texto para la segunda linea
    protected int _width;
    protected int _height;

    /**
     * Crea una nueva instancia de un GameObject Botón,
     * el cual llamará al callback dado cuando sea clicado
     *
     * @param position  La posición centrada del botón
     * @param text Mensaje que contendrá
     * @param font El tipo de letra que utilizará el texto
     * @param fontSize Tamaño de la fuente.
     * @param width El ancho que debe ocupar el botón
     * @param height El alto que debe ocupar el botón
     */
    public TextButton(Position position, String text, FontInterface font, float fontSize, int width, int height)//, OnClickListener onClickCallback)
    {
        _position = position;
        _textBuilder1 = new StringBuilder();
        _textBuilder1.append(text);
        _font = font;
        _fontSize = fontSize;
        _width = width;
        _height = height;
    }

    /**
     * Crea una nueva instancia de un GameObject Botón,
     * el cual llamará al callback dado cuando sea clicado
     *
     * @param position  La posición centrada del botón
     * @param textOne Mensaje que contendrá la primera línea
     * @param textTwo Mensaje que contendrá la segunda línea
     * @param font El tipo de letra que utilizará el texto
     * @param fontSize Tamaño de la fuente.
     * @param width El ancho que debe ocupar el botón
     * @param height El alto que debe ocupar el botón
     */
    public TextButton(Position position, String textOne, String textTwo, FontInterface font, float fontSize, int width, int height)//, OnClickListener onClickCallback)
    {
        _position = position;
        _textBuilder1 = new StringBuilder();
        _textBuilder1.append(textOne);
        _textBuilder2 = new StringBuilder();
        _textBuilder2.append(textTwo);
        _font = font;
        _fontSize = fontSize;
        _width = width;
        _height = height;
    }

    /* ------------------------------
     * SETTERS
     * ------------------------------
     */

    /**
     * Metodo para cambiar el texto a mostrar en el boton
     * Sustituye el texto anterior por el nuevo dado
     * @param text String con el texto a establecer.
     */
    public void setText(String text)
    {
        _textBuilder1.delete(0,_textBuilder1.length());
        _textBuilder1.append(text);
    }

    /**
     * Metodo para cambiar el texto a mostrar en el boton
     * Sustituye el texto anterior por el nuevo dado
     * @param firstLine String con el texto a establecer en la primera linea
     * @param secondLine String con el texto a establecer en la segunda linea
     */
    public void setText(String firstLine, String secondLine)
    {
        _textBuilder1.delete(0,_textBuilder1.length());
        _textBuilder1.append(firstLine);
        if (_textBuilder2 == null) _textBuilder2 = new StringBuilder();
        _textBuilder2.delete(0,_textBuilder2.length());
        _textBuilder2.append(secondLine);
    }

    /**
     * Metodo para cambiar el tamaño de la fuente.
     * @param size
     */
    public void setFontSize(float size)
    {
        _fontSize = size;
    }

    /**
     * Permite cambiar la posición del boton dinamicamente
     * @param p
     */
    public void setPosition(Position p)
    {
        _position = p;
    }

    /**
     * Metodo de pintado del botón y su texto en una linea
     * @param graphics motor de pintado
     */
    public void render(GraphicsInterface graphics)
    {
        graphics.setFont(_font);
        graphics.setFontSize(_fontSize);
        graphics.drawTextInLogicSpace(_textBuilder1.toString(), _position.getX(), _position.getY(), true);
    }

    /**
     * Metodo de pintado del botn y su texto en dos lineas
     * @param graphics motor de pintado
     * @param space int: espaciado entre las dos lineas.
     */
    public void render2lines(GraphicsInterface graphics, int space)
    {
        graphics.setFont(_font);
        graphics.setFontSize(_fontSize);
        graphics.drawTextInLogicSpace(_textBuilder1.toString(), _position.getX(), _position.getY()-(int)(space/2f), true);
        graphics.drawTextInLogicSpace(_textBuilder2.toString(), _position.getX(), _position.getY()+(int)(space/2f), true);
    }


    /**
     * Devuelve si se ha clicado dentro de la zona de acción de la instancia del botón.
     * @param pos La posición a comprobar
     * @return boolean true si ha caido dentro o false si esta fuera.
     */
    public boolean inside(Position pos)
    {
        // TODO - Esto esta un poquito mal para un boton con texto
        // El texto se dibuja en la posición indicada y crece expandiendose hacia arriba (-y)
        // y hacia la derecha (+x)
        // es dificil saber su tamaño basandonos en su posición, ya que depende del tamaño y tipo
        // de la fuente, así que habría que calcular el centro en base a eso y luego ya derivar
        // las esquinas de la zona pulsable. Es complicado, para simplificar por ahora
        // simplemente tomamos la posición de pintado del texto y a partir de ahí se define
        // como otro botón, aunque el area de pulsado no estará bien centrada con el texto
        // ser generosos a la hora de darle height y width
        Position upLeft = new Position(_position.getX()-(_width/2), _position.getY()-(_height/2));
        Position downRight = new Position(_position.getX()+(_width/2), _position.getY()+(_height/2));
        //final Position upLeft = _position.sub(halfExtend); // UpLeft corner
        //final Position downRight = _position.add(halfExtend); // DownRight corner

        //System.out.println("TextButton::inside() Given Pos:(x:"+pos.getX()+",y:"+pos.getY()+")");
        boolean isIn = pos.getX() >= upLeft.getX() && pos.getX() <= downRight.getX()
                && pos.getY() >= upLeft.getY() && pos.getY() <= downRight.getY();
        //if (isIn) System.out.println("TextButton::inside()  is inside ButtonArea: p1(x:"+upLeft.x()+",y:"+upLeft.y()+") -> p2(x:"+downRight.x()+",y:"+downRight.y()+")");
        //    else  System.out.println("TextButton::inside() is OUTSIDE ButtonArea: p1(x:"+upLeft.x()+",y:"+upLeft.y()+") -> p2(x:"+downRight.x()+",y:"+downRight.y()+")");
        return isIn;
    }
}

