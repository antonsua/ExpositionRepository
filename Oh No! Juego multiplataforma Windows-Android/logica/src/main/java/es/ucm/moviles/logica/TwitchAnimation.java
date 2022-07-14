package es.ucm.moviles.logica;

public class TwitchAnimation extends ScaleAnimation
{
    protected final float _maxScale;
    protected final int cycles;
    public TwitchAnimation(float duration, float maxScale) { this(duration, maxScale, 1);}
    public TwitchAnimation(float duration, float maxScale, int cycles) {
        super(duration);
        this.cycles = cycles;
        _maxScale = maxScale;
    }

    @Override
    public float getScale()
    {
        float t = getCompleteness();
        float tc = 1 / (float)cycles;
        float p = t / tc;
        float pi = (int)p;
        t = p - pi;

        if(t < 0.5)
        {
            t *= 2.0; // [0, 0.5) -> [0, 1]
            return lerp(1.f, _maxScale, t);
        }
        //decrece
        else
        {
            t -= 0.5; // [0.5, 1.0] -> [0, 0.5]
            t *= 2.0; // [0, 0.5) -> [0, 1]
            return lerp(_maxScale, 1.f, t);
        }
    }
}
