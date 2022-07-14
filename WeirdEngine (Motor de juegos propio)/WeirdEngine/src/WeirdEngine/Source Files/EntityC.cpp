#include "EntityC.h"
#include "Messages_defs.h"
#include "Utilities\Vector3.h"

#include <RenderSystem.h>
#include <iostream>

EntityC::EntityC(std::string name, WEManager* wem) {
	_entName = name;
	_weM = wem;
	_active = true;
}

EntityC::~EntityC() {}

// Get Managers
WEManager* EntityC::getWEManager() const {
	return _weM;
}

RenderSystem* EntityC::getRSystem() const {
	return _weM->renderSystem;
}

PhysicsEngine* EntityC::getPhysics() const {
	return _weM->py;
}

//------------------------
// Ogre SceneNode Get
Ogre::SceneNode* EntityC::getNode() const {
	return _weM->renderSystem->getSceneNode(_entName);
}

// Posicion
void EntityC::setPos(const Vector3& p) {
	Ogre::Vector3 pos = { p.x, p.y, p.z };
	_weM->renderSystem->setEntityPos(_entName, pos);
}

const Vector3 EntityC::getPosition() const {
	Ogre::Vector3 pos = _weM->renderSystem->getEntityPos(_entName);
	Vector3 v = { pos.x, pos.y, pos.z };
	return v;
}

//Desactiva la entidad y su nodo de Ogre
void EntityC::setActive(bool a) {
	_active = a;
	_weM->renderSystem->getSceneNode(_entName)->setVisible(_active);
}

bool EntityC::isActive() const {
	return _active;
}

std::string EntityC::GetEntityName() const {
	return _entName;
}