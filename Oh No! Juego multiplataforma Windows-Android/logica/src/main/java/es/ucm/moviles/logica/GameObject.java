package es.ucm.moviles.logica;

import es.ucm.moviles.engineinterface.GraphicsInterface;
import es.ucm.moviles.engineinterface.TouchEvent;

public abstract class GameObject {
    void update(float deltaTime){}
    void render(GraphicsInterface g){}
    void handleEvent(TouchEvent e){}
}
