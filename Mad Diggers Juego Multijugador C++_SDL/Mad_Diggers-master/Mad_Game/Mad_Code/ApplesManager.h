#pragma once
#include <vector>
#include "Apple.h"
#include "AppleController.h"
#include "GameObject.h"
#include "Listener.h"
#include "ApplePlayer.h"

const int MAX_RND = -45;
const int MIN_RND = -300;
const int INIT_POS_OFFSET_X = 80;

class AppleMiniGame;
class ApplesManager : public GameObject,public Listener,public Emitter
{

public:
	ApplesManager();
	ApplesManager(Game* game,AppleMiniGame* applMG);
	~ApplesManager();

	void initializeObject(Apple* o,int colorIdentifier);
	void generateApple(int colorIdentifier, Resources::ColorId color);

	void handleEvents(Uint32 time, const SDL_Event& event) {};
	void update(Uint32 time);
	void render(Uint32 time);

	Apple* getObject(int colorIdentifier, const Resources::ColorId appleColor);
	Resources::ColorId getColorbyID(int colorIdentifier) const;
private:
	void receive(Message* msg);
	void setRandomPosition(Apple* &a);
	void spawnApples(SpawnApplesMG* msg);
	bool rectangleCircleColl(const Circle &c, const RectanglePhysics &r)const ;
	void checkColl();

	std::vector<Apple*> objs_;
	std::vector<ApplePlayer*> players_;
	
};

