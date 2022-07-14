//Mad_Diggers

#ifndef SOUNDEFFECT_H_
#define SOUNDEFFECT_H_

#include "sdl_includes.h"
#include <string>

class SoundEffect {

public:

	SoundEffect();
	//creates and loads new mix_chunk from file
	SoundEffect(std::string fileName);
	virtual ~SoundEffect();

	//loads new mix_chunk from file
	bool load(std::string fileName);
	//closes the current mix_chunk
	void close();

	//plays the mix_mchunk. If repetions = 0 -> no repetitions
	void play(int repetitions = 0);
	//stops the mix_music and cancels all repetitions left.
	void pause();

private:

	//pointer to the mix_chunk
	Mix_Chunk *chunck_ = nullptr;
	int lastChannel = -1;
};

#endif /* SOUNDEFFECT_H_ */
