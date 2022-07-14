#pragma once
#include "RotateInputComponent.h"

#include "Utilities\vector4.h"
#include "Container.h"
#include "OgreCamera.h"

#include "ComponentFactory.h"

//CREATE_REGISTER(RotateInput);

RotateInputListener::RotateInputListener(Container* owner) {
	_ow = owner;
}

RotateInputListener::~RotateInputListener() {}

bool RotateInputListener::mouseMoved(const OIS::MouseEvent& me) {
	if (_ow->hasComponent("RotateInput")) {
		float actPosx = me.state.X.rel;
		float actPosy = me.state.Y.rel;

		Ogre::Real tpitch = _ow->getWEManager()->getCam()->getParentNode()->getOrientation().getPitch().valueRadians();
		Ogre::Real tpitchchange = -me.state.Y.rel * 0.01f;
		Ogre::Real tyawchange = -me.state.X.rel * 0.10f;

		Ogre::Real tnewpitch = tpitch + tpitchchange;
		
		if ((tnewpitch <= 1.2f) && (tnewpitch >= -1.5f)) {
			tpitchchange = tpitchchange * 6;
			_ow->getWEManager()->getCam()->getParentNode()->pitch(Ogre::Degree(tpitchchange));
		}
		_ow->getNode()->yaw(Ogre::Degree(tyawchange));
	}
	return true;
}

bool RotateInputListener::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id) {
	return true;
}

bool RotateInputListener::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id) {
	return true;
}

////////////////////////COMPONENT////////////////////////////////////////
RotateInputComponent::RotateInputComponent(Container* e): InputComponent(e) {
	_listener = new RotateInputListener(e);
	_name = "RotateInput";
	_parent = e;
	_parent->getWEManager()->addMouseListener(_listener, _name);
}

void RotateInputComponent::Init(std::unordered_map<std::string, std::string>& param) {
}

void RotateInputComponent::receive(Container* c, const msg::Message& msg) {
	switch (msg.type_) {
	case msg::SWITCH_COMP:
		_parent->activeComponent(_name);
		break;
	case msg::SCENE_OVER:
		_parent->getWEManager()->removeMouseListener(_name);
		break;
	default:
		break;
	}
}

InputKeyListener* RotateInputComponent::getKeyListener() {
	return nullptr;
}

RotateInputListener* RotateInputComponent::getMouseListener() {
	return _listener;
}
