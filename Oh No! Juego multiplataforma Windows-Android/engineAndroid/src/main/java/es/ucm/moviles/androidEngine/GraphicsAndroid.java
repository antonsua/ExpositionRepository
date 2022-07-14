package es.ucm.moviles.androidEngine;

import es.ucm.moviles.engineinterface.FontInterface;
import es.ucm.moviles.engineinterface.GraphicsInterface;
import es.ucm.moviles.engineinterface.ImageInterface;
import es.ucm.moviles.engineinterface.Position;
import es.ucm.moviles.engineinterface.RGBColor;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.Typeface;
import android.os.Build;
import android.view.SurfaceView;

public class GraphicsAndroid implements GraphicsInterface {
    //Atributos propios

    Context _context;
    Canvas _graphics;
    private SurfaceView _view;
    Paint _paint;
    private float _regularStrokeWidth = 5.0f;
    private float _hintsStrokeWidth = 10.0f;
    RGBColor clearColor;
    int clearColor2; // ESTO DEBE ELIMINARSE Y TRABAJAR SOLO CON CLEARCOLOR
    // Variables de escalado
    private float _relacionVentana;
    private float _relacionLogicaJuego = 0.6666667f;  // Por defecto empieza a 2:3 (400x600)
    private int _anchoLogica = 400; // Por defecto empieza a 400x600
    private int _altoLogica = 600;
    private int _mitadDistanciaVaciaVertical;
    private int _mitadDistanciaVaciaHorizontal;
    private float _factorEscaladoGeneral; // Tamaño Ventana / Tamaño Logico

    public GraphicsAndroid(SurfaceView view)
    {
        _view = view;
        _paint = new Paint();
        _paint.setColor(Color.BLUE);
        _paint.setStrokeWidth(5.0f);
    }

    public void init()
    {

    }

    /* ------------------------------------------------------------------
     *  GETTERS
     * ------------------------------------------------------------------
     */

    /**
     * Devuelve la herramienta de dibujado de android
     * @return Canvas : Instancia de la herramienta de dibujado para llamar a sus metodos.
     */
    public Canvas getGraphics()
    {
        return _graphics;
    }

    /**
     * Devuelve la instancia de la ventana
     */
    public SurfaceView getViewport()
    {
        return _view;
    }

    /**
     * Simplemente devuelve el ancho de la ventana abierta.
     * @return int tamaño en pixeles.
     */
    public int getViewportWidth() {
        return _view.getWidth();
    }

    /**
     * Simplemente devuelve el alto de la ventana abierta.
     * @return int tamaño en pixeles.
     */
    public int getViewportHeight() {
        return _view.getHeight();
    }

    /**
     * Devuelve el factor de escalado aplicado a los elementos lógicos.
     * @return float factor de escalado aplicado.
     */
    public float getCurrentScale()
    {
        return (float)_factorEscaladoGeneral;
    }

    /**
     * Devuelve el alto de las bandas blancas horizontales.
     * @return int tamaño en pixeles.
     */
    public int getWhiteBandHeight()
    {
        return _mitadDistanciaVaciaVertical;
    }

    /**
     * Devuelve el ancho de las bandas blancas verticales.
     * @return int tamaño en pixeles.
     */
    public int getWhiteBandWidth()
    {
        return _mitadDistanciaVaciaHorizontal;
    }

    /**
     * Devuelve la relación de la ventana (ancho/alto).
     * @return float con el resultado
     */
    public float getWindowAspect()
    {
        return _relacionVentana;
    }

    /**
     * Devuelve el tamaño actual de la fuente
     * @return Tamaño de punto de la fuente redondeado en un int.
     */
    public float getFontSize()
    {
        return _paint.getTextSize();
    }

    /**
     * Devuelve el paint. Usado por resources.
     * @return
     */
    public Paint getPaint()
    {
        return _paint;
    }


    /* ------------------------------
     * SETTERS
     * ------------------------------
     */

    /**
     * Establece el Context
     * @param c Context
     */
    public void setContext(Context c){ _context = c;}


    /**
     * Recibe el Canvas que usaremos.
     * @param c Canvas.
     */
    public void setGraphics(Canvas c)
    {
        _graphics = c;
    }


    /* ---------------------------------------------------------------
     * LOGICA INTERNA DE PINTADO PARA ANDROID
     * ---------------------------------------------------------------
     */

    /**
     * Metodo que dibuja las barras blancas en lo que sobra de pantalla
     *
     * Barras Horizontales (con tamaño _mitadDistanciaVaciaVertical > 0)
     *              (X1,Y1) +---------------------------------·
     *                      |             Barra1              |
     *                      ·---------------------------------+ (X2, Y2)
     *                      ·                                 ·
     *                      ·                                 ·
     *                      ·                                 ·
     *                      ·                                 ·
     *                      ·                                 ·
     *              (X1,Y1) +---------------------------------·
     *                      |             Barra2              |
     *                      ·---------------------------------+ (X2, Y2)
     *
     * Barras Verticales (con tamaño _mitadDistanciaVaciaHorizontal > 0)
     *              B1(X1,Y1)                  B2(X1,Y1)
     *                      +----·---------------------+-----·
     *                      |    |                     |     |
     *                      |    |                     |     |
     *                      | B1 |                     | B2  |
     *                      |    |                     |     |
     *                      |    |                     |     |
     *                      |    |                     |     |
     *                      ·----+---------------------·-----+
     *                           B1(X2, Y2)                  B2(X2, Y2)
     *
     * En Android los rectangulos se definen con los valores left, top, right y bottom
     *         (barra2X1, barra2Y1) +----------+
     *           left       top     |          |
     *                              |          |   right     bottom
     *                              +----------+ (barra2X2, barra2Y2)
     *
     * Llamado por: Bucle Principal en JFrame o lógica.
     */
    public void drawWhiteBounds(){
        // Pareja de Bandas blancas
        // OJO QUE EN ANDROID LOS RECTANGULOS VAN DISTINTO
        // Se manda la coordenada de los bordes izquierdo, superior, derecha, inferior
        //  (barra2X1, barra2Y1) +----------+
        //    left       top     |          |
        //                       |          |   right     bottom
        //                       +----------+ (barra2X2, barra2Y2)
        //
        //   Left       TOP       RIGHT    BOTTOM
        int barra1X1, barra1Y1, barra1X2, barra1Y2;
        int barra2X1, barra2Y1, barra2X2, barra2Y2;

        // Color de las bandas
        _paint.setColor(Color.WHITE);
        _paint.setStyle(Paint.Style.FILL);

        // Recalculo de variables usadas
        calculateScaleVars();

        // Calculo de las barras blancas:
        // Si la ventana es más ancha o más baja de lo que debería. (Relación mayor a 0.6666667f)
        // Bandas Verticales (_mitadDistanciaVaciaHorizontal > 0)
        if (_relacionVentana > _relacionLogicaJuego)
        {
            // BORDE IZQUIERDA
            //De la esquina superior izquierda
            barra1X1 = 0;
            barra1Y1 = 0;
            //A la derecha a la altura del borde LOGICO (es igual de alto que la logica)
            barra1X2 = Math.abs(_mitadDistanciaVaciaHorizontal);
            barra1Y2 = _view.getHeight();

            // BORDE DERECHA
            //De la esquina superior derecha
            barra2X1 = _view.getWidth() - Math.abs(_mitadDistanciaVaciaHorizontal); // OJO! Ver que no baje de 0.
            barra2X1 = Math.abs(barra2X1);
            barra2Y1 = 0;
            //A la derecha a la altura del borde LOGICO (es igual de alto que la logica)
            barra2X2 = _view.getWidth();
            barra2Y2 = _view.getHeight();

            // Y los mandamos pintar los rectangulos
            Rect b1 = new Rect(barra1X1,barra1Y1,barra1X2,barra1Y2);
            Rect b2 = new Rect(barra2X1,barra2Y1,barra2X2,barra2Y2);
            _graphics.drawRect(b1, _paint);
            _graphics.drawRect(b2, _paint);
        }
        // Si la ventana es más estrecha o más alta de lo que debería
        // Bandas Horizontales (_mitadDistanciaVaciaVertical > 0)
        else if (_relacionVentana < _relacionLogicaJuego)
        {
            // Ocuparemos toda la horizontal
            // Pondremos bandas blancas horizontales arriba y abajo para el espacio sobrante vertical
            // ARRIBA
            //De la esquina superior izquierda
            barra1X1 = 0;
            barra1Y1 = 0;
            //A la derecha a la altura del borde LOGICO (es igual de alto que la logica)
            barra1X2 = _view.getWidth();
            barra1Y2 = Math.abs(_mitadDistanciaVaciaVertical);
            // ABAJO
            //De debajo del juego
            barra2X1 = 0;
            barra2Y1 = _view.getHeight() - Math.abs(_mitadDistanciaVaciaVertical); // OJO! ver que no se baje de 0.
            barra2Y1 = Math.abs(barra2Y1); // Check para no irnos a negativos.
            //A la derecha a la altura del borde LOGICO (es igual de alto que la logica)
            barra2X2 = _view.getWidth();
            barra2Y2 = _view.getHeight();

            // Y los mandamos pintar los rectangulos
            // OJO QUE EN ANDROID LOS RECTANGULOS VAN DISTINTO
            // Se manda la coordenada de los bordes izquierdo, superior, derecha, inferior
            //  (barra2X1, barra2Y1) +----------+
            //    left       top     |          |
            //                       |          |   right     bottom
            //                       +----------+ (barra2X2, barra2Y2)
            Rect b1 = new Rect(barra1X1,barra1Y1,barra1X2,barra1Y2);
            Rect b2 = new Rect(barra2X1,barra2Y1,barra2X2,barra2Y2);
            _graphics.drawRect(b1, _paint);
            _graphics.drawRect(b2, _paint);
        }
        else
        {
            // Ocupamos toda la pantalla con el juego
            // No necesitamos bandas blancas
        }
    }

    /**
     * Metodo que calcula los valores de las variables internas segun el tamaño de la pantalla.
     */
    public void calculateScaleVars()
    {
        // Recalculo de relacion de aspecto
        _relacionVentana = (float)_view.getWidth()/(float)_view.getHeight();
        // Calcular constantemente la relacion de la logica del juego no tiene mucho sentido
        // Recalcular solo cuando cambiamos el tamaño de la logica del juego (ver setLogicSize())
        // _relacionLogicaJuego = (float)_anchoLogica/(float)_altoLogica;

        // Calculamos el factor de escalado
        // Lo que debemos obtener aquí es la escala manteniendo la resolución del juego 2:3, no respecto a la ventana
        // Si la ventana es más ancha de lo que debería
        if (_relacionVentana > _relacionLogicaJuego)
        {
            // Ocupamos toda la vertical y centramos en antura
            _factorEscaladoGeneral =  (float)_view.getHeight() / (float)_altoLogica;
            // Bandas Verticales con distancia sobrante horizontal
            _mitadDistanciaVaciaHorizontal = (int)((_view.getWidth() - (int)(_anchoLogica * _factorEscaladoGeneral))/(float)2.0f);
            _mitadDistanciaVaciaVertical = 0;

        }
        // Si la ventana es más alta de lo que debería
        else if (_relacionVentana < _relacionLogicaJuego)
        {
            // Ocupamos toda la anchura y centramos en antura
            _factorEscaladoGeneral = (float)_view.getWidth() / (float)_anchoLogica;
            // Bandas Horizontales con distancia sobrante vertical
            _mitadDistanciaVaciaVertical = (int)((_view.getHeight() - (int)(_altoLogica * _factorEscaladoGeneral))/(float)2.0f);
            _mitadDistanciaVaciaHorizontal = 0;
        }
        // Si tanto el juego como la ventana son 2:3 (relacion == 0.6666667f)
        else
        {
            // Ocupamos toda la pantalla con el juego
            _factorEscaladoGeneral = (float)_view.getHeight() / (float)_altoLogica; // Aqui nos vale tanto ancho como alto.
            // No son necesarias bandas
            _mitadDistanciaVaciaHorizontal = 0;
            _mitadDistanciaVaciaVertical = 0;
        }
    }

    /**
     * Aplica el escalado al tamaño de fuente
     */
    private void resizeFontFromScale()
    {
        float newSize = _paint.getTextSize();
        newSize = newSize*(float)_factorEscaladoGeneral;
        _paint.setTextSize(newSize);
    }

    /* -----------------------------------
     * METODOS HEREDADOS DE LA INTERFAZ
     * -----------------------------------
     */

    /* -----------------------------------------------
     * Metodos gestion coordenadas Logica <-> Ventana
     * -----------------------------------------------
     */

    /**
     * Dadas unas coordenadas en ventana, devuelve su equivalente lógico
     * o -1 si esta fuera de del espacio lógico.
     * @param x
     * @param y
     * @return ArrayList de dos elementos con X en posicion 0 e Y en posición 1.
     */
    @Override
    public Position translateWindowToLogic(int x, int y)
    {
        //System.out.println("GraphicsAndroid::translateWindowToLogic(x:"+x+",y:"+y+")");
        //System.out.println("Factor de escalado general: "+_factorEscaladoGeneral);
        //System.out.println("Mitad Distancia Vacia Hor : "+_mitadDistanciaVaciaHorizontal);
        //System.out.println("Mitad Distancia Vacia Ver : "+_mitadDistanciaVaciaVertical);
        // Restandole los espacios blancos, deberíamos obtener un valor
        // dentro del espacio lógico. Si es superior es que se ha hecho click fuera
        int lx = (int)((float)(x-_mitadDistanciaVaciaHorizontal)/(float)_factorEscaladoGeneral);
        int ly = (int)((float)(y-_mitadDistanciaVaciaVertical)/(float)_factorEscaladoGeneral);
        //System.out.println("lx calculado: "+lx);
        //System.out.println("ly calculado: "+ly);

        // Si alguna coordenada esta fuera del espacio lógico, establecemos ambas a -1
        if (lx > _anchoLogica || lx < 0 || ly > _altoLogica || ly < 0)
        {
            lx = -1;
            ly = -1;
        }
        Position logicCoordinates = new Position(lx, ly);
        logicCoordinates.setX(lx);
        logicCoordinates.setY(ly);
        //System.out.println("GraphicPC::Translate Window(x:"+x+",y:"+y+") -> Logic(lx:"+lx+",ly:"+ly+")");

        return logicCoordinates;
    }

    /**
     * Dadas unas coordenadas logicas, devuelve su equivalente en el espacio de la ventana.
     * @param lx
     * @param ly
     * @return ArrayList de dos elementos con X en posicion 0 e Y en posición 1.
     */
    @Override
    public Position translateLogicToWindow(int lx, int ly)
    {
        int x = (int)(lx*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)(ly*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        Position windowCoordinates = new Position(x,y);
        //System.out.println("GraphicPC::Translate Logic(lx:"+lx+",ly:"+ly+") -> Window(x:"+x+",y:"+y+")");

        return windowCoordinates;
    }

    /* -------------------------
     * SETTERS
     * -------------------------
     */

    /**
     * Cambia el color utilizado por el motor para pintar en futuras llamadas.
     * @param color RGBColor
     */
    @Override
    public void setColor(RGBColor color)
    {
        _paint.setARGB(color.getA(), color.getR(), color.getG(), color.getB());
    }

    /**
     * Metodo por si queremos variar el tamaño del espacio logico
     * NO SE USARA EN LA PRACTICA YA QUE SIEMPRE SERA 400x600
     * @param w
     * @param h
     */
    @Override
    public void setLogicSize(int w, int h) {
        _anchoLogica = w;
        _altoLogica = h;
        _relacionLogicaJuego = (float) _anchoLogica / (float) _altoLogica;
    }

    /**
     * Metodo para establecer el color de "limpiado"
     * @param c RGBColor
     */
    @Override
    public void setClearColor(RGBColor c) {
        clearColor = c;
    }

    /**
     * Metodo para establecer el color de "limpiado"
     * con un entero desde el motor de Android
     * @param r int
     * @param g int
     * @param b int
     */
    public void setClearColor(int r, int g, int b)
    {
        clearColor = new RGBColor(r,g,b);
    }

    /**
     * Establece la fuente actual con al que pintar texto.
     * @param f Fuente a utilizar
     */
    @Override
    public void setFont(FontInterface f)
    {
        if (f != null)
        {
            FontAndroid fAnd = (FontAndroid)f;
            _paint.setTypeface(fAnd.getFont());
            //setFontSize(f.getSize());
        }
    }

    public void setFont(String f)
    {
        if (f == "Serif")
        {
            _paint.setTypeface(Typeface.SERIF);
        }
        else if (f == "SansSerif")
        {
            _paint.setTypeface(Typeface.SANS_SERIF);
        }
        else if (f == "DefaultBold")
        {
            _paint.setTypeface(Typeface.DEFAULT_BOLD);
        }
        else
        {
            _paint.setTypeface(Typeface.DEFAULT);
        }
    }

    /**
     * Restablece la fuente a la predeterminada por typeface.
     */
    @Override
    public void resetFont()
    {
        _paint.setTypeface(Typeface.DEFAULT);
    }

    @Override
    public int GetWidth() {
        return _view.getWidth();
    }

    @Override
    public int GetHeight() {
        return _view.getHeight();
    }

    /**
     * Permite cambiar el tamaño de la fuente usada actualmetente
     * @param fs float nuevo tamaño de la fuente.
     */
    @Override
    public void setFontSize(float fs)
    {
        float size = fs * _factorEscaladoGeneral;
        _paint.setTextSize(size);
    }

    /* ----------------------------------------
     * METODOS DE MANIPULACION DEL CANVAS
     * ----------------------------------------
     */
    /**
     * Mueve la matriz de dibujado
     * @param x double movimiento en el eje X
     * @param y double movimiento en el eje Y
     */
    @Override
    public void translateCanvas(double x, double y) {
        float xTranslate = (float) (x*_factorEscaladoGeneral+_mitadDistanciaVaciaHorizontal);
        float yTranslate = (float) (y*_factorEscaladoGeneral+_mitadDistanciaVaciaVertical);
        _graphics.translate(xTranslate,yTranslate);
    }

    /**
     * Rota la matriz de dibujado
     * Recibe una cantidad de grados y lo pasa a radiantes para llamar al metodo de graphics
     * @param degrees Cuantos grados queremos que gire.
     */
    @Override
    public void rotateCanvas(float degrees)
    {
        _graphics.rotate(degrees);
    }

    /**
     * Escala la matriz de dibujado
     * Recibe una cantidad de grados y lo pasa a radiantes para llamar al metodo de graphics
     * @param x float escalado del eje X
     * @param y float escalado del eje Y
     */
    @Override
    public void scaleCanvas(float x, float y)
    {
        _graphics.scale( x*_factorEscaladoGeneral,y*_factorEscaladoGeneral);
    }

    /**
     * Guarda el estado de la matriz de dibujado
     */
    @Override
    public void saveCanvas()
    {
        _graphics.save();
    }

    /**
     * Carga un estado previo de la matrix de dibujado
     * que fuera almacenado en una variable interna con el metodo saveCanvas
     */
    @Override
    public void restoreCanvas()
    {
        _graphics.restore();
    }

    /* ----------------------------------------
     * METODOS DE PINTADO DE FIGURAS E IMAGENES
     * -----------------------------------------
     */

    /**
     * Limpia la pantalla utilizando el color de limpiado establecido en el motor
     * Principalmente llamado por el motor antes de pintar cada frame.
     * Pero damos opcion a la lógica de llamarlo si fuese necesario.
     */
    @Override
    public void clear()
    {
        // API LVL 26
        //Color c = Color.valueOf(clearColor.getR(), clearColor.getG(), clearColor.getB(), clearColor.getA());
        _graphics.drawColor(Color.rgb(clearColor.getR(), clearColor.getG(), clearColor.getB()));
    }

    /**
     * Metodo de pintado de una imagen
     * @param image : Imagen a pintar
     * @param x : Posición X dentro del espacio de ventana
     * @param y : Posición Y dentro del espacio de ventana
     */
    @Override
    public void drawImage(ImageInterface image, int x, int y)
    {
        ImageAndroid iAnd = (ImageAndroid) image;
        Bitmap bmImg = iAnd.getBitmapImage();
        _graphics.drawBitmap(bmImg, x, y, _paint);
    }

    /**
     * Metodo de pintado de una imagen con el tamaño dado.
     * Puede pintarse fuera del espacio logico.
     * @param image : Imagen a pintar
     * @param x: Posición X dentro del espacio de ventana
     * @param y : Posición Y dentro del espacio de ventana
     */
    @Override
    public void drawImage(ImageInterface image, int x, int y, int w, int h)
    {
        ImageAndroid iAnd = (ImageAndroid) image;
        Bitmap bmImg = iAnd.getBitmapImage();
        Bitmap resizedBitmap = Bitmap.createScaledBitmap(bmImg,w,h,false);

        _graphics.drawBitmap(resizedBitmap,x,y,_paint);
    }

    /**
     * Metodo de pintado de una imagen dentro del espacio logico
     * Se ajustará cuando cambie el tamaño de ventana y se escalara con ella.
     * @param image : Imagen a pintar
     * @param xLogico : Posición X dentro del espacio de ventana
     * @param yLogico : Posición Y dentro del espacio de ventana
     */
    @Override
    public void drawImageInLogicSpace(ImageInterface image, int xLogico, int yLogico)
    {
        //Obtenemos la imagen
        ImageAndroid imgPC = (ImageAndroid) image;
        Bitmap bmImg = imgPC.getBitmapImage();

        // Check por si esta vacía
        if (bmImg == null)
        {
            System.err.println("GraphicsAndroid::drawImage() ERROR - La imagen que se ha solicitado pintar esta vacia (null)");
            return;
        }

        // Conversión posición Logica a Ventana y escalado
        int x = (int)(xLogico*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)(yLogico*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int w = (int)(bmImg.getWidth()*_factorEscaladoGeneral);
        int h = (int)(bmImg.getHeight()*_factorEscaladoGeneral);

        Bitmap resizedBitmap = Bitmap.createScaledBitmap(bmImg,w,h,false);

        // Pintamos la imagen.
        // Bitmap, left, top, paint
        _graphics.drawBitmap(resizedBitmap, x, y, _paint);
    }

    /**
     * Pinta la imagen, con el tamaño indicado
     * Se ajustará cuando cambie el tamaño de ventana y se escalara con ella.
     * @param image : Imagen a pintar
     * @param xLogico : Posición X dentro del espacio de ventana
     * @param yLogico : Posición Y dentro del espacio de ventana
     * @param logicImgWidth : Ancho a ocupar dentro de las coordenaas logicas
     * @param logicImgHeight : Alto a ocupar dentro de las coordenadas logicas
     */
    @Override
    public void drawImageInLogicSpace(ImageInterface image, int xLogico, int yLogico, int logicImgWidth, int logicImgHeight) {

        ImageAndroid andImg = (ImageAndroid) image;
        Bitmap bmImg = andImg.getBitmapImage();

        if(bmImg == null)
        {
            System.err.println("GraphicsAndroid::drawImage() ERROR - La imagen que se ha solicitado pintar esta vacia (null)");
            return;
        }
        int x = (int)(xLogico*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)(yLogico*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int w = (int)(logicImgWidth*_factorEscaladoGeneral);
        int h = (int)(logicImgHeight*_factorEscaladoGeneral);

        Bitmap resizedBitmap = Bitmap.createScaledBitmap(bmImg,w,h,false);

        _graphics.drawBitmap(resizedBitmap,x,y,_paint);
    }

    /**
     * Dibuja una línea recta entre dos puntos (x1,y1) y (x2,y2) del espacio de ventana
     *       (x1,y1) · ------------------------- · (x2,y2)
     * @param x1 Coordenada X del primer punto
     * @param y1 Coordenada Y del primer punto
     * @param x2 Coordenada X del segundo punto
     * @param y2 Coordenada Y del segundo punto
     */
    @Override
    public void drawLine(int x1, int y1, int x2, int y2)
    {
        _paint.setStyle(Paint.Style.FILL_AND_STROKE);
        _graphics.drawLine(x1, y1, x2, y2, _paint);
    }

    /**
     * Dibuja una línea recta entre dos puntos (lx1,ly1) y (lx2,ly2) del espacio logico
     *       (lx1,ly1) · ------------------------- · (lx2,ly2)
     * @param lx1 Coordenada X del primer punto en el espacio logico
     * @param ly1 Coordenada Y del primer punto en el espacio logico
     * @param lx2 Coordenada X del segundo punto en el espacio logico
     * @param ly2 Coordenada Y del segundo punto en el espacio logico
     */
    @Override
    public void drawLineInLogicSpace(int lx1, int ly1, int lx2, int ly2)
    {
        // Conversión posición Logica a Ventana
        int x1 = (int)(lx1*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y1 = (int)(ly1*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int x2 = (int)(lx2*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y2 = (int)(ly2*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        _paint.setStyle(Paint.Style.STROKE);
        _graphics.drawLine(x1, y1, x2, y2, _paint);
    }

    /**
     * Dibuja un cuadrado a partir de dos puntos (x1,y1) con un ancho y alto dado
     *    (x, y) +------·
     *           |      |
     *           |      |
     *           ·------+ (x+w, y+h)
     * @param x Posicion X del primer punto
     * @param y Posicion Y del primer punto
     * @param w  Ancho del rectangulo
     * @param h  Alto del rectanguloPosicion Y del segundo punto
     */
    @Override
    public void drawRect(int x, int y, int w, int h)
    {
        Rect r = new Rect(x, y, x+w, y+h);
        _paint.setStyle(Paint.Style.STROKE);
        _graphics.drawRect(r, _paint);
    }

    /**
     * Dibuja un cuadrado a partir de dos puntos (x1,y1) con un ancho y alto dado
     *  (x1, y1) +------·
     *           |      |
     *           |      |
     *           ·------+ (x2, y2)
     * @param lx Posicion X del primer punto dentro de las coordenadas logicas
     * @param ly Posicion Y del primer punto dentro de las coordenadas logicas
     * @param lw  Ancho del rectangulo dentro de las coordenadas logicas
     * @param lh  Alto del rectanguloPosicion Y del segundo punto dentro de las coordenadas logicas
     */
    @Override
    public void drawRectInLogicSpace(int lx, int ly, int lw, int lh)
    {
        int left = (int)(lx*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int top = (int)(ly*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int right = (int)((lx+lw)*_factorEscaladoGeneral + _mitadDistanciaVaciaHorizontal);
        int bottom = (int)((ly+lh)*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;

        _paint.setStyle(Paint.Style.STROKE);
        Rect r = new Rect(left, top, right, bottom);
        _graphics.drawRect(r, _paint);
    }

    /**
     * Rellena de color un cuadrado a partir de dos puntos (x1,y1) con un ancho y alto dado
     *    (x, y) +------·
     *           |      |
     *           |      |
     *           ·------+ (x+w, y+h)
     * @param x Posicion X del primer punto
     * @param y Posicion Y del primer punto
     * @param w  Ancho del rectangulo
     * @param h  Alto del rectanguloPosicion Y del segundo punto
     */
    @Override
    public void fillRect(int x, int y, int w, int h)
    {
        _paint.setStyle(Paint.Style.FILL);
        Rect r = new Rect(x, y, x+w, y+h);
        _graphics.drawRect(r, _paint);
    }

    /**
     * Rellena de color un cuadrado a partir de dos puntos (x1,y1) con un ancho y alto dado
     *    (x, y) +------·
     *           |      |
     *           |      |
     *           ·------+ (x+w, y+h)
     * @param lx Posicion X del primer punto dentro de las coordenadas logicas
     * @param ly Posicion Y del primer punto dentro de las coordenadas logicas
     * @param lw  Ancho del rectangulo dentro de las coordenadas logicas
     * @param lh  Alto del rectanguloPosicion Y del segundo punto dentro de las coordenadas logicas
     */
    @Override
    public void fillRectInLogicSpace(int lx, int ly, int lw, int lh)
    {
        int left = (int)(lx*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int top = (int)(ly*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int right = (int)((lx+lw)*_factorEscaladoGeneral + _mitadDistanciaVaciaHorizontal);
        int bottom = (int)((ly+lh)*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;

        _paint.setStyle(Paint.Style.FILL);
        Rect r = new Rect(left, top, right, bottom);
        _graphics.drawRect(r, _paint);
    }

    /**
     * Metodo simple para dibujar el contorno de un circulo dentro del espacio de ventana.
     * OJO! Se pasa la posición de la esquina superior derecha
     * pero en android el metodo drawCircle pinta desde el centro del círculo
     * Por ello se añade el radio en el eje x e y antes de pintar, para que se ajuste la
     * posición dada con la deseada.
     * @param x posicion en el eje x
     * @param y posicion en el eje y
     * @param radius tamaño del circulo en pixeles (relativo al tamaño de ventana)
     */
    @Override
    public void drawCircle(int x, int y, int radius)
    {
        // Pintamos el circulo.
        _paint.setStyle(Paint.Style.STROKE);
        _graphics.drawCircle(x, y, radius, _paint);
    }

    /**
     * Dibuja el contorno de un circulo en el espacio lógico
     * Se aportan la posición (x,y) del centro del circulo en coordenadas logicas y el radio logico.
     * @param lcx : Coordenada X del punto central del círculo dentro del espacio logico.
     * @param lcy : Coordenada Y del punto central del círculo dentro del espacio logico.
     * @param lr : Radio del circulo
     */
    @Override
    public void drawCircleInLogicSpace(int lcx, int lcy, int lr)
    {
        // Conversión Logico a Ventana
        int x = (int)(lcx*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)(lcy*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int radio = (int)((float)lr * _factorEscaladoGeneral);

        // Pintamos el circulo.
        _paint.setStrokeWidth(_hintsStrokeWidth);
        _paint.setStyle(Paint.Style.STROKE);
        _graphics.drawCircle(x, y, radio, _paint);
        _paint.setStrokeWidth(_regularStrokeWidth);
    }

    /**
     * Dibuja el contorno de un ovalo en el espacio de ventana.
     * El ovalo se pinta definiendo un punto que representa el centro de este
     * y a partir del cual se extiende un espacio que lo contendrá, dandole el ancho y alto.
     * @param cx Coordenada X del centro del ovalo.
     * @param cy Coordenada Y del centro del ovalo.
     * @param w ancho del ovalo.
     * @param h alto del ovalo.
     */
    @Override
    public void drawOval(int cx, int cy, int w, int h)
    {
        // Obtenemos los puntos left/right/top/bottom
        int left = cx-w;
        int right = cx+w;
        int top = cy+h;
        int bottom = cy-h;

        // Pintamos el ovalo.
        // API LVL 21
        _paint.setStyle(Paint.Style.STROKE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            _graphics.drawOval(left, top, right, bottom,_paint);
        }
        else
        {
            RectF r = new RectF(left,top,right,bottom);
            _graphics.drawOval(r, _paint);
        }

    }

    /**
     * Dibuja el contorno de un ovalo en el espacio logico.
     * El ovalo se pinta definiendo un punto que representa el centro de este
     * y a partir del cual se extiende un espacio que lo contendrá, dandole el ancho y alto.
     * @param lcx Coordenada X del centro del ovalo en espacio logico.
     * @param lcy Coordenada Y del centro del ovalo en espacio logico.
     * @param lw ancho logico del ovalo.
     * @param lh alto logico del ovalo.
     */
    @Override
    public void drawOvalInLogicSpace(int lcx, int lcy, int lw, int lh)
    {
        // Obtenemos los puntos left/right/top/bottom
        int logicLeft = lcx-lw;
        int logicRight = lcx+lw;
        int logicTop = lcy+lh;
        int logicBottom = lcy-lh;

        // Conversión Logico a Ventana
        int left = (int)(logicLeft*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int top = (int)(logicTop*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int right = (int)((float)logicRight * _factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int bottom = (int)((float)logicBottom * _factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;

        // Pintamos el ovalo.
        // API LVL 21
        _paint.setStyle(Paint.Style.STROKE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            _graphics.drawOval(left, top, right, bottom,_paint);
        }
        else
        {
            RectF r = new RectF(left,top,right,bottom);
            _graphics.drawOval(r, _paint);
        }
    }

    /**
     * Rellena de color un circulo en la posición (lcx, lcy) del espacio de ventana
     * @param cx Coordenada X del centro del circulo
     * @param cy Coordenada Y del centro del circulo
     * @param radius radio del circulo.
     */
    @Override
    public void fillCircle(int cx, int cy, int radius) {
        // Pintamos el circulo.
        _paint.setStyle(Paint.Style.FILL);
        // Draw circle utiliza el centro del circulo.
        _graphics.drawCircle(cx, cy, radius/2, _paint);
        _paint.setStyle(Paint.Style.STROKE);
    }

    /**
     * Rellena de color un circulo en la posición (lcx, lcy) del espacio logico con el radio indicado
     * El circulo escalara con la ventana.
     * @param lcx Coordenada X del centro del circulo en el espacio logico
     * @param lcy Coordenada Y del centro del circulo en el espacio logico
     * @param lr radio logico del circulo.
     */
    @Override
    public void fillCircleInLogicSpace(int lcx, int lcy, int lr)
    {
        // Conversión Logico a Ventana
        int x = (int)((lcx)*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)((lcy)*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int radio = (int)((float)lr * _factorEscaladoGeneral);

        // Pintamos el circulo.
        _paint.setStyle(Paint.Style.FILL_AND_STROKE);
        _paint.setStrokeWidth(5f);
        _graphics.drawCircle(x, y, radio, _paint);
        _paint.setStyle(Paint.Style.STROKE);
    }

    /**
     * Rellena de color un ovalo en el espacio de ventana.
     * El ovalo se pinta definiendo un punto que representa el centro de este
     * y a partir del cual se extiende un espacio que lo contendrá, dandole el ancho y alto.
     * @param cx Coordenada X del centro del circulo.
     * @param cy Coordenada Y del centro del circulo.
     * @param w ancho del ovalo.
     * @param h alto del ovalo.
     */
    @Override
    public void fillOval(int cx, int cy, int w, int h)
    {
        // Obtenemos los puntos left/right/top/bottom
        int left = cx-w;
        int right = cx+w;
        int top = cy+h;
        int bottom = cy-h;

        // Pintamos el ovalo.
        // API LVL 21
        _paint.setStyle(Paint.Style.FILL);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            _graphics.drawOval(left, top, right, bottom,_paint);
        }
        else
        {
            RectF r = new RectF(left,top,right,bottom);
            _graphics.drawOval(r, _paint);
        }
    }

    /**
     * Rellena de color un ovalo en el espacio logico.
     * El ovalo se pinta definiendo un punto que representa el centro de este
     * y a partir del cual se extiende un espacio que lo contendrá, dandole el ancho y alto.
     * @param lcx Coordenada X del centro del ovalo en espacio logico.
     * @param lcy Coordenada Y del centro del ovalo en espacio logico.
     * @param lw ancho logico del ovalo.
     * @param lh alto logico del ovalo.
     */
    @Override
    public void fillOvalInLogicSpace(int lcx, int lcy, int lw, int lh)
    {
        // Obtenemos los puntos left/right/top/bottom
        int logicLeft = lcx-lw;
        int logicRight = lcx+lw;
        int logicTop = lcy+lh;
        int logicBottom = lcy-lh;

        // Conversión Logico a Ventana
        int left = (int)(logicLeft*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int top = (int)(logicTop*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int right = (int)((float)logicRight * _factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int bottom = (int)((float)logicBottom * _factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;

        // Pintamos el ovalo.
        // API LVL 21
        _paint.setStyle(Paint.Style.FILL);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            _graphics.drawOval(left, top, right, bottom,_paint);
        }
        else
        {
            RectF r = new RectF(left,top,right,bottom);
            _graphics.drawOval(r, _paint);
        }
    }

    /* ---------------------------------
     * METODOS DE PINTADO DE TEXTO
     * ---------------------------------
     */

    /**
     * Metodo simple para pintar un texto en cualquier espacio de la ventana
     * @param text : String de texto
     * @param x : posicion x de la ventana
     * @param y : posicion y de la ventana
     */
    @Override
    public void drawText(String text, int x, int y)
    {
        _paint.setStyle(Paint.Style.FILL);
        _graphics.drawText(text,x,y,_paint);
    }

    /**
     * Metodo simple para pintar un texto en cualquier espacio de la ventana
     * RECOMENDACION: NO USAR ESTE METODO EN ANDROID, CAMBIAR FUENTE Y USAR NORMAL.
     * ANDROID SE ENCARGA DE MANTENER EL ASPECTO DE LA FUENTE A PESAR DEL TAMAÑO DE
     * LA VENTANA.
     * El escalado no funciona muy alla en android pero este metodo no deberíamos usarlo.
     * @param text : String de texto
     * @param x : posicion x de la ventana
     * @param y : posicion y de la ventana
     * @param applyScale : Boolean para determinar si el escalado logico afecta al texto.
     */
    @Override
    public void drawTextScalable(String text, int x, int y, boolean applyScale)
    {
        if(applyScale) resizeFontFromScale();
        _paint.setStyle(Paint.Style.FILL);
        _graphics.drawText(text,x,y,_paint);
    }

    /**
     * Metodo simple para pintar un texto dentro del espacio logico de juego
     * @param text : String de texto
     * @param xLogico : posicion x de la ventana
     * @param yLogico : posicion y de la ventana
     * @param applyScale : Boolean para determinar si el escalado logico afecta al texto.
     */
    @Override
    public void drawTextInLogicSpace(String text, int xLogico, int yLogico, boolean applyScale)
    {
        // Android se encarga el solo de mantener la apariencia segun el tamaño de la ventana
        // No hace falta llamar al resize. Es ignorado en esta implementacion.
        //if (applyScale) resizeFontFromScale();

        // Conversion de coordenadas logicas a espacio de ventana
        // Conversión Logico a Ventana
        int x = (int)(xLogico*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)(yLogico*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        _paint.setStyle(Paint.Style.FILL);
        _graphics.drawText(text,x,y,_paint);
    }

    /**
     * Metodo de pintado de una pantalla de ejemplo.
     */
    @Override
    public void drawExample() {
        //System.out.println("GraphicsPC::drawExample()");
        int w = getViewportWidth();
        int h = getViewportHeight();
        float s = getCurrentScale();
        int mitadDistVert = getWhiteBandHeight();
        int mitadDistHori = getWhiteBandWidth();
        float winAspect = getWindowAspect();

        RGBColor Black = new RGBColor(0,0,0);
        RGBColor Red = new RGBColor(255, 0, 0);
        RGBColor Blue = new RGBColor(0, 0, 255);
        RGBColor White = new RGBColor(255,255,255);
        RGBColor Yellow = new RGBColor(255, 255,0);

        // Window Info
        setColor(Black);
        _paint.setStyle(Paint.Style.FILL_AND_STROKE);
        setFontSize(20f);
        String message = "Ventana: (ancho: " + String.valueOf(w) + ", alto: " + String.valueOf(h) + ")";
        drawText(message, (int)(30*_factorEscaladoGeneral), (int)(50*_factorEscaladoGeneral));
        message = "Aspect: " + String.valueOf(winAspect);
        drawText(message, (int)(30*_factorEscaladoGeneral), (int)(70*_factorEscaladoGeneral));
        // Escala
        message = "Escalado lógico: " + String.valueOf(s);
        drawText(message, (int)(30*_factorEscaladoGeneral), (int)(90*_factorEscaladoGeneral));
        // Bandas blancas
        setColor(Black);
        message = "Alto Banda Horizontal: " + String.valueOf(mitadDistVert);
        drawText(message, (int)(30*_factorEscaladoGeneral), (int)(110*_factorEscaladoGeneral));
        message = "Ancho Banda Vertical: " + String.valueOf(mitadDistHori);
        drawText(message, (int)(30*_factorEscaladoGeneral), (int)(130*_factorEscaladoGeneral));
        // Texto del tamaño de tablero
        float fontSize = 32f;
        setColor(Black);
        int textOffset = (int)(fontSize/2.0f); //Offset respecto a su tamaño para centrarlo
        setFontSize(fontSize);
        drawTextInLogicSpace("3x3", 190-textOffset, 100+textOffset, true);
    }


}
