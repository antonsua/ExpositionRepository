#include "RenderComponent.h"

#include "Container.h"
#include "Utilities\Vector3.h"
#include "TransformComponent.h"

#include <RenderSystem.h>
#include "ComponentFactory.h"

//CREATE_REGISTER(Render);

RenderComponent::RenderComponent(Container* e) {
	_name = "Render";
	_parent = e;
}

RenderComponent::~RenderComponent() {
	_node = nullptr;
	_NameOfTheMesh.clear();
}

void RenderComponent::Init(std::unordered_map<std::string, std::string>& param) {
	_NameOfTheMesh = param.at("Mesh");
	_Material = param.at("Material");
	_parent->getRSystem()->addOgreEntity(_parent->GetEntityName(), _NameOfTheMesh, _Material);

	// Le cambiamos al nodo la posicion segun el transform
	TransformComponent* tComp = static_cast<TransformComponent*>(_parent->getComponent("Transform"));
	_parent->setPos(*tComp->GetPosition());

	_parent->getNode()->pitch(Ogre::Radian(tComp->GetRotation()->x * 3.14 / 180));
	_parent->getNode()->yaw(Ogre::Radian(tComp->GetRotation()->y * 3.14 / 180));
	_parent->getNode()->roll(Ogre::Radian(tComp->GetRotation()->z * 3.14 / 180));
}

std::string RenderComponent::getMeshName() {
	return _NameOfTheMesh;
}

// Ogre_Node
Ogre::SceneNode* RenderComponent::getOgreNode() {
	return _node;
}

void RenderComponent::setOgreNode(Ogre::SceneNode* n) {
	_node = n;
}