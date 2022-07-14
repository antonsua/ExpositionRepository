#include "MenuState.h"



MenuState::MenuState(Game* game): GameState(game), padIC_(0),
instRC_(game->getResources()->getImageTexture(Resources::i_inst))
{
	initState();
	instRC_.registerListener(this);

	std::cout
		<< std::endl << "///////////////////////////////////////////////////////"
		<< std::endl
		<< std::endl << "Debug controls with keyboard:"
		<< std::endl
		<< std::endl << " * Menu - dir keys and enter"
		<< std::endl << " * Across many screens SPACE to skip/continue"
		<< std::endl << " * Board - dir keys and space - Numpad numbers to launch minigames"
		<< std::endl << " * To exit game use the X"
		<< std::endl << " * Toggle fullscreen use F"
		<< std::endl
		<< std::endl << "///////////////////////////////////////////////////////"
		<< std::endl;
}

MenuState::~MenuState()
{
	closeState();
}

void MenuState::handleEvents(Uint32 time, const SDL_Event event)
{
	GameState::handleEvents(time, event);
	if (event.type) {

		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_DOWN) {
				currentButton++;
				moveSelector();
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				currentButton--;
				moveSelector();
			}
			if (event.key.keysym.sym == SDLK_RETURN) {
				activateButton();
			}
		}
	}
}

void MenuState::receive(Message * msg)
{
	switch (msg->id_)
	{
	case BOARD_ENDMSG_FADED:
		launchBoard();
		break;
	case A:
		activateButton();
		break;
	case DPAD_UP:
		currentButton--;
		moveSelector();
		break;
	case DPAD_DOWN:
		currentButton++;
		moveSelector();
		break;
	default:
		break;
	}
}

void MenuState::moveSelector()
{
	if (currentButton > NUM_BUTTONS) currentButton = 0;

	else if (currentButton < 0) currentButton = NUM_BUTTONS;

	selectorObject_->setPosition(Vector2D(selectorIniPos.getX(),
		selectorIniPos.getY() + currentButton*distanceBTWButtons));
}

void MenuState::activateButton()
{
	switch (currentButton)
	{
	case 0: //board
		for (auto it : images_) {
			it->fadeToAlpha(0, fadeBoardTime_);
		}
		instRC_.fadeToAlpha(0, fadeBoardTime_, BOARD_ENDMSG_FADED);
		break;
	case 1:
		sendToGSM(&Message(STATE_RULES));
		break;
	case 2:
		sendToGSM(&Message(STATE_CREDITS));
		break;
	}
}

 Entity* MenuState::addEntity(const int height, const int width, const Vector2D pos, const Resources::ImageId image, bool fade)
{
	Entity* enti = new Entity(game_);

	ImageRenderer* ren = new ImageRenderer(game_->getResources()->getImageTexture(image)); //not deleted
	images_.push_back(ren);
	if (fade) {
	ren->setAlpha(0);
	ren->fadeToAlpha(1, fadeIntTime_);
	}

	enti->setHeight(height);
	enti->setWidth(width);
	enti->setPosition(pos);
	enti->addComponent(ren);
	gameObjects_.push_back(enti);

	return enti;
}

 void MenuState::launchBoard() {
	 for (auto it : images_) {
		 it->fadeToAlpha(1, fadeIntTime_);
	 }
	 instRC_.waveAlpha(0, 1, fadeIntTime_);

	 sendToGSM(&Message(STATE_BOARD));
 }

void MenuState::initState()
{
	#define js jsonData //macro to short

	readFromJson(game_->getResources()->getJsonFile(Resources::j_MainMenu));

	addEntity(game_->getWindowHeight(), game_->getWindowWidth(), Vector2D(0, 0), Resources::i_TheHiveBack, false);

	addEntity(buttonHeight, js["startWidth"].asInt(), Vector2D(buttonXDistance, firstButtonY), Resources::i_StartOff);

	addEntity(buttonHeight, js["howToWidth"].asInt(), Vector2D(buttonXDistance, firstButtonY + distanceBTWButtons),
		Resources::i_HowToOff);

	addEntity(buttonHeight, js["creditsWidth"].asInt(), Vector2D(buttonXDistance, firstButtonY + distanceBTWButtons * 2),
		Resources::i_CreditsOff);

	selectorObject_ = addEntity(js["selectorHeight"].asInt(), js["selectorWidth"].asInt(), Vector2D(selectorIniPos),
		Resources::i_paloMenu);

	padEntity_ = new Entity(game_);
	padIC_.registerListener(this);
	padEntity_->addComponent(&padIC_);
	gameObjects_.push_back(padEntity_);

	padEntity_->setWidth(INST_OFFSET.getX());
	padEntity_->setHeight(INST_OFFSET.getY());
	padEntity_->addComponent(&instRC_);
	padEntity_->setPosition(Vector2D(game_->getWindowWidth()/2- INST_OFFSET.getX() /2, game_->getWindowHeight() - INST_OFFSET.getY()));

	instRC_.waveAlpha(0, 1, fadeIntTime_);
}

void MenuState::closeState()
{
	for (auto it : gameObjects_) {
		if (it != nullptr) {
		delete it;
		it = nullptr;
		}
	}

	for (auto it : images_) {
		if (it != nullptr) {
			delete it;
			it = nullptr;
		}
	}
}

