#pragma once
#include "Entity.h"
#include "AppleTree.h"
#include "Listener.h"
#include "Emitter.h"
#include "message_RC.h"
#include "Value_RC.h"
#include "ShapeRenderer.h"
#include "GamePadComponent.h"
#include "ApplePlayerController.h"

class ApplesManager;

struct RectanglePhysics
{
	Point A, B, C, D;
	float w, h;
};

class AppleMiniGame;

const int MAX_SCORE_DIGITS = 3;
const int APPLE_PLAYER_WIDTH = 95;
const int APPLE_PLAYER_HEIGHT = 95;

class ApplePlayer : public Entity, public Listener,public Emitter
{

public:
	ApplePlayer(Game* game, AppleTree* tree, int colorIdentifier, SDL_Keycode left, SDL_Keycode right,
		SDL_Keycode shake, SDL_Keycode exploit, ApplesManager* applesManager,Resources::ColorId color, int padNum
	, int numPlayers);
	~ApplePlayer();
	ApplePlayer();

	virtual int getSomeValue() { return getScore(); } //to avoid some cast

	void addScore(int s);
	int getScore() const { return score_; };
	int getID() const { return colorIdentifier_; };

	RectanglePhysics getRectangle() const { return phRect_; };
	ShapeRenderer* getShapeRC()  { return &shapeRC_; };

private:
	bool isOverlapping(const Point l1, const Point r1, const Point l2, const Point r2) const;
	void setCollisionBox();
	void update(Uint32 time);
	void updateRectangle();
	void receive(Message* msg);
	void boundToLimits();
	void setPos();

	GamePadComponent gamepad_;
	ApplePlayerController playerController_;

	AppleTree* myTree_;

	Point l1, r1;
	RectanglePhysics phRect_;

	Value_RC valueRC_;
	spriteData nameData_;
	ShapeRenderer shapeRC_;

	int colorIdentifier_;
	int score_;
	int numPlayers_;
	
};

