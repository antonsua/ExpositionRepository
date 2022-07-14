#include "DemoMinigame.h"

const string DemoMinigame::idName_ = "DemoMinigame";

DemoMinigame::DemoMinigame(Game* game, stack<int> *p_playersTurnsOrder, int numPlayers) :
	MiniGameState(game, p_playersTurnsOrder, idName_, numPlayers)
{
	initState();
}

DemoMinigame::~DemoMinigame()
{
	closeState();
}

void DemoMinigame::initState()
{
	//this state has no managers or listeners

	//this is how to create specific entities
	//in the states themselves is not really a good idea -> use managers
	//but anyway you will create entities inside those managers
	///options are mixable and ofc they are not unique
	///TL:DR - now entities do not delete their components so u can reuse them
	///TL:DR - but u have to DELETE THEM (if u use pointers)
	///TL:DR - also, now all components are equal from the enity perspective
	///read samir pdf for manager -> do not use pointers

	//OPTION 0 - not very good any more
	//you can still create and add component inside entity factories
	//and then delete them in the destructor of that entity
	//for size, pos etc you can do it whererver you want really
	//in the constructor or outside using sets

	//OPTION 1
	//having a vector<EntityComponent*> for the unic entity
	//pushing new components YOU HAVE TO DELETE THEM
	demoActorComponents.push_back(new BasicKBCtrlComponent(SDLK_a, SDLK_d, SDLK_w, SDLK_s, SDLK_z));
	demoActorComponents.push_back(new BasicMotionPhysics());
	demoActorComponents.push_back(new SpriteSheetRenderer(game_->getResources()->getSpriteSheetTexture(Resources::ss_Dog)));
	demoActorComponents.push_back(new SkeletonRenderer());
	//creating the entity and itself will add all the components (or more demoActors)
	demoActor = new DemoActor(game_, demoActorComponents);
	gameObjects_.push_back(demoActor);
	//gameObjects_.push_back(new  DemoActor(game_, demoActorComponents)); //second with the same components
	///this is usefull if you are never going to need any reference to the object or a specific component

	//OPTION 2
	//references to each component and/or the object
	//create the object (without initial components) and you can already push it
	demoActor_2 = new DemoActor(game_);
	gameObjects_.push_back(demoActor_2);
	//create the components
	control_IC = new BasicKBCtrlComponent(SDLK_a, SDLK_d, SDLK_w, SDLK_s, SDLK_z);
	basicMotion_UC = new BasicMotionPhysics();
	sprite_RC = new SpriteSheetRenderer(game_->getResources()->getSpriteSheetTexture(Resources::ss_Dog));
	debug_RC_ = new SkeletonRenderer();
	//and then manually add them to the entity
	demoActor_2->addComponent(control_IC);
	demoActor_2->addComponent(basicMotion_UC);
	demoActor_2->addComponent(sprite_RC);
	demoActor_2->addComponent(debug_RC_);
	///this is required when you need references to some components or the entity

	//OPTION 3 : MIX 	//just an example of mix
	debug_RC_3 = new SkeletonRenderer(); //I need reference to the debug renderer
	//then I just add them all to a vector for easy deleting
	demoActorComponents_3.push_back(new BasicKBCtrlComponent(SDLK_a, SDLK_d, SDLK_w, SDLK_s, SDLK_z));
	demoActorComponents_3.push_back(new BasicMotionPhysics());
	demoActorComponents_3.push_back(new SpriteSheetRenderer(game_->getResources()->getSpriteSheetTexture(Resources::ss_Dog)));
	demoActorComponents_3.push_back(debug_RC_3); //the referenced one
	//I need reference to the player
	demoActor_3 = new DemoActor(game_, demoActorComponents_3);
	demoActor_3->delComponent(debug_RC_3); //I can delete the debug
	demoActor_3->addComponent(debug_RC_3);
	gameObjects_.push_back(demoActor_3);
}

void DemoMinigame::closeState()
{
	delete demoActor;
	for (auto c : demoActorComponents) delete c;

	delete demoActor_2;
	delete control_IC;
	delete basicMotion_UC;
	delete sprite_RC;
	delete debug_RC_;

	delete demoActor_3;
	for (auto c : demoActorComponents_3) delete c;
}

///////////////////////////////////////////////////////////////////////////////

//propagates the event and then if no one handles it, tries ti handle
void DemoMinigame::handleEvents(Uint32 time, SDL_Event event)
{
	bool handled = false;

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {

		case SDLK_SPACE: //close minigame
			handled = true;
			endMiniGame(); //atm comes from minigameState
			break;
		}
	}

	//prior propagation
	if (!handled) MiniGameState::handleEvents(time, event);
}

///////////////////////////////////////////////////////////////////////////////

void DemoMinigame::endMiniGame()
{
	MiniGameState::endMiniGame(); //default rnd behabior
}
