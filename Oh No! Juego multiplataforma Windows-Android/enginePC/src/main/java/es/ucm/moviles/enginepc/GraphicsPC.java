package es.ucm.moviles.enginepc;

// Ventana
import javax.swing.JFrame;

// Imports del gestor de buffer y motor de pintado.
import java.awt.Font;
import java.awt.image.BufferStrategy; // Gestor de Buffers
import java.awt.Graphics2D; //herramienta que dibuja graficos 2D en Java.

// Herramientas del Graphics
import java.awt.BasicStroke; // Tipo de Pincel
import java.awt.Color;  // Colores
import java.awt.Stroke; // Pincel
import java.awt.geom.AffineTransform; // Matriz de transformación para girar la zona de dibujado de forma lógica.
import java.awt.image.BufferedImage;

import es.ucm.moviles.engineinterface.FontInterface;
import es.ucm.moviles.engineinterface.GraphicsInterface;
import es.ucm.moviles.engineinterface.ImageInterface;
import es.ucm.moviles.engineinterface.Position;
import es.ucm.moviles.engineinterface.RGBColor;

/**
 *  Clase que se encarga del dibujado en la ventana del PC.
 *  Contiene todos los métodos de pintado
 */
public class GraphicsPC implements GraphicsInterface
{
    // Variables de clase
    private JFrame _viewport; // Ventana
    private BufferStrategy _bufferStrat; // Gestor de buffers de java.
    private Graphics2D _graphics2D; //herramienta que dibuja graficos 2D en Java.
    private Stroke _pincel; // Herramienta para determinar el estilo de pintado
    private AffineTransform _savedMatrix; // Matriz de dibujado (para rotar y demas)

    // Variables de escalado
    private float _relacionVentana;
    private float _relacionLogicaJuego = 0.6666667f;  // 2:3 (400x600)
    private int _anchoLogica = 400;
    private int _altoLogica = 600;
    private int _mitadDistanciaVaciaVertical;
    private int _mitadDistanciaVaciaHorizontal;
    private double _factorEscaladoGeneral;        // Tamaño Ventana / Tamaño Logico

    // Configuración de pintado
    private Color _clearColor;
    private Font _originalFont;

    /**
     * Metodo constructora de nuestro graphics PC
     * @param v : Recibe un JFrame
     */
    public GraphicsPC(JFrame v)
    {
        _viewport = v;
    }

    /**
     * Init genera el Buffer Strategy con 2 buffers
     * @return true si genera el strat, false en caso de exception
     */
    public boolean init()
    {
        //System.out.println("4.- GraphicsPC::init()");

        // Generamos el buffer Strategy
        int trys = 100;

        // Intentamos un máximo de 100 veces (sobradísimo)
        while(trys-- > 0)
        {
            try
            {
                // Viewport genera buffer strategy con 2 buffers
                _viewport.createBufferStrategy(2);
                break;
            }
            catch(Exception e)
            {
                e.getCause();
                System.err.print("Error creando buffer strategy");
                return false;
            }
        }

        // Tomamos la instancia del Buffer Strategy de la ventana
        _bufferStrat = _viewport.getBufferStrategy();

        return true;
    }

    /* ------------------------------------------------------------------
     *  GETTERS
     * ------------------------------------------------------------------
     */

    /**
     * Devuelve la herramienta de dibujado de java
     * @return Graphics2D : Instancia de la herramienta de dibujado para llamar a sus metodos.
     */
    public Graphics2D getGraphics()
    {
        return _graphics2D;
    }

    /**
     * Devuelve la instancia de la ventana
     * @return JFRAME
     */
    public JFrame getViewport()
    {
        return _viewport;
    }

    /**
     * Devuelve el gestor de buffers
     * @return BufferStrategy para poder manejar los buffers de pintado.
     */
    public BufferStrategy getStrategy()
    {
       return _bufferStrat;
    }

    /**
     * Simplemente devuelve el ancho de la ventana abierta.
     * @return int tamaño en pixeles.
     */
    public int getViewportWidth() {
        return _viewport.getWidth();
    }

    /**
     * Simplemente devuelve el alto de la ventana abierta.
     * @return int tamaño en pixeles.
     */
    public int getViewportHeight() {
        return _viewport.getHeight();
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
    public int getFontSize()
    {
        return _graphics2D.getFont().getSize();
    }

    /* ------------------------------------------------------------------
     *  SETTERS ESPECIFICOS DE PC - Más abajo estan los de la interfaz.
     * ------------------------------------------------------------------
     */

    /**
     * Set color especifico para PC dando un awt.Color como parametro. NO usado.
     * Establece el color a utilizar en las operaciones de dibujado posteriores.
     * @param c : De tipo Color. Para establecer directamente el color.
     */
    public void setColor(Color c)
    {
        _graphics2D.setColor(c);
    }


    /**
     * Establece el color de limpiado usando un Color de awt.
     * Existe el mismo metodo usando el RGBColor de la interfaz.
     * @param c
     */
    public void setClearColor(Color c) { _clearColor = c; }

    /* ------------------------------------------------------------------
     * LOGICA INTERNA
     * ------------------------------------------------------------------
     */

    /**
     * Establece un modo de pintado predefinido del graphics
     */
    public void prepareDrawGraphics()
    {
        boolean success = false;
        while(!success)
        {
            try
            {
                _graphics2D = (Graphics2D) _bufferStrat.getDrawGraphics();
                if(_graphics2D != null) success = true;
            }
            catch (Exception e)
            {
                System.err.println(e.getMessage());
            }
        }

        if (_graphics2D != null)
        {
            _graphics2D.setColor(Color.BLACK);
            _pincel = new BasicStroke(2f);
            _graphics2D.setStroke(_pincel);
            _originalFont = _graphics2D.getFont(); //Serif
        }
    }

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
     */
    public void drawWhiteBounds()
    {
        //System.out.println("GraphicsPC::drawWhiteBounds()");
        // Pareja de Bandas blancas
        _graphics2D.setColor(Color.WHITE);
        int barra1X1, barra1Y1, barra1X2, barra1Y2;
        int barra2X1, barra2Y1, barra2X2, barra2Y2;

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
            barra1Y2 = getViewportHeight();

            // BORDE DERECHA
            //De la esquina superior derecha
            barra2X1 = getViewportWidth() - Math.abs(_mitadDistanciaVaciaHorizontal); // OJO! Ver que no baje de 0.
            barra2X1 = Math.abs(barra2X1);
            barra2Y1 = 0;
            //A la derecha a la altura del borde LOGICO (es igual de alto que la logica)
            barra2X2 = getViewportWidth();
            barra2Y2 = getViewportHeight();

            // Y los mandamos pintar
            _graphics2D.fillRect(barra1X1,barra1Y1,barra1X2,barra1Y2);
            _graphics2D.fillRect(barra2X1,barra2Y1,barra2X2,barra2Y2);
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
            barra1X2 = getViewportWidth();
            barra1Y2 = Math.abs(_mitadDistanciaVaciaVertical);
            // ABAJO
            //De debajo del juego
            barra2X1 = 0;
            barra2Y1 = getViewportHeight() - Math.abs(_mitadDistanciaVaciaVertical); // OJO! ver que no se baje de 0.
            barra2Y1 = Math.abs(barra2Y1); // Check para no irnos a negativos.
            //A la derecha a la altura del borde LOGICO (es igual de alto que la logica)
            barra2X2 = getViewportWidth();
            barra2Y2 = getViewportHeight();
            // Y los mandamos pintar
            _graphics2D.fillRect(barra1X1,barra1Y1,barra1X2,barra1Y2);
            _graphics2D.fillRect(barra2X1,barra2Y1,barra2X2,barra2Y2);
        }
        else
        {
            // Ocupamos toda la pantalla con el juego
            // No necesitamos bandas blancas
        }
    }

    /**
     * Metodo que calcula los valores de las variables internas segun el tamaño de la ventana. *
     * Llamado en cada frame en PC por si el tamaño de la ventana ha cambiado.
     */
    private void calculateScaleVars()
    {
        // Recalculo de relacion de aspecto
        _relacionVentana = (float)getViewportWidth()/(float)getViewportHeight();

        // Calcular constantemente la relacion de la logica del juego no tiene mucho sentido
        // Recalcular solo cuando cambiamos el tamaño de la logica del juego (ver setLogicSize())
        // _relacionLogicaJuego = (float)_anchoLogica/(float)_altoLogica;

        // Calculamos el factor de escalado
        // Lo que debemos obtener aquí es la escala manteniendo la resolución del juego 2:3, no respecto a la ventana
        // Si la ventana es más ancha de lo que debería
        if (_relacionVentana > _relacionLogicaJuego)
        {
            // Ocupamos toda la vertical y centramos en antura
            _factorEscaladoGeneral =  (float)getViewportHeight() / (float)_altoLogica;
            // Bandas Verticales con distancia sobrante horizontal
            _mitadDistanciaVaciaHorizontal = (int)((getViewportWidth() - (int)(_anchoLogica * _factorEscaladoGeneral))/(float)2.0f);
            _mitadDistanciaVaciaVertical = 0;

        }
        // Si la ventana es más alta de lo que debería
        else if (_relacionVentana < _relacionLogicaJuego)
        {
            // Ocupamos toda la anchura y centramos en antura
            _factorEscaladoGeneral = (float)getViewportWidth() / (float)_anchoLogica;
            // Bandas Horizontales con distancia sobrante vertical
            _mitadDistanciaVaciaVertical = (int)((getViewportHeight() - (int)(_altoLogica * _factorEscaladoGeneral))/(float)2.0f);
            _mitadDistanciaVaciaHorizontal = 0;
        }
        // Si tanto el juego como la ventana son 2:3 (relacion == 0.6666667f)
        else
        {
            // Ocupamos toda la pantalla con el juego
            _factorEscaladoGeneral = (float)getViewportHeight() / (float)_altoLogica; // Aqui nos vale tanto ancho como alto.
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
        float newSize = _graphics2D.getFont().getSize();
        newSize = newSize * (float)_factorEscaladoGeneral;
        Font font = _graphics2D.getFont().deriveFont(newSize);
        _graphics2D.setFont(font);
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
        // Restandole los espacios blancos, deberíamos obtener un valor
        // dentro del espacio lógico. Si es superior es que se ha hecho click fuera
        int lx = (int)((float)(x-_mitadDistanciaVaciaHorizontal)/(float)_factorEscaladoGeneral);
        int ly = (int)((float)(y-_mitadDistanciaVaciaVertical)/(float)_factorEscaladoGeneral);

        // Si alguna coordenada esta fuera del espacio lógico, establecemos ambas a -1
        if (lx > _anchoLogica || lx < 0 || ly > _altoLogica || ly < 0)
        {
            lx = -1;
            ly = -1;
        }
        Position logicCoordinates = new Position(lx,ly);
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
        Position windowCoordinates = new Position(x, y);
        //System.out.println("GraphicPC::Translate Logic(lx:"+lx+",ly:"+ly+") -> Window(x:"+x+",y:"+y+")");

        return windowCoordinates;
    }

    /* -------------------------
     * SETTERS
     * -------------------------
     */

    /**
     * Cambia las dimensiones del espacio logico de juego
     * Esto es muy importante a la hora de usar los metodos de dibujado relativos al espacio logico.
     * Recalcula la relacion logica de juego automaticamente tras cambiar el tamaño logico.
     * @param w Nuevo ancho logico
     * @param h Nuevo alto logico
     */
    @Override
    public void setLogicSize(int w, int h) {
        _anchoLogica = w;
        _altoLogica = h;
        _relacionLogicaJuego = (float)_anchoLogica/(float)_altoLogica;
    }

    /**
     * establece el color a utilizar en las operaciones de dibujado posteriores.
     * @param color: RGBColor, interfaz que almacena valores RGBA (0-255)
     */
    @Override
    public void setColor(RGBColor color)
    {
        Color c = new Color(color.getR(), color.getG(), color.getB(), color.getA());
        _graphics2D.setColor(c);
    }

    /**
     * Metodo para establecer el color de "limpiado"
     * @param c RGBColor
     */
    @Override
    public void setClearColor(RGBColor c) {
        Color newClearColor = new Color(c.getR(), c.getG(), c.getB(), c.getA());
        _clearColor = newClearColor;
    }

    /**
     * Permite cambiar el tamaño de la fuente
     */
    @Override
    public void setFontSize(float fs)
    {
        // Tamaño
        if (fs != getFontSize()){
            Font font = _graphics2D.getFont().deriveFont(fs);
            _graphics2D.setFont(font);
        }
    }

    /**
     * Establece la fuente actual con al que pintar texto.
     * @param f Fuente a utilizar
     */
    @Override
    public void setFont(FontInterface f)
    {
        //System.out.println("GraphicsPC::setFont");
        FontPC _fPC = (FontPC) f;
        _graphics2D.setFont(_fPC.getFont());
    }

    /**
     * Restablece la fuente a la predeterminada por el motor.
     */
    @Override
    public void resetFont()
    {
        _graphics2D.setFont(_originalFont);
    }

    @Override
    public int GetWidth() {
        return _viewport.getWidth();
    }

    @Override
    public int GetHeight() {
        return _viewport.getHeight();
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
    public void translateCanvas(double x, double y)
    {
        _graphics2D.translate(x, y);
    }

    /**
     * Rota la matriz de dibujado
     * Recibe una cantidad de grados y lo pasa a radiantes para llamar al metodo de graphics
     * @param degrees Cuantos grados queremos que gire.
     */
    @Override
    public void rotateCanvas(float degrees)
    {
        _graphics2D.rotate(Math.toRadians(degrees));
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
        _graphics2D.scale(x, y);
    }

    /**
     * Guarda el estado de la matriz de dibujado
     */
    @Override
    public void saveCanvas()
    {
        _savedMatrix = _graphics2D.getTransform();
    }

    /**
     * Carga un estado previo de la matrix de dibujado
     * que fuera almacenado en una variable interna con el metodo saveCanvas
     */
    @Override
    public void restoreCanvas()
    {
        _graphics2D.setTransform(_savedMatrix);
    }

    /* ----------------------------------------
     * METODOS DE PINTADO DE FIGURAS E IMAGENES
     * -----------------------------------------
     */

    /**
     * Metodo de limpiado de pantalla, pinta de un color toda la ventana.
     */
    @Override
    public void clear()
    {
        // Le damos el color al graphics y le pedimos que lo pinte por toda la superficies
        // de la ventana.
        Color previousColor = _graphics2D.getColor();
        _graphics2D.setColor(_clearColor);
        _graphics2D.fillRect(0,0, getViewportWidth(), getViewportHeight());
        _graphics2D.setColor(previousColor);
    }

    /**
     * Metodo de pintado de una imagen
     * Puede pintarse fuera del espacio logico.
     * @param image : Imagen a pintar
     * @param x: Posición X dentro del espacio de ventana
     * @param y : Posición Y dentro del espacio de ventana
     */
    @Override
    public void drawImage(ImageInterface image, int x, int y)
    {
        //Obtenemos la imagen
        ImagePC imgPC = (ImagePC) image;
        BufferedImage bfImg = imgPC.getBuffImage();

        // Check por si esta vacía
        if (bfImg == null)
        {
            System.err.println("GraphicsPC::drawImage() ERROR - La imagen que se ha solicitado pintar esta vacia (null)");
            return;
        }

        // Pintamos la imagen.
        // drawImage(imageToWrite, x, y, width, heigth, null);
        _graphics2D.drawImage(bfImg, x, y, bfImg.getWidth(), bfImg.getHeight(), null);
    }

    /**
     * Metodo de pintado de una imagen
     * Puede pintarse fuera del espacio logico.
     * @param image : Imagen a pintar
     * @param x: Posición X dentro del espacio de ventana
     * @param y : Posición Y dentro del espacio de ventana
     * @param w : ancho que debe ocupar la imagen.
     * @param h : alto que debe ocupar la imagen.
     */
    @Override
    public void drawImage(ImageInterface image, int x, int y, int w, int h)
    {
        //Obtenemos la imagen
        ImagePC imgPC = (ImagePC) image;
        BufferedImage bfImg = imgPC.getBuffImage();

        // Check por si esta vacía
        if (bfImg == null)
        {
            System.err.println("GraphicsPC::drawImage() ERROR - La imagen que se ha solicitado pintar esta vacia (null)");
            return;
        }

        // Pintamos la imagen.
        // drawImage(imageToWrite, x, y, width, heigth, null);
        _graphics2D.drawImage(bfImg, x, y, bfImg.getWidth(), bfImg.getHeight(), null);
    }

    /**
     * Pinta la imagen, escalandola al tamaño indicado
     * @param image : Imagen a pintar
     * @param xLogico : Posición X dentro del espacio de ventana
     * @param yLogico : Posición Y dentro del espacio de ventana
     */
    @Override
    public void drawImageInLogicSpace(ImageInterface image, int xLogico, int yLogico)
    {
        //Obtenemos la imagen
        ImagePC imgPC = (ImagePC) image;
        BufferedImage bfImg = imgPC.getBuffImage();

        // Check por si esta vacía
        if (bfImg == null)
        {
            System.err.println("GraphicsPC::drawImage() ERROR - La imagen que se ha solicitado pintar esta vacia (null)");
            return;
        }

        // Conversión posición Logica a Ventana y escalado
        int x = (int)(xLogico*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)(yLogico*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int w = (int)(bfImg.getWidth()*_factorEscaladoGeneral);
        int h = (int)(bfImg.getHeight()*_factorEscaladoGeneral);

        // Pintamos la imagen.
        _graphics2D.drawImage(bfImg, x, y, w, h, null);
    }

    /**
     * Pinta la imagen, con el tamaño indicado
     * @param image : Imagen a pintar
     * @param xLogico : Posición X dentro del espacio de ventana
     * @param yLogico : Posición Y dentro del espacio de ventana
     * @param logicImgWidth : Ancho a ocupar dentro de las coordenaas logicas
     * @param logicImgHeight : Alto a ocupar dentro de las coordenadas logicas
     */
    @Override
    public void drawImageInLogicSpace(ImageInterface image, int xLogico, int yLogico, int logicImgWidth, int logicImgHeight)
    {
        //Obtenemos la imagen
        ImagePC imgPC = (ImagePC) image;
        BufferedImage bfImg = imgPC.getBuffImage();

        // Check por si esta vacía
        if (bfImg == null)
        {
            System.err.println("GraphicsPC::drawImage() ERROR - La imagen que se ha solicitado pintar esta vacia (null)");
            return;
        }

        // Conversión posición Logica a Ventana
        int x = (int)(xLogico*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)(yLogico*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int w = (int)(logicImgWidth*_factorEscaladoGeneral);
        int h = (int)(logicImgHeight*_factorEscaladoGeneral);

        // Pintamos la imagen.
        // drawImage(imageToWrite, x, y, width, heigth, null);
        _graphics2D.drawImage(bfImg, x, y, w, h, null);
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
    public void drawLine(int x1, int y1, int x2, int y2) {
        _graphics2D.drawLine(x1, y1, x2, y2);
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
        _graphics2D.drawLine(x1, y1, x2, y2);
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
        _graphics2D.drawRect(x, y, w, h);
    }

    /**
     * Dibuja un cuadrado a partir de dos puntos (x1,y1) con un ancho y alto dado
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
    public void drawRectInLogicSpace(int lx, int ly, int lw, int lh)
    {
        // Transformacion de coordenadas
        int x = (int)(lx*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)(ly*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int w = (int)(lw*_factorEscaladoGeneral);
        int h = (int)(lh*_factorEscaladoGeneral);

        // Pintado
        _graphics2D.drawRect(x, y, w, h);
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
        _graphics2D.fillRect(x, y, w, h);
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
        // Transformacion de coordenadas
        int x = (int)(lx*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)(ly*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int w = (int)(lw*_factorEscaladoGeneral);
        int h = (int)(lh*_factorEscaladoGeneral);

        // Pintado
        _graphics2D.fillRect(x, y, w, h);
    }

    /**
     * Dibuja el contorno de un circulo en el espacio de ventana
     * Se aporta las coordenadas del punto central del circulo (cx, cy) y el radio.
     * @param cx : Coordenada X del punto central del círculo.
     * @param cy : Coordenada Y del punto central del circulo.
     * @param radius
     */
    @Override
    public void drawCircle(int cx, int cy, int radius)
    {
        // Covertimos la posición central del circulo a la posición
        // de la esquina superior izquierda que utiliza drawOval de graphics2D.
        int x = cx - radius;
        int y = cy - radius;
        _graphics2D.drawOval(x, y, radius*2, radius*2);
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
        // Covertimos la posición central del circulo a la posición
        // de la esquina superior izquierda que utiliza drawOval de graphics2D.
        int lx = lcx - lr;
        int ly = lcy - lr;

        // Conversión Logico a Ventana
        int x = (int)(lx*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)(ly*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int radio = (int)((float)lr * _factorEscaladoGeneral);
        _graphics2D.drawOval(x, y, radio*2, radio*2);
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
        // Covertimos la posición central del circulo a la posición
        // de la esquina superior izquierda que utiliza drawOval de graphics2D.
        int x = cx - w;
        int y = cy - h;

        // Pintamos el ovalo.
        _graphics2D.drawOval(x, y, w*2, h*2);
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
        // Covertimos la posición central del circulo a la posición
        // de la esquina superior izquierda que utiliza drawOval de graphics2D.
        int lx = lcx - lw;
        int ly = lcy - lh;

        // Conversión Logico a Ventana
        int x = (int)(lx*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)(ly*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int w = (int)((float)lw * _factorEscaladoGeneral);
        int h = (int)((float)lh * _factorEscaladoGeneral);

        // Pintamos el ovalo.
        _graphics2D.drawOval(x, y, w*2, h*2);
    }

    /**
     * Rellena de color un circulo en la posición (lcx, lcy) del espacio de ventana
     * @param cx Coordenada X del centro del circulo
     * @param cy Coordenada Y del centro del circulo
     * @param radius radio del circulo.
     */
    @Override
    public void fillCircle(int cx, int cy, int radius)
    {
        // Covertimos la posición central del circulo a la posición
        // de la esquina superior izquierda que utiliza drawOval de graphics2D.
        int x = cx - radius;
        int y = cy - radius;
        _graphics2D.fillOval(x, y, radius*2, radius*2);
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
        // Covertimos la posición central del circulo a la posición
        // de la esquina superior izquierda que utiliza drawOval de graphics2D.
        int lx = lcx - lr;
        int ly = lcy - lr;

        // Conversión Logico a Ventana
        int x = (int)(lx*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)(ly*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int radio = (int)((float)lr * _factorEscaladoGeneral);

        // Pintamos el circulo.
        _graphics2D.fillOval(x, y, radio*2, radio*2);
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
        // Covertimos la posición central del circulo a la posición
        // de la esquina superior izquierda que utiliza drawOval de graphics2D.
        int x = cx - w;
        int y = cy - h;

        // Pintamos el ovalo.
        _graphics2D.fillOval(x, y, w*2, h*2);
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
        // Covertimos la posición central del circulo a la posición
        // de la esquina superior izquierda que utiliza drawOval de graphics2D.
        int lx = lcx - lw;
        int ly = lcy - lh;

        // Conversión Logico a Ventana
        int x = (int)(lx*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)(ly*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;
        int w = (int)((float)lw * _factorEscaladoGeneral);
        int h = (int)((float)lh * _factorEscaladoGeneral);

        // Pintamos el ovalo.
        _graphics2D.fillOval(x, y, w*2, h*2);
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
        // Pintado
        _graphics2D.drawString(text, x, y);
    }

    /**
     * Metodo simple para pintar un texto en cualquier espacio de la ventana
     * @param text : String de texto
     * @param x : posicion x de la ventana
     * @param y : posicion y de la ventana
     * @param applyScale : Boolean para determinar si el escalado logico afecta al texto.
     */
    @Override
    public void drawTextScalable(String text, int x, int y, boolean applyScale)
    {
        // Escalado
        if (applyScale) resizeFontFromScale();

        // Pintado
        _graphics2D.drawString(text, x, y);
    }

    /**
     * Metodo simple para pintar un texto dentro del espacio logico de juego
     * @param text : String de texto
     * @param xLogico : posicion x del espacio logico
     * @param yLogico : posicion y del espacio logico
     * @param applyScale : Boolean para determinar si el escalado logico afecta al texto.
     */
    @Override
    public void drawTextInLogicSpace(String text, int xLogico, int yLogico, boolean applyScale)
    {
        // Escalado
        // PC: Si escalado es FALSE el tamaño de la fuente se mantiene igual por mucho que
        // varíe el tamaño de la ventana.
        int fsize = getFontSize();
        if (applyScale) resizeFontFromScale();

        // Conversion de coordenadas logicas a espacio de ventana
        // Conversión Logico a Ventana
        int x = (int)(xLogico*_factorEscaladoGeneral) + _mitadDistanciaVaciaHorizontal;
        int y = (int)(yLogico*_factorEscaladoGeneral) + _mitadDistanciaVaciaVertical;

        // Pintado
        _graphics2D.drawString(text, x, y);

        // Devolvemos al tamaño original
        // IMPORTANTE ya que de no hacerlo se acumularían los escalados de un texto a otro.
        setFontSize(fsize);
    }

    /* ----------------------------------------
     * EJEMPLOS PARA TESTING Y DEBUG
     * ----------------------------------------
     */

    /**
     * Metodo que pinta un ejemplo de ventana de juego
     * Usado para testing.
     */
    @Override
    public void drawExample()
    {
        //System.out.println("GraphicsPC::drawExample()");
        int w = getViewportWidth();
        int h = getViewportHeight();
        float s = getCurrentScale();
        int mitadDistVert = getWhiteBandHeight();
        int mitadDistHori = getWhiteBandWidth();
        float winAspect = getWindowAspect();

        // Window Info
        setColor(Color.BLACK);
        String message = "Ventana: (ancho: " + String.valueOf(w) + ", alto: " + String.valueOf(h) + ")";
        drawText(message, 10, 50);
        message = "Aspect: " + String.valueOf(winAspect);
        drawText(message, 10, 70);
        // Escala
        message = "Escalado lógico: " + String.valueOf(s);
        drawText(message, 10, 90);
        // Bandas blancas
        setColor(Color.BLACK);
        message = "Alto Banda Horizontal: " + String.valueOf(mitadDistVert);
        drawText(message, 10, 110);
        message = "Ancho Banda Vertical: " + String.valueOf(mitadDistHori);
        drawText(message, 10, 130);
        // Texto del tamaño de tablero
        setFontSize(64f);
        setColor(Color.BLACK);
        int textOffset = (int)(getFontSize()/2.0f); //Offset respecto a su tamaño para centrarlo
        drawTextInLogicSpace("3x3", 190-textOffset, 100+textOffset, true);
        setFontSize(16f);
        // Circulo
        setColor(Color.RED);
        fillCircleInLogicSpace(100, 200, 100);
        fillCircleInLogicSpace(200, 200, 100);
        fillCircleInLogicSpace(300, 200, 100);
        /*
        setColor(Color.BLUE);
        fillCircleWithTextInLogicSpace(150, 200, 100, "1");
        fillCircleWithTextInLogicSpace(250, 200, 100, "2");
        setColor(Color.WHITE);
        fillCircleInLogicSpace(50, 300, 100);
        fillCircleInLogicSpace(150, 300, 100);
        fillCircleInLogicSpace(250, 300, 100);
        setColor(Color.BLUE);
        fillCircleWithTextInLogicSpace(50, 400, 100, "2");
        setColor(Color.RED);
        fillCircleInLogicSpace(150, 400, 100);
        setColor(Color.WHITE);
        fillCircleInLogicSpace(250, 400, 100);
        */
    }
}
