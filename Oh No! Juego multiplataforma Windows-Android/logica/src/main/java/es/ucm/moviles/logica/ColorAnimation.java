package es.ucm.moviles.logica;

import es.ucm.moviles.engineinterface.RGBColor;


public class ColorAnimation extends Animation
{
    protected final RGBColor _startColor;
    protected final RGBColor _endColor;

    public ColorAnimation(RGBColor startColor, RGBColor endColor, float duration) {
        super(duration);
        _startColor = startColor;
        _endColor = endColor;
    }

    public RGBColor getColor() {
        return RGBColor.lerp(_startColor, _endColor, getCompleteness());
    }
}
