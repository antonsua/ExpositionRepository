#pragma once

#include <string>
#include <unordered_map>

#include "Component.h"
#include <InputListener.h>

namespace msg {
	struct Message;
}

class Container;

class InputComponent : public Component {
public:
	InputComponent(Container* e);
	~InputComponent() {};

	virtual void Init(std::unordered_map<std::string, std::string>& param) = 0;

	// By default components do not do anything when receiving a message.
	// Only those interested will implement this method
	virtual void receive(Container* c, const msg::Message& msg) = 0;

	// Update
	virtual void update(Container* c, float time) = 0;

	virtual InputKeyListener* getKeyListener() = 0;
	virtual InputMouseListener* getMouseListener() = 0;

	Container* getParent() const;

protected:
	InputKeyListener* _keyListener;
	InputMouseListener* _mouseListener;
};