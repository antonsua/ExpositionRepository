#pragma once

#include "MiniGameState.h"

#include "DemoActor.h"
#include "EntityComponent.h"
#include "ButtonInputComponent.h"
#include "BasicKBCtrlComponent.h"
#include "BasicMotionPhysics.h"

#include "ImageRenderer.h"
#include "SpriteSheetRenderer.h"
#include "SkeletonRenderer.h"

class DemoMinigame : public MiniGameState
{
public:
	DemoMinigame(Game* game, stack<int> *p_playersTurnsOrder, int numPlayers);
	virtual ~DemoMinigame();

	virtual void handleEvents(Uint32 time, SDL_Event event);

private:
	static const string idName_;

protected:
	//from GameState
	virtual void initState();
	virtual void closeState();

	virtual void endMiniGame();

	//option 1
	DemoActor* demoActor;
	vector<EntityComponent*> demoActorComponents;

	//option 2
	DemoActor* demoActor_2;
	BasicKBCtrlComponent* control_IC;
	BasicMotionPhysics* basicMotion_UC;
	SpriteSheetRenderer* sprite_RC;
	SkeletonRenderer* debug_RC_;

	//option 3
	DemoActor* demoActor_3;
	SkeletonRenderer* debug_RC_3;
	vector<EntityComponent*> demoActorComponents_3;
};