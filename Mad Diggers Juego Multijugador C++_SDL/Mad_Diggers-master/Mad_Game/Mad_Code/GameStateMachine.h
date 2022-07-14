//Mad_Diggers

#ifndef GAMESTATEMACHINE_H_
#define GAMESTATEMACHINE_H_

#include "GameState.h"
#include <stack>

#include "Listener.h"
#include "Emitter.h"
#include "AnimationRenderer.h"
#include "SoundManager.h"

class GameStateMachine : public Listener, public Emitter
{
public:
	GameStateMachine(Game* game);
	~GameStateMachine();

	void handleEvents(Uint32 time, SDL_Event event);
	void update(Uint32 time);
	void render(Uint32 time);

	virtual void receive(Message* msg);
	GameState* currentState() { return states_.top(); } //unused

private:
	stack<GameState*> states_;
	Game* game_;

	void init();

	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

	//custom global background
	static const Resources::ColorId _DEFAULT_BG_COLOR_;
	void initBackground();

	Entity animBG_;
	AnimationRenderer animation_;
	spriteSheetData animData_ =
	{
		Vector2D(1.0, 1.0), //go to spriteSheetData definition to see value names etc
		Vector2D(0.0, 0.0),
		true,

		0, 0, //0,0 is auto min / max
		0, 0,

		25,
		true,
		true,
		true
	};
};

#endif /* GAMESTATEMACHINE_H_ */
