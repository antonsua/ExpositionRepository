#pragma once
#include <Component.h>

class Container;
class Vector3;
class PhysicsComponent;

class PlayerMoveComponent : public Component {
public:
	PlayerMoveComponent(Container* e);
	~PlayerMoveComponent() {};
	void Init(std::unordered_map<std::string, std::string>& param);

	// Implementar la que sea necesaria
	void update(Container* c, float time);

	//Receive implementation
	void receive(Container* c, const msg::Message& _msg);

private:
	PhysicsComponent* _pc;
	Vector3* _velocity;
	bool slowedDown = false;
};