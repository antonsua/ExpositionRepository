#ifndef BOARDDEBUG_IC_H_
#define BOARDDEBUG_IC_H_

#include "GameInputComponent.h"
#include "Emitter.h"

class BoardDebug_IC : public GameInputComponent, public Emitter, public Listener
{
public:
	BoardDebug_IC(Game* game);
	virtual ~BoardDebug_IC();

	virtual void handleEvents(Uint32 time, const SDL_Event& event);
	virtual void receive(Message* msg);

	void logControls();

private:
	bool debugLog_;
};

#endif /* BOARDDEBUG_IC_H_ */
