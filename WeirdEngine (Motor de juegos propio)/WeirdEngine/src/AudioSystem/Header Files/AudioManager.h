#pragma once

#include <stdio.h>
#include <string>
#include <map>

namespace FMOD {
	class ChannelGroup;
	class Channel;
	class Sound;
	class System;
}

enum FMOD_RESULT;

class AudioManager {
public:
	static bool initSingleton();
	static AudioManager* getSingleton();
	static void closeSingleton();

	void update();

	void createSound(const std::string& audioId, const std::string& filename);

	FMOD::Channel* play(std::string audioId, float volume = 1.0f, float pitch = 1.0f, bool loop = true);
	void pause(FMOD::Channel* ch);
	void stop(FMOD::Channel* ch);
	void releaseChannel(std::string audioId);

private:
	static AudioManager* instance_;

	AudioManager();
	~AudioManager();

	const char* SOUNDPATH_ = "resources/sounds/";

	FMOD_RESULT	result_;
	FMOD::System* system_ = nullptr;
	std::map<std::string, FMOD::Sound*> sounds_;
};

