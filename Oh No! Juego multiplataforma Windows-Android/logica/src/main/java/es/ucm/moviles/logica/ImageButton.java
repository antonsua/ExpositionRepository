package es.ucm.moviles.logica;

import es.ucm.moviles.engineinterface.GraphicsInterface;
import es.ucm.moviles.engineinterface.ImageInterface;
import es.ucm.moviles.engineinterface.Position;

/**
 * Implementa un boton formado por una imagen.
 */
public class ImageButton
{
    protected Position _position;
    protected ImageInterface _image;
    protected int _width;
    protected int _height;

    /**
     * Crea una nueva instancia de un botón e inicializa las variables internas.
     * @param position  La posición del botón en espacio lógico
     * @param image La imagen a renderizar
     * @param width El ancho que debe ocupar el botón en espacio lógico
     * @param height El alto que debe ocupar el botón en espacio lógico
     */
    public ImageButton(Position position, ImageInterface image, int width, int height)
    {
        _position = new Position(position.getX(), position.getY());
        _image = image;
        _width = width;
        _height = height;
    }

    /**
     * Metodo de pintado del botón.
     * @param graphics motor de pintado
     */
    public void render(GraphicsInterface graphics)
    {
        graphics.drawImageInLogicSpace(_image, _position.getX(), _position.getY(), _width, _height);
    }

    public boolean inside(Position pos) {
        //System.out.println("ImageButton::inside() Given Pos:(x:"+pos.x()+",y:"+pos.y()+")");
        final Position extendedPosition = new Position(_position.getX()+_width, _position.getY()+_height);
        final Position upperLeft = _position; // UpLeft corner
        final Position downRight = extendedPosition; // DownRight corner

        boolean isIn = pos.getX() >= upperLeft.getX() && pos.getX() <= downRight.getX()
                && pos.getY() >= upperLeft.getY() && pos.getY() <= downRight.getY();

        //if (isIn) System.out.println("ImageButton::inside()  is inside ButtonArea: p1(x:"+upperLeft.x()+",y:"+upperLeft.y()+") -> p2(x:"+downRight.x()+",y:"+downRight.y()+")");
        //else  System.out.println("ImageButton::inside() is OUTSIDE ButtonArea: p1(x:"+upperLeft.x()+",y:"+upperLeft.y()+") -> p2(x:"+downRight.x()+",y:"+downRight.y()+")");
        return isIn;
    }
}
