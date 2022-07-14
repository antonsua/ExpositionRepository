#include "RulesState.h"



RulesState::RulesState(Game* game) : GameState(game), back1_(game),
rules1RC_(game->getResources()->getImageTexture(Resources::i_rulesMenu1)),
back2_(game), rules2RC_(game->getResources()->getImageTexture(Resources::i_rulesMenu2)), button_(game),
nextRC_(game->getResources()->getImageTexture(Resources::i_menuNext_)), gpad_(0),
backMenuRC_(game->getResources()->getImageTexture(Resources::i_rulesBackMenu))
{
	initState();

}


RulesState::~RulesState()
{
}

void RulesState::receive(Message * msg)
{
	switch (msg->id_)
	{
	case A:
	{
		if (!changed) {
			changed = true;
			button_.switchComponents(&nextRC_, &backMenuRC_);
			button_.setWidth(BACKTO_MENU.getX());
			button_.setHeight(BACKTO_MENU.getY());
			back1_.setActive(false);
			backMenuRC_.waveAlpha(0, 1, 1000);
			break;
		}
		else {
			sendToGSM(&Message(STATE_POP));
		}
	}
	}
}

void RulesState::initState()
{
	back2_.addComponent(&rules2RC_);
	back2_.setHeight(game_->getWindowHeight());
	back2_.setWidth(game_->getWindowWidth());
	gameObjects_.push_back(&back2_);

	back1_.addComponent(&rules1RC_);
	back1_.setHeight(game_->getWindowHeight());
	back1_.setWidth(game_->getWindowWidth());
	gameObjects_.push_back(&back1_);

	button_.addComponent(&nextRC_);
	button_.setHeight(MENU_BUTTON_SIZE.getY());
	button_.setWidth(MENU_BUTTON_SIZE.getX());
	button_.setPosition(Vector2D(game_->getWindowWidth() - button_.getWidth(),
		game_->getWindowHeight() - button_.getHeight()));
	gameObjects_.push_back(&button_);

	nextRC_.waveAlpha(0, 1, 1000);

	gpad_.registerListener(this);
	back2_.addComponent(&gpad_);


}

void RulesState::closeState()
{
}
