#pragma once

#include <string>
#include <OgreSceneNode.h>
#include "Observer.h"
#include "WEManager.h"

class RenderSystem;
class PhysicsEngine;
class InputManager;

class Vector3;

class EntityC : public Observer {
	friend class Container;
public:
	EntityC(std::string name, WEManager* wem);
	virtual ~EntityC();

	// Get Managers
	WEManager* getWEManager() const;
	RenderSystem* getRSystem() const;
	PhysicsEngine* getPhysics() const;

	Ogre::SceneNode* getNode() const;
	
	// Posicion
	const Vector3 getPosition() const;
	void setPos(const Vector3& p);

	// Activar/Desactivar
	void setActive(bool sw);
	bool isActive() const;

	//Getters y setters
	std::string GetEntityName() const;

private:
	// Puntero al nodo de la escena
	//Ogre::SceneNode* _Node = nullptr;

	std::string _entName;

	// Puntero al motor
	WEManager* _weM;

	// Inidica si la entidad esta activa
	bool _active;
};