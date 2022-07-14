package es.ucm.moviles.logica;

import es.ucm.moviles.engineinterface.FontInterface;
import es.ucm.moviles.engineinterface.GraphicsInterface;
import es.ucm.moviles.engineinterface.Position;
import es.ucm.moviles.engineinterface.RGBColor;

public class LevelButton
{
    protected Position _position;
    protected FontInterface _font;
    protected float _fontSize;
    protected String _text;
    protected int _radius;
    protected RGBColor _circleColor;
    protected RGBColor _textColor;

    /**
     * Crea una nueva instancia de un GameObject Botón,
     * el botón será un circulo con un texto blanco.
     *
     * @param position  La posición centrada del botón
     * @param text Mensaje que contendrá
     * @param font El tipo de letra que utilizará el texto
     * @param fontSize Tamaño de la fuente.
     * @param radius El alto que debe ocupar el botón
     */
    public LevelButton(Position position, String text, FontInterface font, float fontSize, int radius, RGBColor circleColor, RGBColor textColor)
    {
        _position = position;
        _text = text;
        _font = font;
        _fontSize = fontSize;
        _radius = radius;
        _circleColor = circleColor;
        _textColor = textColor;
    }

    /**
     * Metodo de pintado del botón.
     * @param graphics motor de pintado
     */
    public void render(GraphicsInterface graphics)
    {
        // Circulo
        graphics.setColor(_circleColor);
        graphics.fillCircleInLogicSpace(_position.getX(), _position.getY(), _radius);
        graphics.setColor(_textColor);
        // Texto
        graphics.setFont(_font);
        graphics.setFontSize(_fontSize);
        int offset = (int)(_fontSize/4f);
        graphics.drawTextInLogicSpace(_text, _position.getX()-offset, _position.getY()+offset, true);
    }

    /**
     * Devuelve si se ha clicado dentro de la zona de acción de la instancia del botón.
     * @param pos La posición a comprobar
     * @return boolean true si ha caido dentro o false si esta fuera.
     */
    public boolean inside(Position pos)
    {
        Position upLeft = new Position(_position.getX()-(_radius), _position.getY()-(_radius));
        Position downRight = new Position(_position.getX()+(_radius), _position.getY()+(_radius));
        return pos.getX() >= upLeft.getX() && pos.getX() <= downRight.getX()
                && pos.getY() >= upLeft.getY() && pos.getY() <= downRight.getY();
    }
}
