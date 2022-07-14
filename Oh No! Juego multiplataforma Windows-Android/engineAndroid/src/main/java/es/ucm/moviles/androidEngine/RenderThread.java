package es.ucm.moviles.androidEngine;

import android.graphics.Canvas;
import android.view.SurfaceView;

import es.ucm.moviles.androidEngine.EngineAndroid;
import es.ucm.moviles.androidEngine.GraphicsAndroid;
import es.ucm.moviles.engineinterface.Scene;

public class RenderThread implements Runnable {

    EngineAndroid _engine;
    Scene _scene;
    SurfaceView _v;
    Canvas _c;
    Thread _thread;
    volatile boolean _running = false;

    public RenderThread(SurfaceView v){
        super();
        _v = v;
    }

    @Override
    public void run() {
        if (_thread != Thread.currentThread()) {
            // ¿¿Quién es el tuercebotas que está llamando al
            // run() directamente?? Programación defensiva
            throw new RuntimeException("run() should not be called directly");
        }

        GraphicsAndroid gAnd = (GraphicsAndroid) _engine.getGraphics();
        while(_running && _v.getWidth() ==0);
        gAnd.calculateScaleVars();
        int b =0;
        _scene.init(_engine);

        // Establecemos el color de limpiado
        gAnd.setClearColor(255,255,255);// Pink(255, 192, 203);

        // Bucle principal
        while(_running) // OJO! El compilador optimizará el código al no ver que la propia clase modifica su variable
        {
            while (!_v.getHolder().getSurface().isValid())
                ;
            Canvas canvas = _v.getHolder().lockCanvas();
            gAnd.setGraphics(canvas);
            // Limpiamos la ventana
            gAnd.clear();

            // Pintamos las bandas blancas
            gAnd.drawWhiteBounds();

            // Llamamos a los metodos Update y Render
            _scene.onUpdate(0.01668f);
            _scene.onRender(gAnd);

            _v.getHolder().unlockCanvasAndPost(canvas);
        }
    }
    public void throwThread(){
        _thread = new Thread(this);
        _thread.start();
    }

    public void resume() {
        if (!_running) {
            // Solo hacemos algo si no nos estábamos ejecutando ya
            // (programación defensiva, nunca se sabe quién va a
            // usarnos...)
            _running = true;
            // Lanzamos la ejecución de nuestro método run()
            // en una hebra nueva.
            _thread = new Thread(this);
            _thread.start();
        } // if (!_running)
    }

    public void pause() {
        if (_running) {
            _running = false;
            while (true) {
                try {
                    _thread.join();
                    _thread = null;
                    break;
                } catch (InterruptedException ie) {
                    // Esto no debería ocurrir nunca...
                }
            } // while(true)
        } // if (_running)
    }

    public void setScene(Scene s)
    {
        _scene = s;
    }
    public void setCanvas(Canvas c)
    {
        _c = c;
    }
    public void setEngine(EngineAndroid e){_engine = e;}
}
