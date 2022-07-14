//Mad_Diggers

#ifndef BOARDSTATE_H_
#define BOARDSTATE_H_

#include "GameState.h"

#include "BoardSquaresManager.h"
#include "BoardPlayersManager.h"
#include "BoardDicesManager.h"
#include "BoardBeesManager.h"

#include "Simulator.h"
#include "boardDebug_IC.h"
#include "BoardPadsManager.h"

#include "ImageRenderer.h"
//#include "Message_RC.h"

#include "SoundManager.h"

#include <stack>

class BoardState : public GameState, public Listener
{
public:
	BoardState(Game* game);
	virtual ~BoardState();

	virtual void handleEvents(Uint32 time, SDL_Event event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	virtual void receive(Message* msg);
	void logControls();

	///////////////////////////////////////////////////////////////////

	void resetBoard();
	void resetPlayersOrder();
	void rollSquare(int numPlayer, bool simulation, bool lastRoll); //public for simulations

protected:
	void moveFromLeft();
	void moveWorld();

	void preLaunchMinigame(MessageId msg);
	void launchMinigame();
	void endedMinigame();

	void preLaunchSpinner();
	void launchSpinner();

	void endGame();
	void preLaunchPodium();
	void launchPodium();

	bool blockGameObjects();

	//from GameState
	virtual void initState();
	void initBigMsg();
	void initRoundCounter();
	virtual void closeState();

private:
	//constants
	const string idName_;

	const int _LAST_ROUND_;				//to end the game
	const int _FIRST_ROUND_;			//start in 0 or 1 etc
	const int _ROLLS_PER_ROUND_;		//4+3+2+1 generations...

	const int numPlayers_, numSquares_, startMsgWaveReps_, startMsgWaveTime_;

	const double outWorldPos_;
	const Vector2D outWorldVel_;

	const double startMsgWtimes_, startMsgHtimes_, startMsgWaveMin_, startMsgWaveMax_;

	const Vector2D topLeftRoundCounter_;
	const double roundCounterW_, roundCounterH_;

	///////////////////////////////////////////////////////////////////

	int round_; //current round
	int roll_;	//allows to tell when the round is over

	bool paused_, starting_, ending_;
	bool rolling_, moving_, fromLeft_, fromMini_;
	MessageId minigameID_;

	BoardSquaresManager squaresManager_;
	BoardPlayersManager playersManager_;
	BoardDicesManager dicesManager_;
	BoardBeesManager beesManager_;

	BoardPadsManager padsManager_;
	BoardDebug_IC debug_IC_;
	Simulator simulator_;

	stack<int> playersTurnsOrder_;	//interactions queue

	Entity* bigMsg_;
	ImageRenderer startingMsg_, endingMsg_;
	spriteData bigMsgData_;
	int waveCounter_;

	Entity* roundCounter_;
	Message_RC roundCounterMsg_;
	spriteData roundCounterMsgData_;
};

#endif /* BOARDSTATE_H_ */
