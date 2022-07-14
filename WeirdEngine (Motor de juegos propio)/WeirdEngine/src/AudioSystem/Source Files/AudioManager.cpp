#include "AudioManager.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#include <fmod.h>

using namespace std;
using namespace FMOD;

AudioManager* AudioManager::instance_ = nullptr;

bool AudioManager::initSingleton() {
	if (instance_ == nullptr) {
		instance_ = new AudioManager();

		return true;
	}

	return false;
}

AudioManager* AudioManager::getSingleton() {
	return instance_;
}

void AudioManager::closeSingleton() {
	delete instance_;
	instance_ = nullptr;
}

void AudioManager::update() {
	result_ = system_->update();
}

void AudioManager::createSound(const std::string& audioId, const std::string& filename) {
	string path = SOUNDPATH_ + filename;

	result_ = system_->createSound(path.c_str(), FMOD_DEFAULT, 0, &sounds_[audioId]);
}

Channel* AudioManager::play(std::string audioId, float volume, float pitch, bool loop) {
	Channel* channel;

	result_ = system_->playSound(sounds_[audioId], 0, false, &channel);

	result_ = channel->setVolume(volume);

	result_ = channel->setPitch(pitch);

	if (loop) {
		result_ = channel->setMode(FMOD_LOOP_NORMAL);
	}
	else {
		result_ = channel->setMode(FMOD_LOOP_OFF);
	}
	return channel;
}

void AudioManager::pause(FMOD::Channel* ch) {
	bool paused;

	result_ = ch->getPaused(&paused);

	result_ = ch->setPaused(!paused);
}

void AudioManager::stop(FMOD::Channel* ch) {
	result_ = ch->stop();
}

void AudioManager::releaseChannel(std::string audioId) {

}

AudioManager::AudioManager() : result_(FMOD_OK) {
	result_ = System_Create(&system_);

	result_ = system_->init(128, FMOD_INIT_NORMAL, 0);
}

AudioManager::~AudioManager() {
	result_ = system_->close();

	result_ = system_->release();
}
