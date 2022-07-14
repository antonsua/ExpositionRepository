package es.ucm.moviles.androidEngine;

import android.content.Context;
import android.view.SurfaceView;

import es.ucm.moviles.engineinterface.GraphicsInterface;
import es.ucm.moviles.engineinterface.Engine;
import es.ucm.moviles.engineinterface.InputInterface;
import es.ucm.moviles.engineinterface.ResourceManagerInterface;
import es.ucm.moviles.engineinterface.ResourcesInterface;
import es.ucm.moviles.engineinterface.Scene;

public class EngineAndroid implements Engine
{
    //Atributos Propios
    private GraphicsAndroid _graphics;
    private Scene _scene;
    private SurfaceView _view;
    private RenderThread _rThread;
    private InputAndroid _input;
    private ResourcesAndroid _resources;
    private FontManagerAndroid _fonts;
    private ImageManagerAndroid _images;
    private AudioManagerAnd _audios;


    // Variables relacionadas con deltaTime
    // del bucle principal
    private long _lastFrameTime;    // momento del anterior Frame
    private long _currentFrameTime; // momento del Frame Actual
    private boolean _60FrameLock;   // Si True, funciona a 60FPS. Establecido en la constructora.

    public EngineAndroid(SurfaceView surf, Context cont, RenderThread r)
    {
        _rThread = r;
        _graphics = new GraphicsAndroid(surf);
        _graphics.setContext(cont);
        _input = new InputAndroid(surf);
        _resources = new ResourcesAndroid(cont, _graphics.getPaint());
        _view = surf;
        _resources.init();
        _fonts = new FontManagerAndroid();
        _fonts.Init(cont, _graphics.getPaint());
        _images = new ImageManagerAndroid();
        _images.Init(cont);
        _audios = new AudioManagerAnd();
        _audios.Init(cont);
    }

    public void setScene(Scene s)
    {
        _rThread.setScene(s);
    }

    @Override
    public ResourceManagerInterface getFontManager() {
        return _fonts;
    }

    @Override
    public ResourceManagerInterface getImageManager() { return _images;}

    @Override
    public ResourcesInterface getResources() {
        return _resources;
    }

    @Override
    public GraphicsInterface getGraphics() {
        return _graphics;
    }

    @Override
    public InputInterface getInput() {
        return _input;
    }

    @Override
    public AudioManagerAnd getAudioManager() {
        return _audios;
    }

}
