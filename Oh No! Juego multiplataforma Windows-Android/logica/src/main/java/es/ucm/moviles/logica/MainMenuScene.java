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

/**
 * Primera escena del juego.
 */
public class MainMenuScene implements Scene
{
    // Instancias importantes
    private Engine _engine;
    private InputInterface _input;
    private ResourcesInterface _resources;
    private GraphicsInterface _graphics;

    // Variables de imagenes
    private ImageInterface _q42Image;

    // Variables de fuentes;
    private FontInterface _font1; // Almacenará Josefin
    private FontInterface _font2; // Almacenará Molle

    // Colores
    private RGBColor _black;
    private RGBColor _lightGrey;

    // Botón
    private TextButton _playButton;
    //Audio
    private AudioInterface _playButtonSound;

    ResourceManagerInterface _fonts;
    ResourceManagerInterface _images;
    ResourceManagerInterface _audios;

    /**
     * Recibe el motor de juego especifico de la plataforma que lo ejecuta
     * y recoge en variables internas las instancias importantes de este.
     * Llama a cargar los recursos necesarios para esta escena.
     * @param engine Motor de juego de la plataforma que lo ha lanzado.
     */
    @Override
    public void init(Engine engine)
    {
        // Al ser la primera escena, se declara en MainActivity y su init se llama desde el MyView::run().

        // Recibimos el engine
        _engine = engine;
        _input = engine.getInput();
        _resources = engine.getResources();
        _graphics = engine.getGraphics();

        // Carga de recursos especificos de esta escena en las variables internas
        loadSceneResources();
    }

    /**
     * Metodo para cargar los recursos que desee la escena utilizando el gestor de recursos.
     * Aunque se llame a un load no signifique que cargue varias veces el recurso en el gestor
     * sino que primero comprueba si dicho recurso existe en el diccionario y sino lo carga.
     */
    void loadSceneResources()
    {
        boolean result;
        _fonts = _engine.getFontManager();
        _images = _engine.getImageManager();
        _audios = _engine.getAudioManager();
        // Fonts
        // JosefinSans->Identificador: "Josefin Sans Bold"
        _font1= (FontInterface) _fonts.getResource("JosefinSans-Bold.ttf", 12,0);
        if(_font1 == null)
            System.err.println("No se ha podido cargar JosefinSans.Bold.ttf");

        _font2 = (FontInterface) _fonts.getResource("Molle-Regular.ttf", 12,0);
        if(_font2 == null){
            System.err.println("No se ha podido cargar Molle Regular.ttf");
        }
        // Molle-Regular->Identificador: "Molle Regular"
        //result = _resources.loadFont("Molle-Regular.ttf", 12,0);
        //if (result) _font2 = _resources.getFont("Molle-Regular");
        //else System.out.println("No se ha podido cargar Molle-Regular.ttf");



        // Images
        // q42 Image
        _q42Image = (ImageInterface) _images.getResource("q42.png");
        if(_q42Image == null)
            System.err.println("No se ha podido cargar q42.png");

        // Colores
        _black = new RGBColor(0,0,0);
        _lightGrey = new RGBColor(180,180,180);

        // Boton
        Position textPos = new Position(130,300);
        _playButton = new TextButton(textPos,"Jugar",_font1,64f,350,200);

        //Audio
//        result = _resources.loadSourceAudio("button-3.wav");
//        if(result)_playButtonSound = _resources.getAudio("button-3");
//        else System.out.println("No se ha podido cargar button-3.wav");

        _playButtonSound = (AudioInterface) _audios.getResource("button.wav");
        if(_playButtonSound == null)
            System.err.println("No se ha podido cargar button.wav");
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
        // Logica interna
        // Update de Objetos
    }

    /**
     * Metodo para llamar a los renders
     * @param g motor grafico que contiene los metodos de renderizado.
     */
    @Override
    public void onRender(GraphicsInterface g)
    {
        // Cartel Oh No
        g.setColor(_black);
        g.setFont(_font2);
        g.setFontSize(100f);
        g.drawTextInLogicSpace("Oh no", 50,150, true);

        // Boton Jugar
        _playButton.render(_graphics);

        // Texto
        g.setColor(_lightGrey);
        g.setFont(_font1);
        g.setFontSize(16f);
        g.drawTextInLogicSpace("Un juego copiado a Q42", 120, 430, true);
        g.drawTextInLogicSpace("Creado por Martin Kool", 120, 460, true);

        // Imagen Q42
        g.drawImageInLogicSpace(_q42Image,180,480, 40,60);
    }

    /**
     * Metodo que gestiona los eventos recibidos por el motor.
     * @param events
     */
    private void handleEvents(List<TouchEvent> events)
    {

        // Mientras existan eventos
        if (!events.isEmpty())
        {
            // Por cada evento
            for(TouchEvent event : events)
            {
                // Transformar coordenadas evento a logicas.
                Position logicPosClick = _graphics.translateWindowToLogic(event.getPosX(), event.getPosY());
                // Si el click esta dentro del espacio lógico
                if (logicPosClick.getX() != -1 && logicPosClick.getY() != -1)
                {
                    switch(event.getTouchType())
                    {
                        case PRESSED:
                            if (_playButton.inside(logicPosClick)) onPlayButtonPressed();
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
     * Metodo que salta a la escena de seleccion de nivel
     */
    private void onPlayButtonPressed()
    {
        //System.out.println("MainMenuScene::onPlayButtonPressed()");
        _playButtonSound.setVolume(30,30);
        _playButtonSound.playAudio();
        // Creamos la escena nueva a saltar
        Scene levelSelection = new LevelSelectionScene("Oh no");
        // Le pasamos el engine
        levelSelection.init(_engine);

        // Le decimos al engine que cambie de escena.
        _engine.setScene(levelSelection);
    }
}
