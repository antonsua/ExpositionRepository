#pragma once
#include "GameObject.h"
#include "Entity.h"
#include "Emitter.h"
#include "Listener.h"
#include "GoodTimer.h"
#include "CollisionManager.h"
#include "ImageRenderer.h"
#include "PlatformGameComponent.h"
#include "ImageRepeatRender.h"
#include "ShapeRenderer.h"
#include "BasicMotionPhysics.h"
#include "PatrolPhysics.h"
#include "AnimationRenderer.h"
#include "GamePadComponent.h"

struct playerInfo {
	SDL_Keycode left, right, up, down;
	Resources::ColorId color;
};
struct platformInfo {
	double x, y, w, h;
	bool trap;
};
struct mobilePlatform
{
	platformInfo platform;
	double velX, velY;
	Uint32 turnTime;
};
struct levelInfo {
	vector<platformInfo> platforms;
	vector<mobilePlatform> mobileplatforms;
	double finishX, finishY;
	double startX, startY;
};

class PlatformManager :
	public GameObject, public Emitter, public Listener, public CollisionManager
{
public:

	PlatformManager(Game* game, stack<int> *p_playersTurnsOrder, int gamemode);
	~PlatformManager();
	void virtual update(Uint32 time);
	void virtual render(Uint32 time);
	void virtual handleEvents(Uint32 time, const SDL_Event& event);
	void virtual receive(Message* msg);
	bool virtual checkEnd();
	

protected:
	void virtual collisionEvents(Physical* o1, Physical* o2);
	void virtual updateCollision(Uint32 time);
	void virtual createPlayer(int numPlayer);
	virtual Entity* createPlatform(Vector2D position, double width, double height, bool trap);
	void virtual createPlatform(Vector2D position, double width, double height, bool trap, Vector2D velocity, Uint32 turnTime);
	void virtual createLevel(int i);
	void virtual initPlayers();
	void virtual initFinish();
	void virtual initLevels();
	void virtual playerFinish(int p);
	void virtual nextLevel();
	void virtual endLevel();

	int gamemode_;
	int level;
	bool end = false;
	bool start = true;
	stack<int> *p_playersTurnsOrder_;
	GoodTimer timer;

	AnimationRenderer* renderAnim;
	BasicMotionPhysics* basicPhysics;
	ImageRenderer* trapRender;
	ImageRenderer* finishRender;
	ImageRepeatRender* blockRender;
	vector<GamePadComponent*> gamepads;
	vector<ShapeRenderer*> playerRender;
	vector<PlatformGameComponent*> playerComponent;
	vector<PatrolPhysics*> platformPhysics;

	vector<playerInfo> infos;
	vector<levelInfo> levels;

	vector<int> playerWin;
	vector<int> playerLoss;
	vector<Entity*> players;
	vector<Entity*> platforms;
	vector<Entity*> traps;
	Entity* finish, *countEntity;

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