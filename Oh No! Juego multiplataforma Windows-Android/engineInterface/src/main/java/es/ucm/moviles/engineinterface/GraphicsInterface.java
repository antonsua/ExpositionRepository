package es.ucm.moviles.engineinterface;

import java.util.ArrayList;

/**
 * Interfaz Graphics
 * Creada para aportar herramientas a la lógica para que mande pintar objetos sin preocuparse
 * del motor interno que lo haga (PC o Android).
 */
public interface GraphicsInterface
{
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
    Position translateWindowToLogic(int x, int y);

    /**
     * Dadas unas coordenadas logicas, devuelve su equivalente en el espacio de la ventana.
     * @param lx
     * @param ly
     * @return ArrayList de dos elementos con X en posicion 0 e Y en posición 1.
     */
    Position translateLogicToWindow(int lx, int ly);

    /* -------------------------
     * SETTERS
     * -------------------------
     */
    /**
     * Métodos de control de tamaño logico para que el motor pueda usarse por cualquier implementacion
     * Este método NO debe llamarse en nuestra implementacion de la practica
     * ya que es un espacio logico prestablecido de 400x600
     * @param w
     * @param h
     */
    void setLogicSize(int w, int h);

    /**
     * Cambia el color utilizado por el motor para pintar en futuras llamadas.
     * @param color RGBColor
     */
    void setColor(RGBColor color);     //Establece el color en las operaciones de dibujado posteriores

    /**
     * Metodo para establecer el color de "limpiado"
     * @param c RGBColor
     */
    void setClearColor(RGBColor c);

    /**
     * Establece la fuente actual con al que pintar texto.
     * @param f Fuente a utilizar
     */
    void setFont(FontInterface f);

    /**
     * Permite cambiar el tamaño de la fuente usada actualmetente
     * @param fs float nuevo tamaño de la fuente.
     */
    void setFontSize(float fs);

    /**
     * Restablece la fuente a la predeterminada por el motor.
     */
    void resetFont();

    /* -------------------------
     * GETTERS
     * -------------------------
     */
    int GetWidth();

    int GetHeight();


    /* ----------------------------------------
     * METODOS DE MANIPULACION DEL CANVAS
     * ----------------------------------------
     */
    /**
     * Mueve la matriz de dibujado
     * @param x double movimiento en el eje X
     * @param y double movimiento en el eje Y
     */
    void translateCanvas(double x, double y);

    /**
     * Rota la matriz de dibujado
     * Recibe una cantidad de grados y lo pasa a radiantes para llamar al metodo de graphics
     * @param degrees Cuantos grados queremos que gire.
     */
    void rotateCanvas(float degrees);

    /**
     * Escala la matriz de dibujado
     * Recibe una cantidad de grados y lo pasa a radiantes para llamar al metodo de graphics
     * @param x float escalado del eje X
     * @param y float escalado del eje Y
     */
    void scaleCanvas(float x, float y);

    /**
     * Guarda el estado de la matriz de dibujado
     */
    void saveCanvas();

    /**
     * Carga un estado previo de la matrix de dibujado
     * que fuera almacenado en una variable interna con el metodo saveCanvas
     */
    void restoreCanvas();

    /* ----------------------------------------
     * METODOS DE PINTADO DE FIGURAS E IMAGENES
     * -----------------------------------------
     */

    /**
     * Limpia la pantalla utilizando el color de limpiado establecido en el motor
     * Principalmente llamado por el motor antes de pintar cada frame.
     * Pero damos opcion a la lógica de llamarlo si fuese necesario.
     */
    void clear();

    /**
     * Metodo de pintado de una imagen
     * Puede pintarse fuera del espacio logico.
     * @param image : Imagen a pintar
     * @param x: Posición X dentro del espacio de ventana
     * @param y : Posición Y dentro del espacio de ventana
     */
    void drawImage(ImageInterface image, int x, int y);

    /**
     * Metodo de pintado de una imagen con el tamaño dado.
     * Puede pintarse fuera del espacio logico.
     * @param image : Imagen a pintar
     * @param x: Posición X dentro del espacio de ventana
     * @param y : Posición Y dentro del espacio de ventana
     */
    void drawImage(ImageInterface image, int x, int y, int w, int h);

    /**
     * Metodo de pintado de una imagen dentro del espacio logico
     * Se ajustará cuando cambie el tamaño de ventana y se escalara con ella.
     * @param image : Imagen a pintar
     * @param xLogico : Posición X dentro del espacio de ventana
     * @param yLogico : Posición Y dentro del espacio de ventana
     */
    void drawImageInLogicSpace(ImageInterface image, int xLogico, int yLogico);

    /**
     * Pinta la imagen, con el tamaño indicado
     * Se ajustará cuando cambie el tamaño de ventana y se escalara con ella.
     * @param image : Imagen a pintar
     * @param xLogico : Posición X dentro del espacio de ventana
     * @param yLogico : Posición Y dentro del espacio de ventana
     * @param logicImgWidth : Ancho a ocupar dentro de las coordenaas logicas
     * @param logicImgHeight : Alto a ocupar dentro de las coordenadas logicas
     */
    void drawImageInLogicSpace(ImageInterface image, int xLogico, int yLogico, int logicImgWidth, int logicImgHeight);

    /**
     * Dibuja una línea recta entre dos puntos (x1,y1) y (x2,y2) del espacio de ventana
     *       (x1,y1) · ------------------------- · (x2,y2)
     * @param x1 Coordenada X del primer punto
     * @param y1 Coordenada Y del primer punto
     * @param x2 Coordenada X del segundo punto
     * @param y2 Coordenada Y del segundo punto
     */
    void drawLine(int x1, int y1, int x2, int y2);

    /**
     * Dibuja una línea recta entre dos puntos (lx1,ly1) y (lx2,ly2) del espacio logico
     *       (lx1,ly1) · ------------------------- · (lx2,ly2)
     * @param lx1 Coordenada X del primer punto en el espacio logico
     * @param ly1 Coordenada Y del primer punto en el espacio logico
     * @param lx2 Coordenada X del segundo punto en el espacio logico
     * @param ly2 Coordenada Y del segundo punto en el espacio logico
     */
    void drawLineInLogicSpace(int lx1, int ly1, int lx2, int ly2);

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
    void drawRect(int x, int y, int w, int h);

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
    void drawRectInLogicSpace(int lx, int ly, int lw, int lh);

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
    void fillRect(int x, int y, int w, int h);

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
    void fillRectInLogicSpace(int lx, int ly, int lw, int lh);

    /**
     * Dibuja el contorno de un circulo en el espacio de ventana
     * Se aporta las coordenadas del punto central del circulo (cx, cy) y el radio.
     * @param cx : Coordenada X del punto central del círculo.
     * @param cy : Coordenada Y del punto central del circulo.
     * @param radius
     */
    void drawCircle(int cx, int cy, int radius);

    /**
     * Dibuja el contorno de un circulo en el espacio lógico
     * Se aportan la posición (x,y) del centro del circulo en coordenadas logicas y el radio logico.
     * @param lcx : Coordenada X del punto central del círculo dentro del espacio logico.
     * @param lcy : Coordenada Y del punto central del círculo dentro del espacio logico.
     * @param lr : Radio del circulo
     */
    void drawCircleInLogicSpace(int lcx, int lcy, int lr);

    /**
     * Dibuja el contorno de un ovalo en el espacio de ventana.
     * El ovalo se pinta definiendo un punto que representa el centro de este
     * y a partir del cual se extiende un espacio que lo contendrá, dandole el ancho y alto.
     * @param cx Coordenada X del centro del circulo.
     * @param cy Coordenada Y del centro del circulo.
     * @param w ancho del ovalo.
     * @param h alto del ovalo.
     */
    void drawOval(int cx, int cy, int w, int h);

    /**
     * Dibuja el contorno de un ovalo en el espacio logico.
     * El ovalo se pinta definiendo un punto que representa el centro de este
     * y a partir del cual se extiende un espacio que lo contendrá, dandole el ancho y alto.
     * @param lcx Coordenada X del centro del ovalo en espacio logico.
     * @param lcy Coordenada Y del centro del ovalo en espacio logico.
     * @param lw ancho logico del ovalo.
     * @param lh alto logico del ovalo.
     */
    void drawOvalInLogicSpace(int lcx, int lcy, int lw, int lh);

    /**
     * Rellena de color un circulo en la posición (lcx, lcy) del espacio de ventana
     * @param cx Coordenada X del centro del circulo
     * @param cy Coordenada Y del centro del circulo
     * @param radius radio del circulo.
     */
    void fillCircle(int cx, int cy, int radius);

    /**
     * Rellena de color un circulo en la posición (lcx, lcy) del espacio logico con el radio indicado
     * El circulo escalara con la ventana.
     * @param lcx Coordenada X del centro del circulo en el espacio logico
     * @param lcy Coordenada Y del centro del circulo en el espacio logico
     * @param lr radio logico del circulo.
     */
    void fillCircleInLogicSpace(int lcx, int lcy, int lr);

    /**
     * Rellena de color un ovalo en el espacio de ventana.
     * El ovalo se pinta definiendo un punto que representa el centro de este
     * y a partir del cual se extiende un espacio que lo contendrá, dandole el ancho y alto.
     * @param cx Coordenada X del centro del circulo.
     * @param cy Coordenada Y del centro del circulo.
     * @param w ancho del ovalo.
     * @param h alto del ovalo.
     */
    void fillOval(int cx, int cy, int w, int h);

    /**
     * Rellena de color un ovalo en el espacio logico.
     * El ovalo se pinta definiendo un punto que representa el centro de este
     * y a partir del cual se extiende un espacio que lo contendrá, dandole el ancho y alto.
     * @param lcx Coordenada X del centro del ovalo en espacio logico.
     * @param lcy Coordenada Y del centro del ovalo en espacio logico.
     * @param lw ancho logico del ovalo.
     * @param lh alto logico del ovalo.
     */
    void fillOvalInLogicSpace(int lcx, int lcy, int lw, int lh);

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
    void drawText(String text, int x, int y); //Escribe le fuente con el color y tamaño activos

    /**
     * Metodo simple para pintar un texto en cualquier espacio de la ventana
     * @param text : String de texto
     * @param x : posicion x de la ventana
     * @param y : posicion y de la ventana
     * @param applyScale : Boolean para determinar si el escalado logico afecta al texto.
     */
    void drawTextScalable(String text, int x, int y, boolean applyScale);

    /**
     * Metodo simple para pintar un texto dentro del espacio logico de juego
     * @param text : String de texto
     * @param xLogico : posicion x del espacio logico
     * @param yLogico : posicion y del espacio logico
     * @param applyScale : Boolean para determinar si el escalado logico afecta al texto.
     */
    void drawTextInLogicSpace(String text, int xLogico, int yLogico, boolean applyScale);

    /* ----------------------------------------
     * EJEMPLOS PARA TESTING Y DEBUG
     * ----------------------------------------
     */

    /**
     * Metodo de pintado de una pantalla de ejemplo.
     */
    void drawExample();
}
