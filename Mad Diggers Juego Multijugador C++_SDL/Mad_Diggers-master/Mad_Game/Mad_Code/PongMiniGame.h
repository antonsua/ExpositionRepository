#pragma once
#include "MiniGameState.h"
#include "Emitter.h"
#include "Listener.h"
#include "BallPhysicsComponent.h"
#include "jsonReader.h"
#include <vector>
#include "PongManager.h"
#include "Paddle.h"
#include "ballPong.h"
#include "BlockPong.h"
#include "Timer.h"
#include "AnimationRenderer.h"



class PongMiniGame : public MiniGameState, public Listener
{
public:

	PongMiniGame(Game* game, stack<int> *p_playersTurnsOrder, int numPlayers);
	virtual ~PongMiniGame();

	virtual void handleEvents(Uint32 time, SDL_Event event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void receive(Message* message);

private:
	static const string idName_;

protected:
	virtual void initState();
	virtual void closeState();

	virtual void endMiniGame();

	bool starting_ = true;

	void addWall(Vector2D pos, bool orientation);
	void createPlayer(int numPlayer);
	void removePlayer(int playerNum);
	bool running_ = false;
	bool exit_ = false;
	bool blockMoving = false;
	bool count = true;
	PongManager* manager;
	vector<Paddle*> paddles;
	int paddleAux = -1;
	vector<BlockPong*> blocks;
	Entity* countEntity;
	AnimationRenderer renderAnim;
	Timer timer_;
	int leftScore_ = 0;
	int rightScore_ = 0;
	//from GameState

	const Vector2D _BORDER_;
	const int _MAX_SCORE_;
	list<int> playerNum_ { 0, 1, 2, 3 };
	const vector<Vector2D> BlockPositions{ { 0.0, 0.0 },{ game_->getWindowWidth() - _BORDER_.getX(), 0.0 },{ Vector2D(0.0, game_->getWindowHeight() - _BORDER_.getY())}, { game_->getWindowWidth() - _BORDER_.getX(), game_->getWindowHeight() - _BORDER_.getY() } };
	spriteSheetData animData_ = {
		Vector2D(1.0, 1.0), //go to spriteSheetData definition to see value names etc
		Vector2D(0.0, 0.0),
		false,

		0, 0, //0,0 is auto min / max
		0, 0,

		10,
		false,
		false,
	};
};
