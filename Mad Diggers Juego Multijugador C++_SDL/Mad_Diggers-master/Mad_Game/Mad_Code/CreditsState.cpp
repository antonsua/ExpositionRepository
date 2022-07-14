#include "CreditsState.h"



CreditsState::CreditsState(Game* game) :GameState(game), backObject_(game),
background_(game->getResources()->getImageTexture(Resources::i_creditsStateBack)), peopleObject_(game),
moveImg_(game->getResources()->getImageTexture(Resources::i_creditsPeople)),
padIC_(0), instRC_(game->getResources()->getImageTexture(Resources::i_rulesBackMenu)) {
	initState();
}



CreditsState::~CreditsState() {
}

void CreditsState::handleEvents(Uint32 time, const SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN)
		sendToGSM(&Message(STATE_POP));
	else GameState::handleEvents(time, event);
}

void CreditsState::update(Uint32 time) {
	GameState::update(time);

	objectY = peopleObject_.getPosition().getY();
	peopleObject_.setPosition(Vector2D(xOffset, objectY - moveVelocity));

	if (objectY < creditsEnd) {
		sendToGSM(&Message(STATE_POP));
	}
}

void CreditsState::initState() {
	//bg
	backObject_.setWidth(game_->getWindowWidth());
	backObject_.setHeight(game_->getWindowHeight());
	backObject_.addComponent(&background_);
	gameObjects_.push_back(&backObject_);

	//people
	peopleObject_.setWidth(creditsWidth);
	peopleObject_.setHeight(creditsHeight);
	peopleObject_.addComponent(&moveImg_);
	peopleObject_.setPosition(Vector2D(xOffset, game_->getWindowHeight() + creditsOffset));
	gameObjects_.push_back(&peopleObject_);

	//padInfo
	padEntity_ = new Entity(game_);
	padIC_.registerListener(this);
	padEntity_->addComponent(&padIC_);
	gameObjects_.push_back(padEntity_);

	padEntity_->setWidth(INST_OFFSET.getX());
	padEntity_->setHeight(INST_OFFSET.getY());
	padEntity_->addComponent(&instRC_);
	padEntity_->setPosition(Vector2D(INST_OFFSET.getY() / 2, game_->getWindowHeight() - INST_OFFSET.getY()));

	instRC_.registerListener(this);
	instRC_.waveAlpha(0, 1, fadeIntTime_, BOARD_STARTMSG_FADED);
}
void CreditsState::closeState() {
	if (padEntity_ != nullptr) {
		delete padEntity_;
		padEntity_ = nullptr;
	}
}

void CreditsState::receive(Message * msg) {
	switch (msg->id_) {
	case A:
		sendToGSM(&Message(STATE_POP));
		break;
	case DPAD_UP:
		moveVelocity -= 1;
		break;
	case DPAD_DOWN:
		moveVelocity += 1;
		break;
	default:
		break;
	}
}