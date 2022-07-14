#include "BoardPadsManager.h"



BoardPadsManager::BoardPadsManager(Game* game, int numPlayers): Entity(game), numPlayers_(numPlayers)
{
	for (int i = 0; i < numPlayers; i++)
	{
		gamePads_.push_back(GamePadComponent(i));
		gamePads_.back().registerListener(this);
	}
	playerNum_ = 0;
}


BoardPadsManager::~BoardPadsManager()
{
}

void BoardPadsManager::handleEvents(Uint32 time, const SDL_Event & event)
{
	if(playerNum_ < 5 && playerNum_ >= 0)
		gamePads_[playerNum_].handleEvents(this, time, event);
}

void BoardPadsManager::receive(Message * msg)
{
	switch (msg->id_) {
	case A:
		send(&Message(BOARD_SELECT));
		break;
	case DPAD_LEFT:
		send(&Message(BOARD_LEFT));
		break;
	case DPAD_RIGHT:
		send(&Message(BOARD_RIGHT));
		break;
	case BOARD_RESET:
		playerNum_ = 0;
		break;
	case BOARD_PLAYER_TURNOVER: {
		BoardMessage_SelectorColor * specificMsg =
			static_cast<BoardMessage_SelectorColor*> (msg);
		
		playerNum_ = specificMsg->playerNumber_;
	}
		break;
	case BOARD_UPDATE_QUEUE:
	{
		BoardMessage_QueueInfo * specificMsg =
			static_cast<BoardMessage_QueueInfo*> (msg);
	
		playerNum_ = specificMsg->p_playersTurnsOrder_->top();
	}
		break;
	default:
		break;
	}
}
