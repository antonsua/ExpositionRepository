package es.ucm.moviles.logica;

import es.ucm.moviles.engineinterface.GraphicsInterface;
import es.ucm.moviles.engineinterface.ImageInterface;
import es.ucm.moviles.engineinterface.InputInterface;
import es.ucm.moviles.engineinterface.Position;
import es.ucm.moviles.engineinterface.RGBColor;
import es.ucm.moviles.engineinterface.TouchEvent;

public class TileObj extends GameObject {
    Tile _tile;
    BoardObj _board;
    Position _pos;
    private final float _animationDuration;
    private final int _width;
    private final int _radius;
    private float _scale = 1.0f;
    private boolean _selected = false;

    private static final RGBColor GREY  = new RGBColor(220,220,220); // Color gris.
    private static final RGBColor BLUE  = new RGBColor(100,175,255); // Color azul.
    private static final RGBColor RED   = new RGBColor(255, 80, 80); // Color rojo.

    private RGBColor _currentColor;

    private Animation _animation;
    static private ImageInterface _lockImg;

    public TileObj(BoardObj board, Tile tile, Position pos, float width, float radius, float animationDuration) {
        this._board = board;
        this._tile = tile;
        this._pos = pos;
        this._width =  (int)Math.floor(width);
        this._radius = (int)Math.floor(radius);
        this._currentColor = getKindColor(_tile.getKind());
        this._animationDuration = animationDuration;
        this._animation = null;

    }

    public static void setLockImage(ImageInterface img)
    {
        _lockImg = img;
    }
    public void setTile(Tile tile)
    {
        if(tile == null)
        {
            System.err.println("Qué coño hace metiendo una tile null");
        }

        System.err.printf("Cambiado tile de %s a %s\n", _tile, tile);
        _tile = tile;
    }

    public void setSelected(boolean value)
    {
        _selected = value;
    }

    public boolean getSelected(){ return _selected;}



    public Coordinate getCoord()  { return _tile.getCoord();}
    public int getNumber()        { return _tile.getNumber();}
    public Tile.Kind getKind()    { return _tile.getKind(); }

    public boolean isUndefined()  { return _tile.isUndefined();}
    public boolean isWall()       { return _tile.isWall();}
    public boolean isTile()       { return _tile.isTile();}
    public boolean isNumber()     { return _tile.isNumber();}
    public boolean isLocked()     { return _tile.isLocked();}


    @Override
    public void update(float deltaTime)
    {
        if(_animation != null)
        {
            _animation.update(deltaTime);

            if(!_animation.hasEnded())
            {
                if(isLocked())
                {
                    ScaleAnimation sa = (ScaleAnimation)_animation;
                    _scale = sa.getScale();
                }
                else
                {
                    ColorAnimation ca = (ColorAnimation)_animation;
                    _currentColor = ca.getColor();
                }
            }
            else
            {
                if(!isLocked())
                {
                    //EL ORDEN IMPORTA
                    Tile.Kind nKind =_tile.getKind().next();
                    _tile.setKind(nKind);
                    _board.onTileChanged(_tile);
                }
                _animation = null;
            }
        }
        else
        {
            _currentColor = getKindColor(_tile.getKind());
        }
    }

    @Override
    public void render(GraphicsInterface g)
    {
        int radius = (int)(((float)(_radius)) * _scale);
        g.setColor(_currentColor);
        g.fillCircleInLogicSpace(_pos.getX(), _pos.getY(), radius);
        if(_tile.isNumber())
        {
            String nStr = Integer.toString(_tile.getNumber());
            g.setColor(RGBColor.WHITE);
            g.drawTextInLogicSpace(nStr,
                    _pos.getX() - (radius/2),
                    _pos.getY() + (radius/2),
                    true);
        }
        else if(_tile.isWall() && _tile.isLocked())
        {
            int offset = radius /2;
            g.drawImageInLogicSpace(_lockImg,
                    _pos.getX() - offset,
                    _pos.getY() - offset,
                    radius, radius);
        }

        if(_selected)
        {
            g.setColor(RGBColor.BLACK);
            g.drawCircleInLogicSpace(_pos.getX(),_pos.getY(), radius);
        }
    }

    @Override
    void handleEvent(TouchEvent e) {
        if(e.getTouchType() == InputInterface.touchType.PRESSED
        && inside(e.getPosition()))
        {
            _board.onTileClicked(this);
        }
    }

    public boolean animationPlaying() { return _animation != null;}

    public boolean inside(Position p)
    {
        int offset = _width/2;
        int minX = _pos.getX() - offset;
        int maxX = _pos.getX() + offset;
        int minY = _pos.getY() - offset;
        int maxY = _pos.getY() + offset;

        int x = p.getX();
        int y = p.getY();

        return x >= minX && x <= maxX
            && y >= minY && y <= maxY;
    }

    private static RGBColor getKindColor(Tile.Kind kind)
    {
        switch (kind){
            case UNKNOWN: return GREY;
            case TILE:    return BLUE;
            case WALL:    return RED;
        }
        return null;
    }

    public void beginTwitchAnimation()
    {
        int cycles = isNumber() ? 2 : 3;
        _animation = new TwitchAnimation(0.2f * cycles, 1.15f, cycles);
    }

    public void beginTransitionAnimation()
    {
        RGBColor currColor = getKindColor(_tile.getKind());
        RGBColor nextColor = getKindColor(_tile.getKind().next());
        _animation = new ColorAnimation(currColor, nextColor, _animationDuration);
    }
}
