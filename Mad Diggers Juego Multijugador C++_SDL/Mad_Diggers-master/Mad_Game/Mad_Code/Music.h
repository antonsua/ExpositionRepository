//Mad_Diggers

#ifndef MUSIC_H_
#define MUSIC_H_

#include "sdl_includes.h"
#include <string>

class Music {

public:

	Music();
	//creates and loads new mix_music from file
	Music(std::string fileName);
	virtual ~Music();

	//loads new mix_music from file
	bool load(std::string fileName);
	//closes the current mix_music
	void close();

	//plays the mix_music. If repetions = -1 -> no repetitions
	void play(int repetitions = -1);
	//stops the mix_music and cancels all repetitions left.
	void pause();

private:

	//pointer to the mix_music
	Mix_Music* music_;
	bool paused_;
};

#endif /* MUSIC_H_ */
