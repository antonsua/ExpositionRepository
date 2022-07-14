package es.ucm.moviles.logica;

public abstract class ScaleAnimation extends Animation
{
    public ScaleAnimation(float duration) {
        super(duration);
    }

    public abstract float getScale();

    protected float lerp(float a, float b, float t)
    {
        return a + (b - a) * t;
    }
}
