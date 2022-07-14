package es.ucm.moviles.logica;

import es.ucm.moviles.engineinterface.RGBColor;

public class FadeOutAnimation extends ColorAnimation
{
    public FadeOutAnimation(RGBColor color, float duration) {
        super(color, new RGBColor(color.getR(), color.getG(), color.getB(), 0), duration);
    }
}
