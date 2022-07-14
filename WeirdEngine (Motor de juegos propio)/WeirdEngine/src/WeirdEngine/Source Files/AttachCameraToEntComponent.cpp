#include "AttachCameraToEntComponent.h"

#include <RenderSystem.h>

#include "messages_defs.h"
#include "Utilities\Vector4.h"

#include "ComponentFactory.h"

//CREATE_REGISTER(AttachCameraToEnt);

AttachCameraToEntComponent::AttachCameraToEntComponent(Container* e) {
	_name = "AttachCameraToEnt";
	_parent = e;
	rSystem = e->getWEManager()->getRenderSystem();

	rSystem->addCameraToEnt(e->GetEntityName());
	Vector4 c = { 0.2, 0.0, 0.2, 0.8 };
	rSystem->addVpToCam(Ogre::ColourValue(c.x, c.y, c.z, c.w));
}

AttachCameraToEntComponent::~AttachCameraToEntComponent() {}

void AttachCameraToEntComponent::Init(std::unordered_map<std::string, std::string>& param) {}

void AttachCameraToEntComponent::update(Container* c, float time) {}

void AttachCameraToEntComponent::receive(Container* c, const msg::Message& msg) {}