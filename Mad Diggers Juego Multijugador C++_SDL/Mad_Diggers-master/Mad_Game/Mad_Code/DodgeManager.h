#pragma once
#include "GameObject.h"
#include "Entity.h"
#include "Emitter.h"
#include "Listener.h"
#include "GoodTimer.h"
#include "CollisionManager.h"
#include "DodgeComponent.h"
#include "FillRectRenderer.h"
#include "ImageRenderer.h"
#include "ImageRepeatRender.h"
#include "ShapeRenderer.h"
#include "BasicMotionPhysics.h"
#include "AnimationRenderer.h"
#include "GamePadComponent.h"
#include "PlatformManager.h"

class DodgeManager : public GameObject, public CollisionManager, public Emitter, public Listener {
public:

	DodgeManager(Game* game, stack<int> *p_playersTurnsOrder);
	~DodgeManager();
	void virtual update(Uint32 time);
	void virtual render(Uint32 time);
	void virtual handleEvents(Uint32 time, const SDL_Event& event);
	void virtual receive(Message* msg);
	bool virtual checkEnd();
protected:
	void virtual collisionEvents(Physical* o1, Physical* o2);
	void virtual updateCollision(Uint32 time);
	void virtual createPlayer(int numPlayer);
	void virtual endGame(Uint32 time);
	void virtual initPlayers();
	void virtual initGame();
	virtual Entity*  getBullet();
	void virtual shootBullet(Vector2D pos,Vector2D vel);
	void virtual shootBarrage(int side);
	void virtual randomOrder(vector<Vector2D>& vec);

	bool end = false;
	bool start = true;
	double roundMult = 2.5;
	GoodTimer timer;
	stack<int> *p_playersTurnsOrder_;
	vector<playerInfo> infos;

	Entity* countEntity;
	Entity* terrain;
	vector<Entity*> players;
	vector<Entity*> bullets;

	AnimationRenderer* renderAnim;
	BasicMotionPhysics* basicPhysics;
	ImageRenderer* bulletRender;
	ImageRenderer* terrainRender;
	vector<GamePadComponent*> gamepads;
	vector<ShapeRenderer*> playerRender;
	vector<DodgeComponent*> playerComponent;

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

	vector<Vector2D> bulletsVel = { { 1,0 },{ 0.7,-0.7 },{ 0,-1 },{ -0.7,-0.7 },{ -1,0 },{ -0.7,0.7 },{ 0,1 },{ 0.7,0.7 } };
	vector<vector<Vector2D>> bulletsPos;
	
};