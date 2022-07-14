package es.ucm.moviles.logica;

import java.util.List;
import java.util.Random;

import es.ucm.moviles.engineinterface.Engine;
import es.ucm.moviles.engineinterface.FontInterface;
import es.ucm.moviles.engineinterface.GraphicsInterface;
import es.ucm.moviles.engineinterface.ImageInterface;
import es.ucm.moviles.engineinterface.InputInterface;
import es.ucm.moviles.engineinterface.Position;
import es.ucm.moviles.engineinterface.RGBColor;
import es.ucm.moviles.engineinterface.ResourcesInterface;
import es.ucm.moviles.engineinterface.ResourceManagerInterface;
import es.ucm.moviles.engineinterface.Scene;
import es.ucm.moviles.engineinterface.TouchEvent;

/**
 * Implementa la escena con el tablero.
 */
public class GameplayScene implements Scene
{
    /* ---------------------------------
     * VARIABLES DE CLASE
     * ---------------------------------
     */
    // Instancias importantes
    Engine _engine;
    InputInterface _input;
    ResourcesInterface _resources;
    private GraphicsInterface _graphics;
    ResourceManagerInterface _fontManager;
    ResourceManagerInterface _imageManager;
    // TABLERO
    private BoardObj _board;
    private int _boardSize;

    // Variables de imagenes
    private ImageInterface _closeImage;
    private ImageInterface _eyeImage;
    private ImageInterface _historyImage;
    private ImageInterface _lockImage;

    // Variables de fuentes;
    private FontInterface _font1;
    private FontInterface _font2;

    // Colores
    RGBColor _black;
    RGBColor _blue;
    RGBColor _red;
    RGBColor _lightGrey;

    // String
    String _boardSizeText;

    // Botones
    private ImageButton _closeButton;
    private ImageButton _hintButton; //eye image
    private ImageButton _undoButton; //history image
    private TextButton _hintTextButton; // Contiene el texto de la pista.

    // Condicion de victoria
    private boolean _boardCompleted;
    private float _winAcuTime;    // Variable que acumula tiempo hasta el timeout.
    private float _winAcuTimeOut; // Cuanto duramos en la pantalla de victoria
    private double _completionRate; // valor mostrado de 0 a 100%
    private StringBuilder _completionTextBuilder;
    private String _completionRateText;
    private String _winText; // Se elige entre una serie de opciones
    private boolean winJustOnce; //Para que solo se inicie la victoria una vez

    // Texto complecion
    private int _greysAtStart;
    private int _greyInBoard;
    private int _positionsSet; //greysAtStart-greyInBoard

    // Pistas
    private boolean _displayHint;
    private Position _hintPos; // Posicion en TABLERO del tile en coordenadas tablero
    private Position _hintTilePos; // Posicion LOGICA del centro del tile a marcar por la pista
    private int _nextHintDEVTEST; // Variable de desarrollo, eliminar.
    private Tip _hint;
    private Position hintTextPos;


    //FADE
    private static final float FADEIN_ANIMATION_DURATION = 1.5f;
    private static final float FADEOUT_ANIMATION_DURATION = 1.5f;
    private boolean _fadingIn = false;
    private boolean _fadingOut = false;

    private ColorAnimation _fadeAnimation;

    // FadeOut
    private boolean _endingScene = false;

    /* -------------------------------------
     * METODOS DE CLASE
     * -------------------------------------
     */

    /**
     * Constructora.
     * Recibe y almacena el tamaño de tablero que debe generarse en su interior.
     * Inicializa el vector de arrays.
     * @param boardSize int tamaño de tablero a generar.
     */
    public GameplayScene(int boardSize)
    {
        // Almacena el tamaño en una variable interna
        _boardSize = boardSize;
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
        _fontManager = engine.getFontManager();
        _imageManager = engine.getImageManager();
        _graphics = engine.getGraphics();

        // BOARD
        // Llama a generar el tablero
        _board = new BoardObj(_boardSize);
        _board.addObserver(new BoardObj.BoardObserver() {
            @Override
            public void onTileClicked(Tile tile) {
                _displayHint = false;
            }

            @Override
            public void onTileChanged(Tile tile) {

            }
        });
        _boardCompleted = false; //Para el texto de tablero completado
        winJustOnce = true;
        //_OLD_board = new OLD_Board(_boardSize, _resources);
        //_OLD_board.createSolution();
        //_OLD_board.createPlayerBoard();

        // Carga de recursos especificos de esta escena en las variables internas
        loadSceneResources();

        _fadingOut = true;
        _fadeAnimation = new FadeOutAnimation(RGBColor.WHITE, FADEOUT_ANIMATION_DURATION);

    }

    /**
     * Metodo para cargar los recursos que desee la escena utilizando el gestor de recursos.
     * Aunque se llame a un load no signifique que cargue varias veces el recurso en el gestor
     * sino que primero comprueba si dicho recurso existe en el diccionario y sino lo carga.
     */
    void loadSceneResources()
    {
        // Fonts
        // JosefinSans->Identificador: "Josefin Sans Bold"
        _font1= (FontInterface) _fontManager.getResource("JosefinSans-Bold.ttf", 12,0);
        if(_font1 == null)
            System.err.println("No se ha podido cargar JosefinSans.Bold.ttf");

        // Molle-Regular->Identificador: "Molle Regular"
        _font2 = (FontInterface) _fontManager.getResource("Molle-Regular.ttf", 12,0);
        if(_font2 == null)
            System.err.println("No se ha podido cargar Molle-Regular.ttf");

        // Images
        // Close Image
        _closeImage = (ImageInterface) _imageManager.getResource("close.png", 0 ,0);
        if(_closeImage == null)
            System.err.println("No se ha podido cargar close.png");
        // Eye Image
        _eyeImage = (ImageInterface) _imageManager.getResource("eye.png", 0 ,0);
        if(_eyeImage == null)
            System.err.println("No se ha podido cargar eye.png");
        // History Image
        _historyImage = (ImageInterface) _imageManager.getResource("history.png", 0 ,0);
        if(_historyImage == null) System.err.println("No se ha podido cargar history.png");
        // Lock Image
        _lockImage = (ImageInterface)_imageManager.getResource("lock.png", 0,0);
        if(_lockImage == null) System.err.println("No se ha podido cargar lock.png");
        TileObj.setLockImage(_lockImage);



        // Colores
        _black = new RGBColor(0,0,0);
        _blue = new RGBColor(100,175,255);
        _red = new RGBColor(255,80,80);
        _lightGrey = new RGBColor(180,180,180);

        // Texto
        _boardSizeText = (_boardSize >= 4 && _boardSize <= 9) ?
                _boardSize + "x" + _boardSize :
                "Error: Invalid Size";

        // Botones
        Position closeButtonPos = new Position(90,550);
        _closeButton = new ImageButton(closeButtonPos, _closeImage, 25, 25);
        Position undoButtonPos = new Position(190,550);
        _undoButton = new ImageButton(undoButtonPos, _historyImage, 25, 25);
        Position hintButtonPos = new Position(290,550);
        _hintButton = new ImageButton(hintButtonPos, _eyeImage, 25, 25);
        Position hintTextPos = new Position(10,80);
        _hintTextButton = new TextButton(hintTextPos, "Hints Text", _font1,42f, 380, 90);

        // Inicializacion de variables
        _boardCompleted = false;
        _winAcuTimeOut = 3f; // 3 segundos

        _winAcuTime = 0f;
        _greysAtStart = _board.undefinedAtStart;
        _greyInBoard = _board.currentUndefined;
        //_greyInBoard = _OLD_board.countGreysInBoard(_OLD_board.getPlayerBoard());
        _completionRate = (100f/(float)_greysAtStart);
        _positionsSet = _greysAtStart - _greyInBoard;
        // el % es _completionRate*_positionsSet.
        _completionTextBuilder = new StringBuilder();
        _displayHint = false;
        _nextHintDEVTEST = 1; // VARIABLE DE DESARROLLO - ELIMINAR
    }

    /* -----------------------------------------
     * METODOS HEREDADOS de engineInterface::Scene
     * -----------------------------------------
     */
    /**
     * Llamado cada frame.
     * Implementar aqui la lógica que necesita actualizarse.
     * @param deltaTime El tiempo (en segundos) desde el último frame
     */
    @Override
    public void onUpdate(float deltaTime)
    {
        if(_fadingOut)
        {
            _fadeAnimation.update(deltaTime);
            if(_fadeAnimation.hasEnded())
            {
                _fadingOut = false;
                _fadeAnimation = null;
            }
        }
        else if(_fadingIn)
        {
            _fadeAnimation.update(deltaTime);
            if(_fadeAnimation.hasEnded())
            {
                _fadingIn = false;
                _fadeAnimation = null;
            }
        }
        // Victoria
        _boardCompleted = _board.isSolved();
        if (_boardCompleted && winJustOnce)
            onBoardCompleted();
        if(_boardCompleted) {
            _completionTextBuilder.delete(0,_completionTextBuilder.length());
            _completionTextBuilder.append(100); //Al estar completado no actualiza el resto de updatey queda en el estado anterior
            _completionTextBuilder.append("%");
            displayWin(deltaTime);
        }
        else
        {
            // Gestion de eventos
            handleEvents(_input.getTouchEvents());

            // Logica Interna
            //   -Update % completado
            _greyInBoard = _board.currentUndefined;
            _positionsSet = _greysAtStart - _greyInBoard;
            _completionTextBuilder.delete(0,_completionTextBuilder.length());

            if(_positionsSet == _greysAtStart)
                _completionTextBuilder.append(100); //Los redondeos, con muchos tiles de _size alto pueden llegar a perder 1 y quedarse en 99%
            else _completionTextBuilder.append((int)Math.floor(_completionRate*_positionsSet));

            _completionTextBuilder.append("%");
            _board.update(deltaTime);


            if(_greyInBoard == 0 && !_boardCompleted && !_displayHint)
            {
                onHintButtonPressed();
            }

            // Update de objetos del tablero
            //_OLD_board.onUpdate(deltaTime);
        }


    }

    /**
     * Llamado cada frame.
     * @param graphics Los gráficos activos
     */
    @Override
    public void onRender(GraphicsInterface graphics)
    {

        // Texto
        // Tamaño de tablero (mientras no estemos mostrando una pista)
        if (_boardCompleted){
            graphics.setFont(_font1);
            graphics.setColor(_black);
            graphics.setFontSize(60f);

            graphics.drawTextInLogicSpace(_winText, 50,80,true);
            _displayHint = false;
        }
        else if (!_displayHint)
        {
            graphics.setFont(_font1);
            graphics.setColor(_black);
            graphics.setFontSize(72f);
            graphics.drawTextInLogicSpace(_boardSizeText,150,80,true);
        }
        else
        {
            // Segun el valor almacenado en _hintNo, cambia el texto del hintTextButton y lo muestra
            graphics.setColor(_black);
            printHint();
            // Obtener centro del tile y su radio
            // Centro
            //BoardPosition hintedTilePos = hint.getTile().getBoardPosition();
            //_hintTilePos = getBoardPos(hintedTilePos.row(), hintedTilePos.col());
            // Radio
            // Pintar contorno para marcar elt ile

            //Position logicHintPos = _OLD_board.getTileLogicPosition(_OLD_board.getHintPos());
            //graphics.drawCircleInLogicSpace(logicHintPos.getX(), logicHintPos.getY(), (int) _OLD_board.getTileRadius());
        }

        // Tablero
        // Se puede renderizar la solucion para ver como se genera el tablero
        _board.render(graphics);
        //_OLD_board.onRender(graphics);
        //_board.onRenderSolution(graphics);

        // Completion Rate Text
        graphics.setFont(_font1);
        graphics.setColor(_lightGrey);
        graphics.setFontSize(20f);
        graphics.drawTextInLogicSpace(_completionTextBuilder.toString(), 185, 530, true);

        // Botones
        if (!_boardCompleted)
        {
            _closeButton.render(graphics);
            _undoButton.render(graphics);
            _hintButton.render(graphics);
        }
        if(_fadeAnimation != null)
        {
            graphics.setColor(_fadeAnimation.getColor());
            graphics.fillRectInLogicSpace(0,0, graphics.GetWidth(), graphics.GetHeight());
        }

    }

    /**
     * Metodo que gestiona los eventos recibidos por el motor.
     * @param events Lista de eventos desde el anterior ciclo.
     */
    private void handleEvents(List<TouchEvent> events)
    {
        boolean isMovement = false;
        if (!events.isEmpty())
        {
            for(TouchEvent event : events)
            {
                // Transformar las coordenadas del evento a coordenadas lógicas
                Position logicPos = _graphics.translateWindowToLogic(event.getPosX(), event.getPosY());
                if (event.getTouchType() == InputInterface.touchType.PRESSED)
                {
                    event.setPosX(logicPos.getX());
                    event.setPosY(logicPos.getY());

                    _board.handleEvent(event);
                    if(_closeButton.inside(logicPos))onCloseButtonPressed();
                    if(_hintButton.inside(logicPos)) onHintButtonPressed();
                    if(_undoButton.inside(logicPos)) onUndoButtonPressed();
                    if(_hintTextButton.inside(logicPos)) onHintTextButtonPressed();

                    if(_board.unselectedTileButNotNoticed){
                        _hint = null;
                        _board.unselectedTileButNotNoticed = false;
                        _displayHint = false;
                    }
                    /*switch(event.getTouchType())
                    {
                        case PRESSED:
                            // Tablero
                            //isMovement = _OLD_board.handleEvent(logicPos);
                            if (isMovement)
                            {
                                _displayHint = false;
                                //_greyInBoard = _OLD_board.countGreysInBoard(_OLD_board.getPlayerBoard());
                                _positionsSet = _greysAtStart - _greyInBoard;
                            }
                            // Botones
                            if(_closeButton.inside(logicPos))onCloseButtonPressed();
                            if(_hintButton.inside(logicPos)) onHintButtonPressed();
                            if(_undoButton.inside(logicPos)) onUndoButtonPressed();
                            if(_hintTextButton.inside(logicPos)) onHintTextButtonPressed();
                            break;
                        case RELEASED:
                            break;
                        case DRAGGED:
                            break;
                    }*/
                }
            }
        }
        if(_boardCompleted)
            onBoardCompleted();
        // Si ha habido un movimiento en el tablero
        // Comprobar si esta solucionado
        // Llamar al boardCompleted.
       /* if (isMovement && _OLD_board.isSolved(_OLD_board.getPlayerBoard()))
        {
          // Le decimos al board que cambie sus dots azules por numeros
          _OLD_board.displayCompletedBoard();
          // Activamos la lógica de completado.
          onBoardCompleted();
        }*/
    }

    /* ----------------------------
     * "CALLBACKS" de botones
     * ----------------------------
     */
    /**
     * Si se pulsa el boton close volvemos a selección de nivel
     */
    private void onCloseButtonPressed()
    {
        // Creamos la escena nueva a saltar
        Scene selectionScene = new LevelSelectionScene("Oh no");
        // Le pasamos el engine
        selectionScene.init(_engine);
        // Le decimos al engine que cambie de escena.
        _engine.setScene(selectionScene);
    }

    /**
     * Callback del boton Hint (ojo)
     * Llamará a la logica necesaria para mostrar una pista
     */
    private void onHintButtonPressed()
    {
        // Si ya se muestra una pista, simplemente ocultarla.
        if (_displayHint)
        {
            _displayHint = false;
            _hintPos = new Position(-1,-1);
            _hint = null;
            _board.unselectTiles();
        }
        else
        {
            // Activamos el boolean para avisar al render
            // Pasara a false si:
            //   - Se clica sobre el hint mostrado [DONE]
            //   - Se clica sobre el boton hint. [DONE]
            //   - Se clica en una tile no predefinida por el tablero. [DONE]
            // Preguntarle al board que pista mostrar
            //_OLD_board.searchHint(_OLD_board.getPlayerBoard());
            _hint = _board.getTip();
            if (_hint != null)
            {
                _displayHint = true;
                _board.selectTile(_hint.getTile());
            }
            else
            {
                _displayHint = false;
                _board.unselectTiles();
                _hint = null;
                //System.out.println("No hay pistas que mostrar");
            }
        }
    }

    /**
     * Si mientras se esta mostrando el texto de una pista, este se pulsa
     * se cerrará la pista.
     */
    private void onHintTextButtonPressed()
    {
        if (_displayHint && !_boardCompleted)
        {
            _displayHint = false;
            _board.unselectTiles();
        }

    }

    /**
     * Callback del boton Undo (history)
     * Llamará a la logica necesaria para deshacer un movimiento
     */
    private void onUndoButtonPressed()
    {
        _board.undoMove();
    }

    /* -------------------------------------
     * "Callbacks" Logicos
     * -------------------------------------
     */
    /**
     * Llamado al completar el tablero para establecer las
     * variables relacionadas con la condicion de victoria.
     */
    private void onBoardCompleted()
    {
        if(winJustOnce) {
            // Establecemos la variable de condición de victoria a true.
            setRandomWinMessage();
            _boardCompleted = true;
            // Se hace tambien en el init, pero por si acaso.
            _winAcuTime = 0f;
            _winAcuTimeOut = FADEIN_ANIMATION_DURATION;
            winJustOnce = false;

            _fadingIn = true;
            _fadeAnimation = new FadeInAnimation(RGBColor.WHITE, FADEIN_ANIMATION_DURATION);

        }
    }

    /* ------------------------------------
     * LOGICA INTERNA
     * ------------------------------------
     */

    /**
     * Metodo interno que calcula el tiempo que mostraremos el letrero de victoria
     * @param deltaTime float
     */
    private void displayWin(float deltaTime)
    {
        // Acumulamos el tiempo
        _winAcuTime += deltaTime;

        // Si superamos el TimeOut establecido
        if (_winAcuTime > _winAcuTimeOut)
        {
            // Reseteo de variables
            _winAcuTime = 0f;
            _boardCompleted = false;

            // Llamada a cerrar el board
            closeBoardAfterWin();
        }
    }

    /**
     * Vuelve a la seleccion de nivel
     * Llamado tras completar el tablero y mostrar victoria durante _winAcuTimeOut
     */
    private void closeBoardAfterWin()
    {
        // Creamos la escena nueva a saltar
        Scene selectionScene = new LevelSelectionScene(_winText);
        // Le pasamos el engine
        selectionScene.init(_engine);
        // Le decimos al engine que cambie de escena.
        _engine.setScene(selectionScene);
    }

    /**
     * Establece un mensaje de victoria seleccionado al azar entre las opciones disponibles.
     */
    private void setRandomWinMessage()
    {
        final String[] cheers =
        {
            "Outstanding!", " Fabulous! ",
            "  Dazzling! ", "Marvelous!",
            "   Super!   ", "Magnificent!",
            " Awesome!  ", " Excellent! ",
            "    Ojoo!   ", "  Brilliant!",
            "  Shazam!  ", " Well done! ",
            "       Yay!    "
        };
        _winText = cheers[new Random().nextInt(cheers.length)];
    }

    /* ---------------------------
     * GESTION DE PISTAS
     * ---------------------------
     */
    /**
     * Imprime en la cabecera de la escena el mensaje adecuado
     * para la pista establecida actualmente.
     */
    private void printHint()
    {
        // Mostrar texto de la pista


        _graphics.setColor(_black);
        switch(_hint.getKind())
        {
            case CAN_BE_CLOSED:
                _hintTextButton.setFontSize(30f);
                _hintTextButton.setPosition(new Position(10, 80));
                _hintTextButton.setText("This number can see all its dots");
                _hintTextButton.render(_graphics);
                break;
            case MUST_BE_WALL:
                _hintTextButton.setFontSize(26f);
                _hintTextButton.setPosition(new Position(30, 70));
                _hintTextButton.setText("Looking further in one direction","   would exceed this number");
                _hintTextButton.render2lines(_graphics, 26);
                break;
            case MUST_BE_TILE:
                _hintTextButton.setFontSize(28f);
                _hintTextButton.setPosition(new Position(40, 70));
                _hintTextButton.setText("This dot is included", " in all solutions imaginable");
                _hintTextButton.render2lines(_graphics, 28);
                break;
            case ERROR_TOO_MANY_TILES:
                _hintTextButton.setFontSize(28f);
                _hintTextButton.setPosition(new Position(15, 80));
                _hintTextButton.setText("This number sees a bit too much");
                _hintTextButton.render(_graphics);
                break;
            case ERROR_NOT_ENOUGH_TILES_BUT_CLOSED:
                _hintTextButton.setFontSize(30f);
                _hintTextButton.setPosition(new Position(20, 80));
                _hintTextButton.setText("This number can't see enough");
                _hintTextButton.render(_graphics);
                break;
//            case CLOSED_MUST_BE_WALL:
//                _hintTextButton.setFontSize(32f);
//                _hintTextButton.setPosition(new Position(40, 70));
//                _hintTextButton.setText("This one should be easy...");
//                _hintTextButton.render(_graphics);
//                break;
            case CLOSED_MUST_BE_WALL:
                _hintTextButton.setFontSize(28f);
                _hintTextButton.setPosition(new Position(50, 70));
                _hintTextButton.setText("A blue dot should always","   see at least one other");
                _hintTextButton.render2lines(_graphics, 28);
                break;
//            case hint8OneDirectionLeft:
//                _hintTextButton.setFontSize(28f);
//                _hintTextButton.setPosition(new Position(40, 70));
//                _hintTextButton.setText("Only one direction remains", " for this number to look in");
//                _hintTextButton.render2lines(_graphics, 28);
//                break;
            case ERROR_NOT_ENOUGH_TILES_BUT_OPEN:
                _hintTextButton.setFontSize(30f);
                _hintTextButton.setPosition(new Position(10, 80));
                _hintTextButton.setText("This number will not be", "able to see all its dots...");
                _hintTextButton.render(_graphics);
            default:
                _graphics.drawTextInLogicSpace("No Hints to show.", 50, 80, true);
                break;
        }
    }
}