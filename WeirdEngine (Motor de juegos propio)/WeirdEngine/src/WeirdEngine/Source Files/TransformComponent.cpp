#include "TransformComponent.h"
#include "ComponentFactory.h"
#include <iostream>

CREATE_REGISTER(Transform);

TransformComponent::TransformComponent(Container* e) {
	_name = "Transform";
	_parent = e;
}

void TransformComponent::Init(std::unordered_map<std::string, std::string>& param) {
	std::vector<std::string> aux = GetWords(param.at("positionT"));
	position.x = std::stof(aux[0]);
	position.y = std::stof(aux[1]);
	position.z = std::stof(aux[2]);
	aux.clear();

	aux = GetWords(param.at("scaleT"));
	scale.x = std::stof(aux[0]);
	scale.y = std::stof(aux[1]);
	scale.z = std::stof(aux[2]);

	aux.clear();
	aux = GetWords(param.at("rotationT"));
	rotation.x = std::stof(aux[0]);
	rotation.y = std::stof(aux[1]);
	rotation.z = std::stof(aux[2]);
	aux.clear();
}

//GETTERS
Vector3* TransformComponent::GetPosition() { return &position; }
Vector3* TransformComponent::GetRotation() { return &rotation; }
Vector3* TransformComponent::GetScale() { return &scale; }

//SETTERS
void TransformComponent::SetPosition(Vector3 v_) { position = v_; }
void TransformComponent::SetPosition(float x_, float y_, float z_) { position = Vector3(x_, y_, z_); }

void TransformComponent::SetRotation(Vector3 v_) { rotation = v_; }
void TransformComponent::SetRotation(float x_, float y_, float z_) { rotation = Vector3(x_, y_, z_); }

void TransformComponent::SetScale(Vector3 v_) { scale = v_; }
void TransformComponent::SetScale(float x_, float y_, float z_) { scale = Vector3(x_, y_, z_); }