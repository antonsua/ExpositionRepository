#pragma once

#include <InputListener.h>
#include "InputComponent.h"

class WEInputListener : public InputKeyListener {
public:
	WEInputListener(Container *owner);
	~WEInputListener();

	// Teclas
	bool keyPressed(const OIS::KeyEvent& ke);
	bool keyReleased(const OIS::KeyEvent& ke);

private:
	Container* _owner;
};

class PlaySceneInputComponent : public InputComponent {
public:
	PlaySceneInputComponent(Container* e);
	~PlaySceneInputComponent() {};
	void Init(std::unordered_map<std::string, std::string>& param);

	// Implementar la que sea necesaria
	void update(Container* c, float time) {};

	//Receive implementation
	void receive(Container* c, const msg::Message& msg) {};

	virtual WEInputListener* getKeyListener();
	virtual InputMouseListener* getMouseListener();

private:
	WEInputListener* _listener;
	OIS::KeyCode PauseMenu;
	//OIS::KeyCode PauseMenu;
};