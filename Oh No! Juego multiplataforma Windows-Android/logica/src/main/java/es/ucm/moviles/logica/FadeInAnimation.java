package es.ucm.moviles.logica;

import es.ucm.moviles.engineinterface.RGBColor;

public class FadeInAnimation extends ColorAnimation
{
    public FadeInAnimation(RGBColor color, float duration)
    {
        super(new RGBColor(color.getR(), color.getG(), color.getB(), 0), color, duration);
    }
}
