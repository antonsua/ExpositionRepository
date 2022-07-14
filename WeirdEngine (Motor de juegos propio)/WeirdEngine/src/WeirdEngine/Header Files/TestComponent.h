#pragma once
//***********!ADVERTENCIA¡***********
// Clase utilizada para testear el funcionamiento del proyecto.
//***********************************
#include "Component.h"
#include <string>

class Container;
class EntityC;

class TestComponent : public Component {
public:
	TestComponent(EntityC* e);
	~TestComponent() {};
	void Init(std::unordered_map<std::string, std::string>& param);

	// Implementar la que sea necesaria
	void update(Container* c, float time) {};

	//Receive implementation
	void receive(Container* c, const msg::Message& msg) {};

	void Debug();

private:
	float f;
	int intArray[3];
	std::string s;
	bool b;
};