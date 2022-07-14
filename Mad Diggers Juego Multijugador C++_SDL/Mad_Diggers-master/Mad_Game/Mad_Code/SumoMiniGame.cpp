#include "SumoMiniGame.h"
#include "SumoPlayer.h"
#include "BackgroundObject.h"
#include <iterator>


const string SumoMinigame::idName_ = "SumoMinigame";

SumoMinigame::SumoMinigame(Game* game, stack<int> *p_playersTurnsOrder, int numPlayers)
	: MiniGameState(game, p_playersTurnsOrder, idName_, numPlayers), sumoManager_(new SumoManager(game)), countEntity_(game),
	renderAnim_(game_->getResources()->getSpriteSheetTexture(Resources::ss_SumoCD), &animData_, false)
{
	initState();
}

SumoMinigame::~SumoMinigame()
{
	closeState();
}

void SumoMinigame::initState()
{
	readFromJson(game_->getResources()->getJsonFile(Resources::j_SumoPlayer));

	SDL_SetRenderDrawColor(game_->getRenderer(), jsonData["renderDrawColor"][0].asUInt(),
		jsonData["renderDrawColor"][1].asUInt(), jsonData["renderDrawColor"][2].asUInt(),
		jsonData["renderDrawColor"][3].asUInt());

	p1Position_ = Vector2D(jsonData["Player1"]["x"].asUInt(), jsonData["Player1"]["y"].asUInt());
	p2Position_ = Vector2D(jsonData["Player2"]["x"].asUInt(), jsonData["Player2"]["y"].asUInt());
	p3Position_ = Vector2D(jsonData["Player3"]["x"].asUInt(), jsonData["Player3"]["y"].asUInt());
	p4Position_ = Vector2D(jsonData["Player4"]["x"].asUInt(), jsonData["Player4"]["y"].asUInt());

	initialPositions_.push_back(p1Position_);
	initialPositions_.push_back(p2Position_);
	initialPositions_.push_back(p3Position_);
	initialPositions_.push_back(p4Position_);


	sumoManager_->registerListener(this);
	BackgroundObject* sumoArea = new  BackgroundObject(game_, Resources::i_sumoArea);
	sumoManager_->addCollisionObject(sumoArea);
	gameObjects_.push_back(sumoArea);

	// game object based on components
	if (numOfPlayers_ >= 2) {
		SumoPlayer* p1 = new SumoPlayer(game_, jsonData["Keys"]["p1Keys"],Resources::i_sumoP0,
			this,0);
		SumoPlayer* p2 = new SumoPlayer(game_, jsonData["Keys"]["p2Keys"], Resources::i_sumoP1,
			this,1);

		sumoManager_->addCollisionObject(p1);
		gameObjects_.push_back(p1);
		sumos_.push_back(p1);
		sumos_.push_back(p2);

		sumoManager_->addCollisionObject(p2);
		gameObjects_.push_back(p2);
	}
	 if (numOfPlayers_ == 4)
	{
		SumoPlayer* p3 = new SumoPlayer(game_,jsonData["Keys"]["p3Keys"], Resources::i_sumoP2,
			this,2);
		SumoPlayer* p4 = new SumoPlayer(game_, jsonData["Keys"]["p4Keys"], Resources::i_sumoP3,
			this,3);

		sumoManager_->addCollisionObject(p3);
		gameObjects_.push_back(p3);
		sumos_.push_back(p3);

		sumoManager_->addCollisionObject(p4);
		gameObjects_.push_back(p4);
		sumos_.push_back(p4);
	}
	 /*countEntity_.addComponent(new AnimationRenderer(game_->getResources()->getSpriteSheetTexture(Resources::ss_SumoCD)
		 , &animData_, false));*/
	 countEntity_.setWidth(320);
	 countEntity_.setHeight(240);
	 countEntity_.setPosition(Vector2D(400-160, 300-120)); //lul
	 renderAnim_.registerListener(this);
	 renderAnim_.registerListener(sumoArea);
	 gameObjects_.push_back(&countEntity_);

	 placeCircles();
	 moveCirclesToInitial();
}

void SumoMinigame::closeState()
{
	//superClass GameState deletes all entities
	//each entity deletes its components
}


//propagates the event and then if no one handles it, tries ti handle
void SumoMinigame::handleEvents(Uint32 time, const SDL_Event event)
{
	bool handled = false;

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {

		case SDLK_SPACE: //close minigame
			handled = true;
			MiniGameState::endMiniGame();
			break;
		}
	}

	//prior propagation
	if (!handled && ready) MiniGameState::handleEvents(time, event);
}

//controls logic and calls all gameobjects' update
void SumoMinigame::update(Uint32 time)
{
		if (starting_)
		{
			starting_ = false;
			sendToGSM(&Message(STATE_SUMO_CONTROLS));
		}

		MiniGameState::update(time);
		if (ready) sumoManager_->update(time);
}

void SumoMinigame::render(Uint32 time)
{
	if (starting_) return;

	bool z_order = false;
	for (GameObject* o : gameObjects_) {
		if (o->isActive())o->render(time);
		if (!z_order) {
			sumoManager_->render(time);
			z_order = true;
		}
	}
}

void SumoMinigame::receive(Message * msg)
{
	switch (msg->id_)
	{
	case SUMOGAME_OUT_FROM_AREA:
		p_playersTurnsOrder_->push(static_cast<Message_OutFromArea*>(msg)->player_);
		game_->sendToSM(msg);
		break;
	case MINIGAME_GAME_OVER:
		endMiniGame();
		break;

	case SUMOGAME_PLACE_REACHED:
		placedCircles_++;

		if (!isPlacingCircles()) //if alrdy placed -> do anim
		{
			countEntity_.addComponent(&renderAnim_);
			renderAnim_.start();
		}
		break;

	case ANIMATION_ENDED:
		ready = true;
		break;
	}
}

void SumoMinigame::endMiniGame()
{
	/*int elimSize = eliminationOrder_.size();
	for (int i = 0; i < elimSize; i++) {
		p_playersTurnsOrder_->push(eliminationOrder_.top());
		eliminationOrder_.pop();
	}*/

	sumoManager_->removeListener(this);
	closeMinigame();

	sendToGSM(&StateMessage_Minigame(STATE_PODIUM, p_playersTurnsOrder_));
}

void SumoMinigame::placeCircles()
{
	Vector2D aux;
	for (auto it : sumos_) {
		aux = getInitialPos();
		it->setPosition(aux);
	}
}

Vector2D SumoMinigame::getInitialPos()
{
	double x, y;

	switch (rand() % 3 + 0)
	{
	case 0: //Arriba
		x = rand() % game_->getWindowWidth() + 0;
		y = 0;
		break;
	case 1: // Abajo
		x = rand() % game_->getWindowWidth() + 0;
		y = game_->getWindowHeight();

		break;
	case 2: //Izquierda
		x = 0;
		y = rand() % game_->getWindowHeight() + 0;

		break;
	case 3: //Derecha
		x = game_->getWindowWidth();
		y = rand() % game_->getWindowHeight() + 0;
		break;
	}

	return Vector2D(x, y);
}

void SumoMinigame::moveCirclesToInitial()
{
	int i = 0;
	for (auto it : sumos_) {
		it->moveToPoint(initialPositions_[i], 3000);
		i++;
	}
}






