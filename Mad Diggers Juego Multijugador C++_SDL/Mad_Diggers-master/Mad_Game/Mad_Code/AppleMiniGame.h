#pragma once
#include "ApplePlayer.h"
#include "Apple.h"
#include "MiniGameState.h"
#include "AppleTree.h"
#include <list>
#include "ApplePlayerController.h"
#include "BasicMotionPhysics.h"
#include "ImageRenderer.h"
#include "ApplesManager.h"
#include "Listener.h"
#include "AppleTimer.h"


class AppleMiniGame : public MiniGameState,public Listener
{

public:
	AppleMiniGame(Game* game, stack<int> *p_playersTurnsOrder, int numPlayers);
	~AppleMiniGame();
	std::vector<ApplePlayer*> getPlayers() { return applePlayers_; };
	virtual void handleEvents(Uint32 time, const SDL_Event event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

protected:
	//from GameState
	virtual void initState();
	virtual void closeState();
	virtual void endMiniGame();
private:
	static const string idName_;
	ApplesManager applesManager_;

	std::vector<ApplePlayer*> applePlayers_;
	std::list<Apple*> appleList_;
	std::list<AppleTree*> appleTrees_;
	AppleTimer timer_;

	Entity timerSquare_;
	ImageRenderer timerRC_;

	bool starting = true;

	void initMinigame();
	void receive(Message* msg);

	//Collision detection functions
	bool pointInRectangle(Point p, ApplePlayer* player);
	float area(Point a,Point b,Point c);
	bool RectCircleCollision(Circle c, RectanglePhysics r);
	void addScoreToPlayer(int playerID);


};

