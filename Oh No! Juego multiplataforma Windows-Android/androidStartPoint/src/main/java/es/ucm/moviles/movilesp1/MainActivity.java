package es.ucm.moviles.movilesp1;


import androidx.appcompat.app.AppCompatActivity;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.view.SurfaceView;

import es.ucm.moviles.androidEngine.EngineAndroid;
import es.ucm.moviles.androidEngine.RenderThread;
import es.ucm.moviles.engineinterface.Scene;
import es.ucm.moviles.logica.MainMenuScene;

public class MainActivity extends AppCompatActivity
{
    AssetManager _assetManager;
    RenderThread _rThread;
    // Instancia del pintado

    /**
     * OnCreate es un método que forma parte del ciclo de vida de Android
     * Siempre que sobreescribamos uno de estos métodos siempre tendremos que
     * llamar al método del padre mediante el super.Método().
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState); // Siempre llamar al método de la superclase
        getSupportActionBar().hide(); // Elimina la barra de arriba.

        //AssetManager : Gestor de recursos de Android
        _assetManager = this.getAssets(); //this es esta clase de la actividad: la ventana.


        // Instancia de View
        SurfaceView v = new SurfaceView(this);

        // Instancia de Thread
        _rThread = new RenderThread(v);

        // Instancia de Engine
        EngineAndroid engine = new EngineAndroid(v,this, _rThread);

        _rThread.setEngine(engine);
        Scene scene = new MainMenuScene();
        setContentView(v);

        _rThread.setScene(scene);
    }
    @Override
    protected void onResume() {

        // Avisamos a la vista (que es la encargada del active render)
        // de lo que está pasando.
        super.onResume();
        _rThread.resume();

    } // onResume

    @Override
    protected void onPause() {

        // Avisamos a la vista (que es la encargada del active render)
        // de lo que está pasando.
        super.onPause();
        _rThread.pause();

    } // onPause
    public AssetManager getAssetManager()
    {
        return _assetManager;
    }

}


/*
 * En Android la gestión de la ventana (Activity en android) se hace mediante
 * la clase AppCompatActivity.
 * Los componentes heredan de una superclase View que es el que tiene el
 * método de paint. En vez de generar un JFrame, se hace una clase View.
 *
 * Ciclo de vida de una actividad
 *      Created (onCreate)
 *      Started (onStart, onRestart) : Visible
 *      Resumed (onResume) : Visible
 *      Paused  (onPause) : Visible pero en segundo plano, sin input.
 *      Stopped (onStop)
 * Android no asegura las llamadas de onStop o onDestroy, ya que intenta no cerrar procesos.
 *
 *
 * Renderizado pasivo: al igual que en JAVA tenemos un renderizado pasivo llamando al onDraw de View.
 * Sin embargo va a 60 fps fijos. No a toda velocidad como pasaba con JFRAME.
 * Este proceso sucede en la hebra de UI.
 *
 * Renderizado activo: Hebra con nuestro bucle principal, en Java usabamos la hebra del main.
 * En Android necesitaremos crear una hebra en Java/Android (se hace igual).
 * Ver la implementación en el PcMain
 * Clase Thread, tiene toda la infraestructura para ejecutar un hilo
 *      run() -> en principio vacío y que podemos sobrescribir
 *      start() -> habla con el SO para generar una hebra nueva y empieza a ejecutar run()
 *      join() ->
 */
