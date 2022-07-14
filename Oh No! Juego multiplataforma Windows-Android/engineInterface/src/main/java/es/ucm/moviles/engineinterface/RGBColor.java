package es.ucm.moviles.engineinterface;


/**
 * Clase intermedia para trasladar colores usando el formato
 * RGB (0-255)
 */
public class RGBColor {
    int _r;
    int _g;
    int _b;
    int _a;

    /**
     * Constructora en la que se dan los valores RGB
     * El alpha será puesto al maximo.
     * @param r componente roja [0, 255]
     * @param g componente verde [0, 255]
     * @param b componente azul [0, 255]
     */
    public RGBColor(int r, int g, int b)
    {
        this(r, g, b, 255);
    }
    /**
     * Constructora en la que se dan los valores RGB
     * El alpha será puesto al maximo.
     * @param r componente roja  [0.0, 1.0]
     * @param g componente verde [0.0, 1.0]
     * @param b componente azul  [0.0, 1.0]
     */
    public RGBColor(float r, float g, float b)
    {
        this(r, g, b, 1.0f);
    }

    /**
     * Constructora en la que se dan los valores RGBA
     * @param r Componente roja [0, 255]
     * @param g Componente verde [0, 255]
     * @param b Componente blue [0, 255]
     * @param a Componente alfa [0, 255]
     */
    public RGBColor(int r, int g, int b, int a)
    {
        // Establecemos los valores internos,
        // asegurando que estén en el rango válido [0, 255]
        _r = clamp(r);
        _g = clamp(g);
        _b = clamp(b);
        _a = clamp(a);
    }
    /**
     * Constructora en la que se dan los valores RGBA
     * @param r Componente roja  [0.0, 1.0]
     * @param g Componente verde [0.0, 1.0]
     * @param b Componente blue  [0.0, 1.0]
     * @param a Componente alfa  [0.0, 1.0]
     */
    public RGBColor(float r, float g, float b, float a)
    {
        // Establecemos los valores internos,
        // asegurando que estén en el rango válido [0.0, 1.0]
        _r = (int)Math.floor(255 * clamp(r));
        _g = (int)Math.floor(255 * clamp(g));
        _b = (int)Math.floor(255 * clamp(b));
        _a = (int)Math.floor(255 * clamp(a));
    }

    public RGBColor(RGBColor other)
    {
        this._r = other._r;
        this._b = other._b;
        this._g = other._g;
        this._a = other._a;
    }

    private static int clamp(int v)
    {
        return Math.max(0, Math.min(v, 255));
    }
    private static float clamp(float v)
    {
        return Math.max(0.0f, Math.min(v, 1.0f));
    }

    /* -----------------------------
     * Getters
     * -----------------------------
     */

    /**
     * Devuelve la componente roja del color.
     * @return int en el rango[0, 255]
     */
    public int getR(){return _r;}

    /**
     * Devuelve la componente verde del color.
     * @return int en el rango[0, 255]
     */
    public int getG() {return _g;}

    /**
     * Devuelve la componente azul del color.
     * @return int en el rango[0, 255]
     */
    public int getB() { return _b; }

    /**
     * Devuelve la compoenente alfa del color
     * @return int en el rango[0, 255]
     */
    public int getA() { return _a; }


    public void setR(int value) { _r = clamp(value);}
    public void setG(int value) { _g = clamp(value);}
    public void setB(int value) { _b = clamp(value);}
    public void setA(int value) { _a = clamp(value);}

    public void setR(float value) { _r = (int) Math.floor(255.f * clamp(value));}
    public void setG(float value) { _g = (int) Math.floor(255.f * clamp(value));}
    public void setB(float value) { _b = (int) Math.floor(255.f * clamp(value));}
    public void setA(float value) { _a = (int) Math.floor(255.f * clamp(value));}

    public int toInt32()
    {
        return  (_r << 8*3)|
                (_g << 8*2)|
                (_b << 8*1)|
                (_a << 8*0);
    }

    public static RGBColor fromInt32(int color)
    {
        int r = (color & (0xff << 8*3)) >> 8*3;
        int g = (color & (0xff << 8*2)) >> 8*2;
        int b = (color & (0xff << 8*1)) >> 8*1;
        int a = (color & (0xff << 8*0)) >> 8*0;
        return new RGBColor(r, g, b, a);
    }


    public static RGBColor lerp(RGBColor a, RGBColor b, float t)
    {
        float ar = (float)a.getR() / 255.f;
        float ag = (float)a.getG() / 255.f;
        float ab = (float)a.getB() / 255.f;
        float aa = (float)a.getA() / 255.f;

        float br = (float)b.getR() / 255.f;
        float bg = (float)b.getG() / 255.f;
        float bb = (float)b.getB() / 255.f;
        float ba = (float)b.getA() / 255.f;

        return new RGBColor
        (
            ar + (br - ar) * t,
            ag + (bg - ag) * t,
            ab + (bb - ab) * t,
            aa + (ba - aa) * t
        );
    }

    @Override
    public String toString() {
        return String.format("#%02X%02X%02X%02X", _r, _g,_b,_a);
    }

    public static final RGBColor TRANSPARENT = new RGBColor(0,0,0,0);
    public static final RGBColor BLACK   = new RGBColor(0, 0, 0);
    public static final RGBColor WHITE   = new RGBColor(255, 255, 255);
    public static final RGBColor RED     = new RGBColor(255, 0, 0);
    public static final RGBColor GREEN   = new RGBColor(0, 255, 0);
    public static final RGBColor BLUE    = new RGBColor(0, 0, 255);
    public static final RGBColor YELLOW  = new RGBColor(255, 255, 0);
    public static final RGBColor CYAN    = new RGBColor(0, 255, 255);
    public static final RGBColor MAGENTA = new RGBColor(255, 0, 255);
}
