package es.ucm.moviles.enginepc;

// Import de la clase que genera JFrame que controla la ventana.
import javax.swing.JFrame;

//
import java.awt.Color;
import java.awt.image.BufferStrategy;

// Import para
import es.ucm.moviles.engineinterface.Engine;
import es.ucm.moviles.engineinterface.InputInterface;
import es.ucm.moviles.engineinterface.ResourcesInterface;
import es.ucm.moviles.engineinterface.ResourceManagerInterface;
import es.ucm.moviles.engineinterface.Scene;

/**
 * Clase que se encarga del motor de dibujado en PC y que utilizará la lógica a través de la
 * interfaz para ordenar dibujar distintos objetos en la ventana.
 */
public class EnginePC implements Engine
{
    // Instancia de la clase propia que instancia el Graphics2D que se encarga del pintado.
    private GraphicsPC _graphics;
    private BufferStrategy _buffStrat;
    private Scene _scene;
    private JFrame _viewPort;
    private InputPC _input;
    private ResourcesPC _resources;
    private FontManagerPC _fontRes;
    private ImageManagerPC _ImageRes;
    private AudioManagerPC _audioRes;
    // Variables relacionadas con deltaTime
    // del bucle principal
    private long _lastFrameTime;    // momento del anterior Frame
    private long _currentFrameTime; // momento del Frame Actual
    private boolean _60FrameLock;   // Si True, funciona a 60FPS. Establecido en la constructora.

    /**
     * Constructora del motor gráfico para la ejecución en PC.
     * Genera una instancia de nuestra clase Graphics que controla el pintado de
     * elementos utilizando Graphics2D de javax.awt
     * Recibe la ventana sobre la que pintar desde la clase PCMain que se encarga del arranque
     * de la aplicación, además de darle nombre y tamaño a la ventana. (h:400 x w:600)
     */
    public EnginePC()
    {
        _60FrameLock = true;
    } // EnginePC()

    /**
     * Inicializador del motor de PC
     * Genera la ventana con los parametros dados desde PcLauncher::main()
     * Genera el motor de dibujado de awt.graphics2D (GraphicsPC _graphics)
     * Crea el hilo paralelo de renderizado activo.
     * @param windowName String con el nombre de la ventana.
     * @param windowWidth Ancho de la ventana a generar.
     * @param windowHeight Alto de la ventana a generar.
     */
    public void init(String windowName, int windowWidth, int windowHeight)
    {
        //System.out.println("3.- EnginePC::init()");

        // Generamos la ventana
        _viewPort = new JFrame(windowName); // MyJFrame personalizado con bucle principal del juego.
        _viewPort.setSize(windowWidth, windowHeight); // Redimensionamos la ventana a los parametros recibidos
        _viewPort.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        _viewPort.setUndecorated(false);
        _viewPort.setVisible(true);

        // Generamos el motor de dibujado
        _graphics = new GraphicsPC(_viewPort);
        _graphics.init();

        // Generamos instancia del gestor de input
        _input = new InputPC(_viewPort);

        // Gestor recursos
        _resources = new ResourcesPC();
        _resources.init();

        _fontRes = new FontManagerPC();
        _fontRes.Init();

        _ImageRes = new ImageManagerPC();
        _ImageRes.Init();

        _audioRes = new AudioManagerPC();
        _audioRes.Init();
    }

    /**
     * Método que implementa el bucle principal.
     * Llamará a la interfaz de la aplicación para que esta llame al update y render
     * de la lógica.
     * Aunque se llame run() no implica que sea un método ejecutado en un hilo paralelo.
     * Eso solo lo hará el run() de MyJFrame, ya que implementa la interfaz Runnable.
     */
    public void runMainLoop()
    {
        //System.out.println("6.- EnginePC::runMainLoop() Arranque Bucle principal.");

        // Variables de Tiempo
        _lastFrameTime = System.nanoTime(); // Obtenemos punto de referencia inicial de la ejecución

        // Preparamos el graphics
        _buffStrat = _graphics.getStrategy();

        // Bucle Principal
        while(true)
        {
            // Calculo del DeltaTime
            _currentFrameTime = System.nanoTime();
            long nanoDeltaTime = _currentFrameTime - _lastFrameTime;
            double deltaTime = (double) nanoDeltaTime/1.0E9;
            // Establecemos el color de limpiado de pantalla
            _graphics.setClearColor(Color.WHITE);//Color.PINK);
            do {
                do {
                    // Obtiene la zona de pintado y establece las variables de pincel
                    _graphics.prepareDrawGraphics();
                    // Zona de llamada a los métodos de la lógica del bucle principal
                    try
                    {
                        if (_60FrameLock)
                        {
                            if((float)deltaTime >= 0.0166667f)
                            {
                                _lastFrameTime = _currentFrameTime;
                                //System.out.println("DeltaTime: " + deltaTime);
                                // Limpiamos
                                _graphics.clear();
                                // Pintamos bandas blancas
                                _graphics.drawWhiteBounds();
                                // Bucle principal implementado en la logica
                                _scene.onUpdate((float)deltaTime);
                                _scene.onRender(_graphics);
                            }
                        }
                        else
                        {
                            _lastFrameTime = _currentFrameTime;
                            //System.out.println("DeltaTime: " + deltaTime);
                            // Bucle principal
                            _scene.onUpdate((float)deltaTime);
                            _scene.onRender(_graphics);
                        }
                    }
                    finally
                    {
                        _graphics.getGraphics().dispose(); // Liberamos la zona de pintado
                    }
                } while (_buffStrat.contentsRestored());
                // Le decimos al buffer Strategy que intercambie los buffers
                _buffStrat.show();
            } while (_buffStrat.contentsLost());
        }
    }

    /* ----------------------------------------------------
     * METODOS DE LA INTERFAZ (GETTERS Y SETTERS)
     * ----------------------------------------------------
     */

    /**
     * Enlace con la clase Interfaz usado para que el bucle principal se pase a la lógica.
     * @param scn
     */
    @Override
    public void setScene(Scene scn)
    {
        _scene = scn;
    }

    @Override
    public ResourceManagerInterface getFontManager() {
        return _fontRes;
    }

    @Override
    public ResourceManagerInterface getImageManager() { return _ImageRes;}

    /**
     * Devuelve instancia del gestor de recursos para gestionarlos.
     * @return ResourcesInterface
     */
    @Override
    public ResourcesInterface getResources() {
        return _resources;
    }

    /**
     * Devuelve la instancia del motor de dibujado para utilizar sus métodos.
     * LLamado por: Lógica a través de la interfaz.
     * @return
     */
    @Override
    public GraphicsPC getGraphics()
    {
        return _graphics;
    } // getGraphics()

    /**
     * Devuelve instancia del input interface.
     * @return
     */
    @Override
    public InputInterface getInput() {
        return _input;
    }

    @Override
    public AudioManagerPC getAudioManager() {
        return _audioRes;
    }
}