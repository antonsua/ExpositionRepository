package es.ucm.moviles.logica;

import es.ucm.moviles.engineinterface.GraphicsInterface;
import es.ucm.moviles.engineinterface.Position;
import es.ucm.moviles.engineinterface.RGBColor;

public class TransitionScreen extends GameObject {
    protected Position _position;
    protected int _width;
    protected int _height;
    float _duration;
    private Animation _animation;
    RGBColor _color;
    boolean hasEnded;


    public void Init(Position p, int w, int h){
        _position = new Position();
        _position.setY(p.getY()); _position.setX(p.getX());
        _width = w; _height = h;
        _duration = 30f;
        _animation = null;
        _color = RGBColor.WHITE;
        hasEnded = false;
    }

    public void StartFadeOutAnim(){
        _animation = new FadeOutAnimation(_color,_duration);
        hasEnded = false;
    }
    public void StartFadeInAnim(){
        _animation = new FadeInAnimation(_color,_duration);
        hasEnded = false;
    }

    @Override
    void update(float deltaTime) {
        if(_animation != null){
            _animation.update(deltaTime);
            if(_animation.hasEnded()) {
                _animation = null;
                hasEnded = true;
            }
        }
    }

    @Override
    void render(GraphicsInterface g) {
        super.render(g);
        g.setColor(_color);
        g.drawRect(_position.getX(),_position.getY(),_width,_height);
    }
    public boolean TransitionHasEnded(){ return hasEnded;}
}
