#pragma once

#include "InputComponent.h"
class Vector3;

class RotateInputListener : public InputMouseListener {
public:
	RotateInputListener(Container* owner);
	~RotateInputListener();

	virtual bool mouseMoved(const OIS::MouseEvent& me);
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);
private:
	float xMousePrev=0.0f;
	float yMousePrev=0.0f;
	float cameraSpeed = 1.0f;
	Container* _ow;
	float degree = 1;
};

class RotateInputComponent :public InputComponent {
public:
	RotateInputComponent(Container* e);
	~RotateInputComponent() {};

	void Init(std::unordered_map<std::string, std::string>& param);

	// Implementar la que sea necesaria
	void update(Container* c, float time) {};

	//Receive implementation
	void receive(Container* c, const msg::Message& msg);

	virtual InputKeyListener* getKeyListener();
	virtual RotateInputListener* getMouseListener();

	//Esto est� aqu� por que necesito acceder a ella desde PlayerInputListener, solo hasta 
	//que se pueden usar mensajes

private:
	RotateInputListener* _listener;
};
