#include "GameStateMachine.h"

#include "BoardState.h"

#include "DemoMinigame.h"
#include "SumoMinigame.h"
#include "PongMinigame.h"
#include "AppleMiniGame.h"
#include "PlatformMinigame.h"
#include "RaceMinigame.h"
#include "DodgeMinigame.h"
#include "MenuState.h"
#include "CreditsState.h"
#include "ControlsState.h"
#include "PodiumState.h"
#include "RulesState.h"
#include "SpinnerState.h"

const Resources::ColorId GameStateMachine::_DEFAULT_BG_COLOR_ = Resources::c_Black;

///////////////////////////////////////////////////////////////////

GameStateMachine::GameStateMachine(Game* game) : game_(game),
//background
animation_(game->getResources()->getSpriteSheetTexture(Resources::ss_BackGround),
	&animData_, true), animBG_(game)
{
	init();
}

GameStateMachine::~GameStateMachine()
{
	while (!states_.empty()) {
		delete states_.top(); //delete its states
		states_.pop();
	}
}

void GameStateMachine::init()
{
	pushState(new MenuState(game_));
	game_->sendToSM(&Message (STATE_MENU));
	initBackground();
}

void GameStateMachine::initBackground()
{
	animBG_.addComponent(&animation_);

	animBG_.setPosition(Vector2D(0, 0));
	//animBG_->setDirection(Vector2D(0, 1));

	animBG_.setWidth(game_->getWindowWidth());
	animBG_.setHeight(game_->getWindowHeight());
}

//////////////////////////////////////////////////////////////////////////////

void GameStateMachine::receive(Message* msg)
{
	switch (msg->id_)
	{
	case STATE_END_GAME:
		popState();
		pushState(new CreditsState(this->game_));
		break;
	case STATE_POP_MINIGAME:
	case STATE_POP:
		popState();
		break;
	}

	StateMessage_Minigame* MiniGameMsg = static_cast<StateMessage_Minigame*> (msg);
	switch (msg->id_)
	{
	case STATE_DEMO:
		pushState(new DemoMinigame(game_, MiniGameMsg->p_playersTurnsOrder_, 4));
		break;
	case STATE_SUMO:
		pushState(new SumoMinigame(game_, MiniGameMsg->p_playersTurnsOrder_, 4));
		break;
	case STATE_PONG:
		pushState(new PongMiniGame(game_, MiniGameMsg->p_playersTurnsOrder_, 4));
		break;
	case STATE_APPLE:
		pushState(new AppleMiniGame(game_, MiniGameMsg->p_playersTurnsOrder_, 4));
		break;
	case STATE_PLATFORM:
		pushState(new PlatformMinigame(game_, MiniGameMsg->p_playersTurnsOrder_, 4));
		break;
	case STATE_RACE:
		pushState(new RaceMinigame(game_, MiniGameMsg->p_playersTurnsOrder_, 4));
		break;
	case STATE_DODGE:
		pushState(new DodgeMinigame(game_, MiniGameMsg->p_playersTurnsOrder_, 4));
		break;

	case STATE_PODIUM_END:
		pushState(new PodiumState(this->game_, MiniGameMsg->p_playersTurnsOrder_, true));
		break;
	case STATE_PODIUM:
		pushState(new PodiumState(this->game_, MiniGameMsg->p_playersTurnsOrder_, false));
		break;

	case STATE_SUMO_CONTROLS:
		pushState(new ControlsState(game_, 4, "SumoMinigame"));
		break;
	case STATE_PONG_CONTROLS:
		pushState(new ControlsState(game_, 4, "PongMinigame"));
		break;
	case STATE_APPLE_CONTROLS:
	{
		ControlsState * aux = new ControlsState(game_, 4, "AppleMiniGame");
		aux->registerListener(static_cast<AppleControlsPop*>(msg)->miniGame_);
		pushState(aux);
		break;
	}
	case STATE_CONTROLS_PLATFORM:
		pushState(new ControlsState(game_, 4, "RaceMinigame"));
		break;
	case STATE_PLAT_CHALLENGE:
		pushState(new ControlsState(game_, 4, "PlatformMinigame"));
		break;
	case STATE_BULLET_CONTROLS:
		pushState(new ControlsState(game_, 4, "DodgeMinigame"));
		break;
	case STATE_BOARD:
		pushState(new BoardState(this->game_));
		break;
	case BOARD_SPINNER:
		pushState(new SpinnerState(this->game_,
			static_cast<StateMessage_Spinner*>(msg)->nextMinigame_, static_cast<StateMessage_Spinner*>(msg)->numPlayers_));
		break;
	case STATE_CREDITS:
		pushState(new CreditsState(this->game_));
		break;
	case STATE_RULES:
		pushState(new RulesState(game_));
		break;
	}

	game_->sendToSM(msg);
}

//////////////////////////////////////////////////////////////////////////////

//pushes over the current state (no delete, no pop)
void GameStateMachine::pushState(GameState *newState)
{
	states_.push(newState);
}

void GameStateMachine::popState()
{
	if (!states_.empty())
	{
		//	delete states_.top(); //delete before popping
		states_.pop();
	}
}

//deletes and pops all the states befor pushing the new one
void GameStateMachine::changeState(GameState *newState)
{
	while (!states_.empty()) {
		delete states_.top(); //delete before popping
		states_.pop();
	}

	states_.push(newState);
}

//////////////////////////////////////////////////////////////////////////////

void GameStateMachine::handleEvents(Uint32 time, SDL_Event event)
{
	if (!states_.empty())
	{
		states_.top()->handleEvents(time, event);
	}
}

void GameStateMachine::update(Uint32 time)
{
	if (!states_.empty())
	{
		states_.top()->update(time);
	}
}

void GameStateMachine::render(Uint32 time)
{
	if (!states_.empty())
	{
		SDL_Renderer* renderer = game_->getRenderer();

		SDL_SetRenderDrawColor(renderer, COLOREXP_P(Resources::getSDLColor(_DEFAULT_BG_COLOR_)));
		SDL_RenderClear(renderer);

		animBG_.render(time);
		states_.top()->render(time);

		SDL_RenderPresent(renderer);
	}
}
