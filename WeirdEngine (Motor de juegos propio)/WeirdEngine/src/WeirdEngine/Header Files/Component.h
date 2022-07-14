#pragma once

#include <string>
#include <unordered_map>
#include "Messages_defs.h"

namespace msg {
	struct Message;
}

class Container;

class Component {
public:
	Component() {};
	~Component() {};

	virtual void Init(std::unordered_map<std::string, std::string>& param) = 0;

	// By default components do not do anything when receiving a message.
	// Only those interested will implement this method
	virtual void receive(Container* c, const msg::Message& msg) = 0;

	bool getName(std::string name);

	// A implementar por cada componente
	// Update
	virtual void update(Container* c, float time) = 0;
	bool hasUpdate();
	void setUpdate(); //Lo activa como UpdateComponent

protected:
	std::vector<std::string> GetWords(std::string& s);

	std::string _name;
	Container* _parent;

	bool uc;
};