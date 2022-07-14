#include "BoardDebug_IC.h"

BoardDebug_IC::BoardDebug_IC(Game* game) : GameInputComponent(game), debugLog_(true)
{
}

BoardDebug_IC::~BoardDebug_IC()
{
}

///////////////////////////////////////////////////////////////////////////////

void BoardDebug_IC::receive(Message* msg)
{

	if (isActive()) switch (msg->id_)
	{
	case BOARD_INIT: {
		logControls();
		break;
	}
	}

	if (isActive() && debugLog_) switch (msg->id_)
	{
	case BOARD_GAMEOVER: {
		cout << endl << "///// GAME FINISHED ///// you can continue though /////" << endl << endl;
		break;
	}
	case BOARD_ROLL_RnR: {
		//cast for specific msg type
		BoardMessage_RollInfo* specificMsg = static_cast<BoardMessage_RollInfo*> (msg);

		if (specificMsg->roll_ == 0) cout << endl << " ROUND < " << specificMsg->round_ << endl;
		cout << "\t\b\bRoll > " << specificMsg->roll_ << endl;

		break;
	}
	case BOARD_LOG_STRING: {
		//cast for specific msg type
		BoardMessage_String* specificMsg = static_cast<BoardMessage_String*> (msg);

		cout << specificMsg->messageText_;
		break;
	}
	}
}

///////////////////////////////////////////////////////////////////////////////

void BoardDebug_IC::handleEvents(Uint32 time, const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym)
		{
		case SDLK_c: //show controls again
			logControls();
			break;

		case SDLK_r: //reset the board and game
			cout << endl << "///// RESET ///// ONGOING GAME CANCELLED /////" << endl << endl;
			send(&Message(BOARD_RESET));
			break;

		case SDLK_u: //reset the board and game
			cout << endl << "///// UPDATING ///// PLAYERS POSITIONS /////" << endl << endl;
			send(&Message(BOARD_UPDATE_PLAYERS));
			break;

		case SDLK_d: //switch console log
			debugLog_ = !debugLog_;
			cout << endl << "///// SWITCHED LOG ///// to "
				<< to_string(debugLog_) << " /////" << endl << endl;
			break;

			//roll for specific player
		case SDLK_1: send(&BoardMessage_numPlayerInfo(0, false));
			break;
		case SDLK_2: send(&BoardMessage_numPlayerInfo(1, false));
			break;
		case SDLK_3: send(&BoardMessage_numPlayerInfo(2, false));
			break;
		case SDLK_4: send(&BoardMessage_numPlayerInfo(3, false));
			break;

			//dir keys
		case SDLK_SPACE: send(&Message(BOARD_SELECT));
			break;
		case SDLK_UP: send(&Message(BOARD_UP));
			break;
		case SDLK_DOWN: send(&Message(BOARD_DOWN));
			break;
		case SDLK_LEFT: send(&Message(BOARD_LEFT));
			break;
		case SDLK_RIGHT: send(&Message(BOARD_RIGHT));
			break;
		}
	}
}

void BoardDebug_IC::logControls()
{
	game_->logControls();
	cout << "//  * C : Show controls" << endl;
	cout << "//  " << endl;

	cout << "//  * 1 2 3 4 : manual roll to respective player" << endl;
	cout << "//  * R : Reset board, players and match" << endl;
	cout << "//  * U : Update player positions (order)" << endl;
	cout << "//  * D : Switch console logs // affects simulations" << endl;
	cout << "//  " << endl;
	cout << "//  * DIR KEYS: move while in menus" << endl;
	cout << "//  * SPACE : select while in menus" << endl;
	cout << "//  " << endl;

	send(&Message(BOARD_LOG_CONTROLS));
	cout << "//  " << endl;

	//cout << endl;
}

