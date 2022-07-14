package es.ucm.moviles.pcstartpoint;

import es.ucm.moviles.engineinterface.Scene;
import es.ucm.moviles.enginepc.EnginePC;
import es.ucm.moviles.logica.MainMenuScene;

/**
 * Clase que se encarga del arranque del motor de juego en PC. Mantener minimalista.
 */
public class PcLauncher
{
    /**
     * Constructora del main para PC.
    */
    public PcLauncher()
    {
    }

    /**
     * Método del cual se lanzará la ejecución en PC.
     * Genera una instancia del Engine de PC y de la interfaz Scene
     * Engine internamente instancia de Ventana (JFrame) y arranca el motor de pintado (Graphics)
     * Llamado por: usuario o entorno de desarrollo para iniciar la ejecución.
     * @param args argumentos recibidos en el comando de ejecución. No los usaremos.
     */
    public static void main(String[] args)
    {
        //System.out.println("1.- PcLauncher::main()");
        // Creamos la instancia del motor gráfico y le damos la ventana
        EnginePC _enginePc = new EnginePC();
        Scene scn = new MainMenuScene();//LevelSelectionScene();//MainMenuScene();//GameplayScene(3);
        _enginePc.setScene(scn);
        // Arranca la ventana y el hilo con el bucle de renderizado activo.
        _enginePc.init("OhNo!", 400, 600);
        // Pasamos el motor a la escena una vez este ha inicializado los modulos de Input, Resources y Graphics.
        scn.init(_enginePc);
        // Inicializamos el bucle principal
        _enginePc.runMainLoop();
    }
}