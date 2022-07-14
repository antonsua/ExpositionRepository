#pragma once
#include "Component.h"
#include <OgreVector.h>

#include "Utilities\Vector3.h"

class Container;

class TransformComponent : public Component {
public:
	TransformComponent(Container* e) ;
	~TransformComponent() {};
	void Init(std::unordered_map<std::string, std::string>& param);

	// Implementar la que sea necesaria
	void update(Container* c, float time) {};

	//Receive implementation
	void receive(Container* c, const msg::Message& msg) {};

	//Getters & Setters
	Vector3* GetPosition();
	Vector3* GetRotation();
	Vector3* GetScale();

	void SetPosition(Vector3 v_);
	void SetPosition(float x_, float y_, float z_);
	void SetRotation(Vector3 v_);
	void SetRotation(float x_, float y_, float z_);
	void SetScale(Vector3 v_);
	void SetScale(float x_, float y_, float z_);

private:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
};