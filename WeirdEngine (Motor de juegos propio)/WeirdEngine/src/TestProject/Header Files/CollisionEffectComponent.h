#pragma once
#include <Component.h>
#include <ctime>
#include <cstdlib>

class Container;
class Vector3;
class PhysicsComponent;

class CollisionEffectComponent : public Component
{
public:
	CollisionEffectComponent(Container* e);
	~CollisionEffectComponent() {};
	void Init(std::unordered_map<std::string, std::string>& param);

	void update(Container* c, float time);
	
	void doEffect();
	void undoEffect();

	void receive(Container* c, const msg::Message& _msg) {};

protected:
	PhysicsComponent* _pc;
	double effectTime = 3;
	bool buffActive = false;
private:
	double secondsPassed;
	clock_t startTime;
};

