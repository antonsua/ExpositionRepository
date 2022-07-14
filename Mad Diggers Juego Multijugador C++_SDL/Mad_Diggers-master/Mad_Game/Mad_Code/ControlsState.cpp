#include "ControlsState.h"


ControlsState::ControlsState(Game* game, int numPlayers, string MiniGameID) : GameState(game), animBG_(game),
playerShapes_(numPlayers), playersReady_(numPlayers, false), numPlayers_(numPlayers), idName(MiniGameID),
backkk(game->getResources()->getImageTexture(getBackground())),button_(game),
pressA_(game->getResources()->getImageTexture(Resources::i_pressA_))
{
	initState();
}


ControlsState::~ControlsState()
{
}

void ControlsState::initState()
{

	setShapes();


	animBG_.addComponent(&backkk);
	animBG_.setWidth(game_->getWindowWidth());
	animBG_.setHeight(game_->getWindowHeight());
	gameObjects_.push_back(&animBG_);

	pressA_.waveAlpha(0, 1, 2000);

	button_.addComponent(&pressA_);
	button_.setWidth(BUTTON_SIZE.getX());
	button_.setHeight(BUTTON_SIZE.getY());
	button_.setPosition(BUTTON_OFFSET);

	gameObjects_.push_back(&button_);

	initiatePadComp();
	addPads();
	registerPadListeners();
	pushPlayers();
	positionIndicators();
}

void ControlsState::closeState()
{
}

void ControlsState::handleEvents(Uint32 time, const SDL_Event event)
{
	GameState::handleEvents(time, event);

	if (event.type)
	{
		if (event.type == SDL_KEYDOWN) sendToGSM(&Message(STATE_POP));
		send(&Message(STATE_CONTROLS_POP));

	}
}

void ControlsState::update(Uint32 time)
{
	GameState::update(time);

}

void ControlsState::addPads()
{
	fakePlayers_.resize(numPlayers_);
	for (int i = 0; i < fakePlayers_.size(); i++) {
		fakePlayers_[i] = new Entity(game_);
		fakePlayers_[i]->addComponent(padComponents_[i]);
		fakePlayers_[i]->addComponent(playerShapes_[i]);
		fakePlayers_[i]->setWidth(60);
		fakePlayers_[i]->setHeight(60);
	}
}

void ControlsState::initiatePadComp()
{
	padComponents_.resize(numPlayers_);
	for (int i = 0; i < padComponents_.size(); i++) {
		padComponents_[i] = new GamePadComponent(i);
	}
}

void ControlsState::registerPadListeners()
{
	for (auto it : padComponents_) {
		it->registerListener(this);
	}
}

void ControlsState::pushPlayers()
{
	fakePlayers_[0]->setPosition(Vector2D(200, 200));
	for (auto it : fakePlayers_) {
		gameObjects_.push_back(it);
	}
}

bool ControlsState::allReady()
{
	auto it = playersReady_.begin();
	while (it != playersReady_.end()) {
		if (*it) it++;
		else return false;
	}
	return true;
}

void ControlsState::startMG()
{
	GameState::render(SDL_GetTicks());

	for (auto it : padComponents_) {
		it->removeListener(this);
	}

	SDL_Delay(2000);

	sendToGSM(&Message(STATE_POP));
}

void ControlsState::setShapes()
{
	Resources::ColorId color = Resources::c_Grey_light;
	Resources::ShapeId p1, p2, p3, p4;

	if (numPlayers_ >= 2) {
		if (idName == "SumoMinigame") {
			 p1 = Resources::s_sumoCP1;
			 p2 = Resources::s_sumoCP2;
		}
		else if (idName == "PongMinigame") {
			 p1 = Resources::s_pongCP1;
			 p2 = Resources::s_pongCP2;
		}
		else if (idName == "AppleMiniGame") {
			p1 = Resources::s_beeKeepingPlayer;
			p2 = Resources::s_beeKeepingPlayer;
		}
		else if (idName == "RaceMinigame") {
			p1 = Resources::s_platPlayer;
			p2 = Resources::s_platPlayer;
		}
		else if (idName == "PlatformMinigame") {
			p1 = Resources::s_platPlayer;
			p2 = Resources::s_platPlayer;
		}
		else if (idName == "DodgeMinigame") {
			p1 = Resources::s_bulletPlayer;
			p2 = Resources::s_bulletPlayer;
		}
		playerShapes_[0] = new ShapeRenderer(game_, p1, color);
		playerShapes_[1] = new ShapeRenderer(game_, p2, color);
	}

	 if (numPlayers_ == 4) {
		if (idName == "SumoMinigame") {
			 p3 = Resources::s_sumoCP3;
			 p4 = Resources::s_sumoCP4;
		}
		else if (idName == "PongMinigame") {
			 p3 = Resources::s_pongCP3;
			 p4 = Resources::s_pongCP4;
		}
		else if (idName == "AppleMiniGame") {
			p3 = Resources::s_beeKeepingPlayer;
			p4 = Resources::s_beeKeepingPlayer;
		}
		else if (idName == "RaceMinigame") {
			p3 = Resources::s_platPlayer;
			p4 = Resources::s_platPlayer;
		}
		else if (idName == "PlatformMinigame") {
			p3 = Resources::s_platPlayer;
			p4 = Resources::s_platPlayer;

		}
		else if (idName == "DodgeMinigame") {
			p3 = Resources::s_bulletPlayer;
			p4 = Resources::s_bulletPlayer;
		}
		playerShapes_[2] = new ShapeRenderer(game_, p3, color);
		playerShapes_[3] = new ShapeRenderer(game_, p4, color);
	}
}



Resources::ImageId ControlsState::getBackground()
{

	if (idName == "SumoMinigame") {
		return Resources::i_sumoControls;
	}
	else if (idName == "PongMinigame") {
		return Resources::i_pongControls;
	}
	else if (idName == "AppleMiniGame") {
		return Resources::i_appleControls;
	}
	else if (idName == "RaceMinigame") {
		return Resources::i_platControls;
	}
	else if (idName == "PlatformMinigame") {
		return Resources::i_challControls;
	}
	else if (idName == "DodgeMinigame") {
		return Resources::i_dodgeControls;
	}
}

void ControlsState::receive(Message * msg)
{
	int n;
	switch (msg->id_)
	{
	case A:
		n = static_cast<PressedAPAD*>(msg)->playerPadID_;
		playersReady_[n] = true;
		playerShapes_[n]->setColor(Resources::_DEFAULT_PLAYERS_COLORS_ID_[n]);
		if (allReady()) startMG();
		cout << n << endl;
		break;
	}
}

void ControlsState::positionIndicators()
{
		int x = 390; int y = 325;
		for (int i = 0; i < fakePlayers_.size(); i++) {
			fakePlayers_[i]->setPosition(Vector2D(x + i * fakePlayers_[i]->getWidth()*1.2, y));
		}
}

