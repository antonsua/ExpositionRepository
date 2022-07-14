#pragma once

#include <InputListener.h>
#include "InputComponent.h"
class Vector3;

class EntityC;

class PlayerInputListener : public InputKeyListener {
public:
	PlayerInputListener(Container *owner);
	~PlayerInputListener();

	// Teclas
	bool keyPressed(const OIS::KeyEvent& ke);
	bool keyReleased(const OIS::KeyEvent& ke);

	Container* _owner;
private:

};

//InputComponent es la clase base de todos los componentes de Input
class PlayerInputComponent : public InputComponent {
public:
	PlayerInputComponent(Container* e);
	~PlayerInputComponent() {};
	void Init(std::unordered_map<std::string, std::string>& param);

	// Implementar la que sea necesaria
	void update(Container* c, float time) {};

	//Receive implementation
	void receive(Container* c, const msg::Message& msg) {};

	virtual PlayerInputListener* getKeyListener();
	virtual InputMouseListener* getMouseListener();

	//Esto está aquí por que necesito acceder a ella desde PlayerInputListener, solo hasta 
	//que se pueden usar mensajes
	
private:
	PlayerInputListener* _listener;
};