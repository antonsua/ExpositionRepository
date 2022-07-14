#pragma once
#include "Component.h"

#include "Utilities\Vector3.h"
#include <string>

class Container;
class RenderSystem;

class AttachCameraToEntComponent : public Component {
public:
	AttachCameraToEntComponent(Container* e);
	~AttachCameraToEntComponent();

	void Init(std::unordered_map<std::string, std::string>& param);

	// Es necesaria para actualizar la pos
	void update(Container* c, float time);

	//Receive implementation
	void receive(Container* c, const msg::Message& msg);


private:
	RenderSystem* rSystem;
};
