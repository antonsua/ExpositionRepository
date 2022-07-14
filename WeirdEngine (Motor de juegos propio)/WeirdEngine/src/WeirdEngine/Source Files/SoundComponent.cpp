#include "SoundComponent.h"
#include "ComponentFactory.h"

#include <AudioManager.h>

#include <iostream>

//CREATE_REGISTER(SoundComponent);

SoundComponent::SoundComponent(Container* e) {
	_name = "Sound";
	_parent = e;
	audioManager = _parent->getWEManager()->getAudioManager();
}

void SoundComponent::Init(std::unordered_map<std::string, std::string>& param) {
	//nombre
	audioName = param.at("name");
	fileName = param.at("filename");

	//volumen
	std::vector<std::string> aux;
	aux = GetWords(param.at("volume"));
	Vector3 collSize = Vector3(std::stof(aux[0]),
		std::stof(aux[1]) ,
		std::stof(aux[2]));
	volume = collSize.x + collSize.y * 0.1 + collSize.z * 0.01;

	//loop
	if (param.at("loop") == "0") loop = false;
	else loop = true;

	//playStart
	if (param.at("playStart") ==  "0") playStart = false;
	else playStart = true;

	//playEvent
	if (param.at("playEvent") == "0") playEvent = false;
	else playEvent = true;

	audioManager->createSound(audioName, fileName);
}

void SoundComponent::receive(Container* c, const msg::Message& msg) {
	switch (msg.type_) {
	case msg::SWITCH_COMP: {
		//_parent->activeComponent(_name);
		break;
	}
	case msg::SCENE_OVER: {
		audioManager->stop(ch);
		//audioManager->releaseChannel();
		break;
	}
	case msg::SCENE_START: {
		if (playStart) ch = audioManager->play(audioName, volume, 1.0, loop);
		break;
	}
	case msg::PLAY_SOUND: {
		const msg::PlaySound _m = static_cast<const msg::PlaySound&>(msg);
		if (_m._name == audioName) {
			if (playEvent)
				ch = audioManager->play(audioName, volume, 1.0, loop);
		}
		break;
	}
	default:
		break;
	}
}
