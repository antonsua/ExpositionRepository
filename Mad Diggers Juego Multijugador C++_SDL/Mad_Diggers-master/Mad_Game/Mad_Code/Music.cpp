#include "Music.h"

Music::Music() :
		music_(nullptr) {
}

Music::Music(std::string fileName) :
		music_(nullptr), paused_(false) {
	load(fileName);
}

Music::~Music() {
	close();
}

#include <iostream>
bool Music::load(std::string fileName) {
	close();
	music_ = Mix_LoadMUS(fileName.c_str());
	if (music_ == NULL) {
		std::cout << "Unable to load " << fileName  << " :: " << Mix_GetError() <<std:: endl;
	}
	return music_ != nullptr;
}

void Music::close() {
	if (music_ != nullptr) {
		Mix_FreeMusic(music_);
		music_ = nullptr;
	}
}

///////////////////////////////////////////////////////////////////

void Music::play(int repetitions) {
	if (paused_) {
		Mix_ResumeMusic();
		paused_ = false;
	}
	else Mix_PlayMusic(music_, repetitions);
}

void Music::pause() {
	paused_ = true;
	Mix_PauseMusic();
}

