#pragma once

#include <OIS.h>

// Input Listener class to be used as callback class for InputManager
// Abstract class
// Handles Input events for keys
class InputKeyListener : public OIS::KeyListener {
public:
	InputKeyListener() {};
	~InputKeyListener() {};

	// Teclas
	virtual bool keyPressed(const OIS::KeyEvent& ke) = 0;
	virtual bool keyReleased(const OIS::KeyEvent& ke) = 0;

private:
	
};

// Input Listener class to be used as callback class for InputManager
// Abstract class
// Handles Input events for mouse
class InputMouseListener : public OIS::MouseListener {
public:
	InputMouseListener() {};
	~InputMouseListener() {};

	// Raton
	virtual bool mouseMoved(const OIS::MouseEvent& me) = 0;
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id) = 0;
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id) = 0;

private:

};