package es.ucm.moviles.logica;

import java.util.List;

import es.ucm.moviles.engineinterface.AudioInterface;
import es.ucm.moviles.engineinterface.Engine;
import es.ucm.moviles.engineinterface.FontInterface;
import es.ucm.moviles.engineinterface.GraphicsInterface;
import es.ucm.moviles.engineinterface.ImageInterface;
import es.ucm.moviles.engineinterface.InputInterface;
import es.ucm.moviles.engineinterface.Position;
import es.ucm.moviles.engineinterface.RGBColor;
import es.ucm.moviles.engineinterface.ResourceManagerInterface;
import es.ucm.moviles.engineinterface.ResourcesInterface;
import es.ucm.moviles.engineinterface.Scene;
import es.ucm.moviles.engineinterface.TouchEvent;

public class LevelSelectionScene implements Scene
{
    // Instancias importantes
    Engine _engine;
    InputInterface _input;
    ResourcesInterface _resources;
    private GraphicsInterface _graphics;

    // Variables de imagenes
    private ImageInterface _closeImage;

    // Variables de fuentes;
    private FontInterface _font1;
    private FontInterface _font2;

    //Variables de audio
    private AudioInterface _buttonSound;

    // Colores
    private RGBColor _black;
    private RGBColor _blue;
    private RGBColor _red;
    private RGBColor _white;

    // Botones
    private LevelButton board4;
    private LevelButton board5;
    private LevelButton board6;
    private LevelButton board7;
    private LevelButton board8;
    private LevelButton board9;
    private ImageButton closeButton;

    // Texto
    // En el caso de venir de la un tablero completado
    // Mostraremos el mensaje de victoria, como en el juego original
    private String _headerMessage;


    private static final float ANIMATION_DURATION = 0.75f;
    private ColorAnimation _animation;

    public LevelSelectionScene(String txt)
    {
        _headerMessage = txt;
    }

    /**
     * Recibe el motor de juego especifico de la plataforma que lo ejecuta
     * y recoge en variables internas las instancias importantes de este.
     * Llama a cargar los recursos necesarios para esta escena.
     * @param engine Motor de juego de la plataforma que lo ha lanzado.
     */
    @Override
    public void init(Engine engine)
    {
        // Recibimos el engine
        _engine = engine;
        _input = engine.getInput();
        _resources = engine.getResources();
        _graphics = engine.getGraphics();

        // Carga de recursos especificos de esta escena en las variables internas
        loadSceneResources();
        if(!_headerMessage.equals("Oh no"))
        {
            _animation = new FadeOutAnimation(RGBColor.WHITE, ANIMATION_DURATION);
        }

    }

    /**
     * Metodo para cargar los recursos que desee la escena utilizando el gestor de recursos.
     * Aunque se llame a un load no signifique que cargue varias veces el recurso en el gestor
     * sino que primero comprueba si dicho recurso existe en el diccionario y sino lo carga.
     */
    void loadSceneResources()
    {
        ResourceManagerInterface _fonts = _engine.getFontManager();
        ResourceManagerInterface _images = _engine.getImageManager();
        ResourceManagerInterface _audios = _engine.getAudioManager();

        boolean result;

        // Fonts
        // JosefinSans->Identificador: "Josefin Sans Bold"
        _font1 = (FontInterface) _fonts.getResource("JosefinSans-Bold.ttf", 12,0);
        if(_font1 == null)
            System.err.println("No se ha podido cargar JosefinSans.Bold.ttf");

        // Molle-Regular->Identificador: "Molle Regular"
        _font2 = (FontInterface) _fonts.getResource("Molle-Regular.ttf", 12,0);
        if(_font2 == null)
            System.err.println("No se ha podido cargar Molle-Regular.ttf");

        // Images
        // Close Image
        _closeImage = (ImageInterface) _images.getResource("close.png");
        if(_closeImage == null)
            System.err.println("No se ha podido cargar close.png");

        //Audio
        //Boton
        _buttonSound = (AudioInterface) _audios.getResource("buttonSmoother.wav");
        if(_buttonSound == null)
            System.err.println("No se ha podido cargar button-3.wav");

        // Colores
        _black = new RGBColor(0,0,0);
        _blue = new RGBColor(100,175,255);
        _red = new RGBColor(255,80,80);
        _white = new RGBColor(255,255,255);

        // Botones
        Position b4pos = new Position(130,275);
        board4 = new LevelButton(b4pos,"4",_font1,32f,32, _blue, _white);
        Position b5pos = new Position(200,275);
        board5 = new LevelButton(b5pos,"5",_font1,32f,32, _red, _white);
        Position b6pos = new Position(270,275);
        board6 = new LevelButton(b6pos,"6",_font1,32f,32, _blue, _white);
        Position b7pos = new Position(130,350);
        board7 = new LevelButton(b7pos,"7",_font1,32f,32, _red, _white);
        Position b8pos = new Position(200,350);
        board8 = new LevelButton(b8pos,"8",_font1,32f,32, _blue, _white);
        Position b9pos = new Position(270,350);
        board9 = new LevelButton(b9pos,"9",_font1,32f,32, _red, _white);
        Position closeButtonPos = new Position(190,550);
        closeButton = new ImageButton(closeButtonPos, _closeImage,25,25);
    }

    /**
     * Metodo para llamar al update de los objetos.
     * @param deltaTime float con el tiempo transcurrido desde el anterior ciclo de ejecución.
     */
    @Override
    public void onUpdate(float deltaTime)
    {
        // Handle Events
        handleEvents(_input.getTouchEvents());
        // Update de Objetos
        if(_animation != null)
        {
            _animation.update(deltaTime);
            if(_animation.hasEnded())
                _animation = null;
        }
    }

    /**
     * Metodo para llamar a los renders
     * @param g motor grafico que contiene los metodos de renderizado.
     */
    @Override
    public void onRender(GraphicsInterface g)
    {
        // Oh No Text
        g.setColor(_black);
        if (_headerMessage.equals("Oh no"))
        {
            g.setFont(_font2);
            g.setFontSize(72f);
            g.drawTextInLogicSpace(_headerMessage, 90,100,true);
        }
        else
        {
            g.setFont(_font1);
            g.setFontSize(60f);
            g.drawTextInLogicSpace(_headerMessage, 50,80,true);
        }


        // Texto elige tamaño
        g.setColor(_black);
        g.setFont(_font1);
        g.setFontSize(26f);
        g.drawTextInLogicSpace("Elija el tamaño a jugar", 80,190,true);

        // Grid de botones de seleccion de tamaño
        board4.render(_graphics);
        board5.render(_graphics);
        board6.render(_graphics);
        board7.render(_graphics);
        board8.render(_graphics);
        board9.render(_graphics);

        // Boton Close
        _graphics.drawImageInLogicSpace(_closeImage, 190, 550, 25, 25);

        if(_animation != null)
        {
            _graphics.setColor(_animation.getColor());
            _graphics.fillRectInLogicSpace(0, 0, _graphics.GetWidth(), _graphics.GetHeight());
        }
    }

    /**
     * Metodo que gestiona los eventos recibidos por el motor.
     * @param events La lista de eventos generados desde la última vez
     */
    private void handleEvents(List<TouchEvent> events)
    {
        if (!events.isEmpty())
        {
            for(TouchEvent event : events)
            {
                // Transformar las coordenadas del evento a coordenadas lógicas
                Position logicPos = _graphics.translateWindowToLogic(event.getPosX(), event.getPosY());
                if (event != null && event.getTouchType()!= null)
                {
                    switch(event.getTouchType())
                    {
                        case PRESSED:
                                 if(board4.inside(logicPos)) onLevelButtonPressed(4);
                            else if(board5.inside(logicPos)) onLevelButtonPressed(5);
                            else if(board6.inside(logicPos)) onLevelButtonPressed(6);
                            else if(board7.inside(logicPos)) onLevelButtonPressed(7);
                            else if(board8.inside(logicPos)) onLevelButtonPressed(8);
                            else if(board9.inside(logicPos)) onLevelButtonPressed(9);
                            else if(closeButton.inside(logicPos)) onCloseButtonPressed();
                            break;
                        case RELEASED:
                            break;
                        case DRAGGED:
                            break;
                    }
                }
            }
        }
    }

    /**
     * Metodo "callback" que salta a la escena de tablero seleccionada
     * @param selection int tamaño de tablero a generar.
     */
    private void onLevelButtonPressed(int selection)
    {
        //System.out.println("LevelSelectionScene::onLevelButtonPressed()-Selection:"+selection);
        _buttonSound.setVolume(20,20);
        _buttonSound.playAudio();
        // Creamos la escena nueva a saltar
        Scene boardScene = new GameplayScene(selection);
        // Le pasamos el engine
        boardScene.init(_engine);
        // Le decimos al engine que cambie de escena.
        _engine.setScene(boardScene);
    }

    /**
     * Metodo "callback" que vuelve al main menu scene.
     */
    private void onCloseButtonPressed()
    {
        //System.out.println("LevelSelectionScene::onCloseButtonPressed()");
        _buttonSound.setVolume(30,30);
        _buttonSound.playAudio();
        // Creamos la escena nueva a saltar
        Scene mainScene = new MainMenuScene();
        // Le pasamos el engine
        mainScene.init(_engine);
        // Le decimos al engine que cambie de escena.
        _engine.setScene(mainScene);
    }

    private void drawSceneWireFrame(GraphicsInterface g)
    {

    }
}
