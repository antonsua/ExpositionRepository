#include "PhysicsComponent.h"
#include "ComponentFactory.h"
#include "messages_defs.h"

#include <PhysicsEngine.h>
#include <iostream>

CREATE_REGISTER(Physics);

PhysicsComponent::PhysicsComponent(Container* e) {
	_name = "Physics";
	_parent = e;
	id = -1;
}

PhysicsComponent::~PhysicsComponent() {
	id = NULL;
}

void PhysicsComponent::Init(std::unordered_map<std::string, std::string>& param) {
	//Aux
	std::vector<std::string> aux;

	//Gravity
	if (param.at("gravity") == "true")
		gravity = true;
	else
		gravity = false;

	//CollSize
	aux = GetWords(param.at("collSize"));
	collSize = Vector3(std::stof(aux[0]),
		std::stof(aux[1]),
		std::stof(aux[2]));

	_py = _parent->getPhysics();
	id = _py->basicMesh(_parent->getNode(), btVector3(collSize.x, collSize.y, collSize.z), gravity, "null");
}

void PhysicsComponent::update(Container* c, float time)
{
}

void PhysicsComponent::receive(Container* c, const msg::Message& msg) {

}

int PhysicsComponent::GetID()
{
	return id;
}

Vector3 PhysicsComponent::GetScale()
{
	return collSize;
}

Vector3 PhysicsComponent::linearVelocity()
{
	return Vector3(_py->linearVelocity(id).getX(), _py->linearVelocity(id).getY(), _py->linearVelocity(id).getZ());
}

Vector3 PhysicsComponent::position()
{
	return Vector3(_py->position(id).getX(), _py->position(id).getY(), _py->position(id).getZ());
}

bool PhysicsComponent::HaveGravity()
{
	return gravity;
}

bool PhysicsComponent::isColliding()
{
	return _py->isColliding(id);
}

void PhysicsComponent::checkColliding()
{
	_py->checkColliding(id);
}

void PhysicsComponent::move(Vector3 dir)
{
	_py->changeVelocity(id, btVector3(dir.x, dir.y, dir.z));
}

void PhysicsComponent::push(Vector3 dir)
{
	_py->addForce(id, btVector3(dir.x, dir.y, dir.z));
}

void PhysicsComponent::moveComponent(Vector3 pos)
{
	_py->setPosition(id, btVector3(pos.x, pos.y, pos.z));
}