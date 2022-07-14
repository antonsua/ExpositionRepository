#pragma once
#include "GameState.h"
#include "AnimationRenderer.h"
#include "ShapeRenderer.h"
#include "SumoPlayer.h"
#include "Listener.h"

const Vector2D BUTTON_OFFSET(380, 280);
const Vector2D BUTTON_SIZE(344, 38);


class ControlsState : public GameState,public Listener
{


public:
	ControlsState(Game* game,int numPlayers, string MiniGameID);
	~ControlsState();
	virtual void initState();
	virtual void closeState();

	void handleEvents(Uint32 time, const SDL_Event event);
	virtual void update(Uint32 time);
private:
	const string idName;

	int numPlayers_;

	ImageRenderer backkk;
	ImageRenderer pressA_;

	Entity animBG_;
	Entity button_;

	std::vector<Entity*> fakePlayers_;
	std::vector<GamePadComponent*> padComponents_;
	std::vector<ShapeRenderer*> playerShapes_;
	std::vector<bool> playersReady_;

	void addPads();
	void initiatePadComp();
	void registerPadListeners();
	void pushPlayers();
	bool allReady();
	void startMG();
	void setShapes();
	void receive(Message* msg);
	void positionIndicators();
	Resources::ImageId getBackground();


};

