#pragma once
#include "Component.h"

#include "Utilities\Vector3.h"

class Container;
class AudioManager;

namespace FMOD {
	class Channel;
}

class SoundComponent : public Component {
public:
	SoundComponent(Container* e) ;
	~SoundComponent() {};
	void Init(std::unordered_map<std::string, std::string>& param);

	// Implementar la que sea necesaria
	void update(Container* c, float time) {};

	//Receive implementation
	void receive(Container* c, const msg::Message& msg);

private:
	AudioManager* audioManager;

	std::string audioName;
	std::string fileName;
	float volume;
	bool loop;
	bool playStart;
	bool playEvent;
	FMOD::Channel* ch;
};