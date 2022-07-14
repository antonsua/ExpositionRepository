package es.ucm.moviles.logica;

import es.ucm.moviles.engineinterface.RGBColor;

public abstract class Animation
{
    private final float _duration;
    private float _time;
    private float t;

    public Animation(float duration)
    {
        _duration = duration;
        _time = 0;
        t = 0;
    }

    public void update(float deltaTime)
    {
        _time += deltaTime;
        t = _time / _duration;
        if(t > 1.f) t = 1.f;
    }

    public float getDuration()   { return _duration;}
    public float getTime()       { return  _time;}
    public float getCompleteness()
    {
        return t;
    }
    public boolean hasEnded()
    {
        return getCompleteness() >= 1.f;
    }


}
