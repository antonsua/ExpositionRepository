#ifndef SRC_SOUNDMANAGER_H_
#define SRC_SOUNDMANAGER_H_

#include "Listener.h"
#include "SDLGame.h"

class SoundManager: public Listener
{
public:
	SoundManager(SDLGame* game);
	virtual ~SoundManager();

	virtual void receive(Message* msg);

private:
	SDLGame* game_;
	int vol_ = MIX_MAX_VOLUME / 10;
	const int volAdd_ = MIX_MAX_VOLUME / 20;

	int idMusic = 0;
	vector<Music*> music;
	Music *menu_, *board_, *sumo_, *pong_, *apple_, *platform_, *race_, *dodge_;
	SoundEffect *sumoBounce_, *sumoDeath_,*pongBlockHit_, *pongPaddleHit_, *pongDeath_,
		*appleDrop_, *appleFall_, *appleHit_, *appleCatch_, *jump_, *platformDeath_,
		*dodgeDeath_, *dodgeShot_;
};

#endif /* SRC_SOUNDMANAGER_H_ */
