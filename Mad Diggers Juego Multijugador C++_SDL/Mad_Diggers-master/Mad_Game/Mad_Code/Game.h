//Mad_Diggers

#ifndef GAME_H_
#define GAME_H_

#include "SDLGame.h"
#include "Messages.h"
#include "SoundManager.h"
#include <queue>

class GameStateMachine; //foward declaration

class Game: public SDLGame {

public:

	Game();
	virtual ~Game();

	//starts the game (run)
	virtual void start();
	//stops the game (end)
	virtual void stop();

	///////////////////////////////////////////////////////////////////

	GameStateMachine* getGSM();
	void logControls();

	///////////////////////////////////////////////////////////////////

	void sendToSM(Message* msg);

private:

	//Constants

	static const string //initialized in cpp
		_WINDOW_TITLE_;

	static const int
		_WINDOW_WIDTH_ = 800,
		_WINDOW_HEIGHT_ = 600;

	static const Uint32
		_MS_BETWEEN_FRAMES_ = 10; //for consistent framerate

	///////////////////////////////////////////////////////////////////

	void initGame();
	void closeGame();

	void run();

	void handleEvents(Uint32 time);
	void update(Uint32 time);
	void render(Uint32 time);

	void toggleFullscreen();

	///////////////////////////////////////////////////////////////////

	bool exit_; //ends the game

	GameStateMachine* gameStateMachine_; //controls the states
	SoundManager* soundManager_; //controls the sound
};

#endif /* GAME_H_ */
