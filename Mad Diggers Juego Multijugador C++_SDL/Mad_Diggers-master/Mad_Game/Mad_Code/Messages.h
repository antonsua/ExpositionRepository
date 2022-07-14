#ifndef MESSAGES_H_
#define MESSAGES_H_

#include <string>
#include <vector>
#include "Vector2D.h"
#include <stack>


class ControlsState;
class BoardPlayer;
class BoardBee;
class Paddle;
class AppleMiniGame;

enum MessageId
{
	//general game
	VOLUP,
	VOLDOWN,
	ENDING,

	//gameStates machine
	STATE_POP,
	STATE_POP_MINIGAME,
	STATE_END_GAME,
	STATE_END_MINIGAME,
	STATE_MENU,
	STATE_RULES,
	STATE_BOARD,

	STATE_PODIUM,
	STATE_PODIUM_END,

	STATE_NULL,
	STATE_DEMO,
	STATE_SUMO,
	STATE_PONG,
	STATE_APPLE,
	STATE_PLATFORM,
	STATE_RACE,
	STATE_DODGE,
	STATE_CREDITS,
	STATE_CREDITS_EXT,
	STATE_SUMO_CONTROLS,
	STATE_PONG_CONTROLS,
	STATE_APPLE_CONTROLS,
	STATE_CONTROLS_POP,
	STATE_CONTROLS_PLATFORM,
	STATE_PLAT_CHALLENGE,
	STATE_BULLET_CONTROLS,

	//board and squares
	BOARD_INIT,
	BOARD_SPINNER,
	BOARD_RESET,
	BOARD_GAMEOVER,
	BOARD_PLAYER_TURNOVER,
	BOARD_PLAYER_STARTED,

	BOARD_RESET_DICES,
	BOARD_UPDATE_PLAYERS,
	BOARD_UPDATE_QUEUE,
	BOARD_GO_QUEUE,
	BOARD_POP_QUEUE,

	BOARD_LOG_CONTROLS,
	BOARD_LOG_STRING,

	BOARD_ROLL_P,
	BOARD_ROLL_NumP,
	BOARD_ROLL_RnR,
	BOARD_ROLL_End,
	BOARD_ROLL_PointsEvents,
	BOARD_ROLL_PointsOwned,
	BOARD_ROLL_PointsFaded,

	BOARD_FADE_spinner,
	BOARD_END_TURN,

	BOARD_ROLL_Bee,
	BOARD_ROLL_BeeEnd,
	BOARD_ROLL_BeeSquared,
	BOARD_ROLL_BeeSpawn,
	BOARD_BEE_Reached,
	BOARD_BEE_Resize,
	BOARD_BEE_ResetSize,

	BOARD_SELECT,
	BOARD_SELECTED,
	BOARD_RIGHT,
	BOARD_LEFT,
	BOARD_UP,
	BOARD_DOWN,

	BOARD_SPINNED,
	BOARD_SPINNED_SIZE,
	BOARD_STARTMSG_WAVE,
	BOARD_STARTMSG_FADED,
	BOARD_ENDMSG_WAVE,
	BOARD_ENDMSG_FADED,

	//general minigames / or whatever
	MINIGAME_GAME_OVER,
	MINIGAME_ROUND_START,
	MINIGAME_ROUND_OVER,
	UPDATE_GUI,

	ANIMATION_ENDED,
	ANIMATION_LOOPED,

	//SumoMiniGame Messages
	SUMOGAME_OUT_FROM_AREA,
	SUMOGAME_PLACE_REACHED,
	SUMO_BOUNCE,

	//AppleMiniGame Messages
	SHAKING_TREE,
	DETONATE_TREE,
	SPAWN_APPLES,
	APPLE_TOUCHED_FLOOR,
	PLAYER_CAUGTH_APPLE,

	//PongMinigame Messages
	BALL_BLOCK_COLLISION,
	BALL_PADDLE_COLLISION,

	//PlatformMinigame Messages
	PLATFORM_COLLISION,
	TRAP_COLLISION,
	JUMP,
	PLATFORM_DEATH,
	RACE_DEATH,

	//Dodge Messages
	DODGE_SHOT,
	DODGE_DEATH,

	//axis input
	MOVE_1,
	MOVE_2,
	NO_MOVE,

	//gamePad Messages
	A, B, X, Y,
	DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT,
	RB, LB,
	START,
	BACK,
	GUIDE,
	JOYRIGHT_UP, JOYRIGHT_DOWN, JOYRIGHT_RIGHT, JOYRIGHT_LEFT,
	JOYLEFT_UP, JOYLEFT_DOWN, JOYLEFT_RIGHT, JOYLEFT_LEFT,
	RT, LT,
	uA, uB, uX, uY,
	uDPAD_UP, uDPAD_DOWN, uDPAD_LEFT, uDPAD_RIGHT,
	uRB, uLB,
	uSTART,
	uBACK,
	uGUIDE,
	//JOYRIGHT_UP, JOYRIGHT_DOWN, JOYRIGHT_RIGHT, JOYRIGHT_LEFT,
	//JOYLEFT_UP, JOYLEFT_DOWN, JOYLEFT_RIGHT, JOYLEFT_LEFT,
	uRT, uLT,
};

struct Message {
	Message(){}
	Message(MessageId id) :
		id_(id) {
	}
	MessageId id_;
};

///////////////////////////////////////////////////////////////////////////////
//states machine messages

struct StateMessage_Menu : Message {
	StateMessage_Menu(MessageId id, bool resetStack = false) :
		Message(id), resetStack_(resetStack) {}

	bool resetStack_;
};

struct StateMessage_Minigame : Message {
	StateMessage_Minigame(MessageId id, std::stack<int>* p_playersTurnsOrder) :
		Message(id), p_playersTurnsOrder_(p_playersTurnsOrder) {}

	std::stack<int> *p_playersTurnsOrder_;
};

struct StateMessage_Spinner : Message
{
	StateMessage_Spinner(MessageId* nextMinigame, int numPlayers) :
		Message(BOARD_SPINNER), nextMinigame_(nextMinigame), numPlayers_(numPlayers) {
	}

	MessageId* nextMinigame_;
	int numPlayers_;
};

///////////////////////////////////////////////////////////////////////////////
//board messages

struct BoardMessage_QueueInfo : Message {
	BoardMessage_QueueInfo(std::stack<int>* p_playersTurnsOrder) :
		Message(BOARD_UPDATE_QUEUE), p_playersTurnsOrder_(p_playersTurnsOrder) {}

	std::stack<int> *p_playersTurnsOrder_;
};

struct BoardMessage_ResetDices : Message
{
	BoardMessage_ResetDices(int playerTurn) :
		Message(BOARD_RESET_DICES), playerTurn_(playerTurn) {
	}

	int playerTurn_;
};

//main roll interactive msg
struct BoardMessage_PlayerInfo : Message {
	BoardMessage_PlayerInfo(BoardPlayer* player, bool simulation, bool lastRoll) :
		Message(BOARD_ROLL_P), player_(player), simulation_(simulation), lastRoll_(lastRoll) {}

	BoardPlayer* player_;
	bool simulation_, lastRoll_;
};

//selected dice info
struct BoardMessage_DiceInfo : Message {
	BoardMessage_DiceInfo(int rolls) :
		Message(BOARD_SELECTED), rolls_(rolls) {}

	int rolls_;
};
struct BoardMessage_BeeSpawnPoint : Message {
	BoardMessage_BeeSpawnPoint(Vector2D* pos) :
		Message(BOARD_ROLL_BeeSpawn), pos_(pos) {}

	Vector2D* pos_;
};
struct BoardMessage_SelectorColor : Message {
	BoardMessage_SelectorColor(int playerNumeber) :
		Message(BOARD_PLAYER_TURNOVER), playerNumber_(playerNumeber) {}

	int playerNumber_;
};

//roll bee information
struct BoardMessage_BeeRollInfo : Message {
	BoardMessage_BeeRollInfo(BoardPlayer* player, int squareNum, Vector2D pos, bool lastRoll) :
		Message(BOARD_ROLL_Bee), player_(player), squareNum_(squareNum), pos_(pos), lastRoll_(lastRoll) {}

	BoardPlayer* player_;
	int squareNum_;
	bool lastRoll_;
	Vector2D pos_;
};
struct BoardMessage_BeeFinished : Message {
	BoardMessage_BeeFinished(BoardPlayer* player, int squareNum, bool lastRoll) :
		Message(BOARD_ROLL_BeeEnd), player_(player), squareNum_(squareNum), lastRoll_(lastRoll) {}

	BoardPlayer* player_;
	int squareNum_;
	bool lastRoll_;
};
struct BoardMessage_BeeSquared : Message {
	BoardMessage_BeeSquared(BoardBee* bee) :
		Message(BOARD_ROLL_BeeSquared), bee_(bee) {}

	BoardBee* bee_;
};
struct BoardMessage_BeeReached : Message {
	BoardMessage_BeeReached(BoardBee* bee) :
		Message(BOARD_BEE_Reached), bee_(bee) {}

	BoardBee* bee_;
};
struct BoardMessage_BeeResized : Message {
	BoardMessage_BeeResized(BoardBee* bee) :
		Message(BOARD_BEE_Resize), bee_(bee) {}

	BoardBee* bee_;
};
struct BoardMessage_BeeResetSize : Message {
	BoardMessage_BeeResetSize(BoardBee* bee) :
		Message(BOARD_BEE_ResetSize), bee_(bee) {}

	BoardBee* bee_;
};

//roll player point events
struct BoardMessage_PointsEvents : Message {
	BoardMessage_PointsEvents(int points, int numPlayer) :
		Message(BOARD_ROLL_PointsEvents), points_(points), numPlayer_(numPlayer) {}

	int points_, numPlayer_;
};

//ending info for simulator (ex.)
struct BoardMessage_GameOverResults : Message {
	BoardMessage_GameOverResults(std::vector<int> playerScores) :
		Message(BOARD_GAMEOVER), playerScores_(playerScores) {}

	std::vector<int> playerScores_;
};

//debug controls
struct BoardMessage_numPlayerInfo : Message {
	BoardMessage_numPlayerInfo(int numPlayer, bool bees) :
		Message(BOARD_ROLL_NumP), numPlayer_(numPlayer), bees_(bees){}

	int numPlayer_;
	bool bees_;
};

//debug logging information
struct BoardMessage_RollInfo : Message {
	BoardMessage_RollInfo(int round, int roll) :
		Message(BOARD_ROLL_RnR), round_(round), roll_(roll) {}

	int round_, roll_;
};
struct BoardMessage_String : Message {
	BoardMessage_String(std::string s) :
		Message(BOARD_LOG_STRING), messageText_(s) {}

	std::string messageText_;
};

///////////////////////////////////////////////////////////////////////////////
//Dodge Component

struct Message_PlatformCollision : Message {
	Message_PlatformCollision(int player, bool collision) :
		Message(PLATFORM_COLLISION), player_(player), collision_(collision) {
	}
	int player_;
	bool collision_;
};

struct Message_TrapCollision : Message {
	Message_TrapCollision(int player) :
		Message(TRAP_COLLISION), player_(player) {
	}
	int player_;
};

///////////////////////////////////////////////////////////////////////////////
//Pong Messages

struct Message_BallLimits : Message {
	Message_BallLimits(int player) :
		Message(MINIGAME_ROUND_OVER), player_(player) {
	}
	int player_;
};

struct PongMessage_BallPaddleCollision : Message {
	PongMessage_BallPaddleCollision(Paddle* paddle) :
		Message(BALL_PADDLE_COLLISION), paddle_(paddle) {}

	Paddle* paddle_;
};
//////////////////////////////////////////////////
//Apple Messages
struct SpawnApplesMG : Message {
	SpawnApplesMG(int colorIdentifier, int numberOfApples) :
		Message(SPAWN_APPLES), colorIdentifier_(colorIdentifier),
		numberOfApples_(numberOfApples){}

	int colorIdentifier_;
	int numberOfApples_;
};
struct AppleDown : Message {
	AppleDown(int colorIdentifier) :
		Message(APPLE_TOUCHED_FLOOR), colorIdentifier_(colorIdentifier){}

	int colorIdentifier_;
};
struct PlayerGotApple : Message {
	PlayerGotApple(int colorIdentifier) :
		Message(PLAYER_CAUGTH_APPLE), colorIdentifier_(colorIdentifier) {}

	int colorIdentifier_;
};
struct UpdateAppleGUI : Message {
	UpdateAppleGUI(int playerID,int newScore) :
		Message(UPDATE_GUI), playerID_(playerID), newScore_(newScore) {}

	int playerID_;
	int newScore_;
};

/////////////// Gamepad
struct PressedAPAD : Message {
	PressedAPAD(int playerPadID) :
		Message(A), playerPadID_(playerPadID) {}

	int playerPadID_;
};
struct ControlsSumoMessage : Message {
	ControlsSumoMessage(ControlsState* c_state) :
		Message(STATE_SUMO_CONTROLS), c_state_(c_state) {}

	ControlsState* c_state_;
};
struct AppleControlsPop : Message {
	AppleControlsPop(AppleMiniGame* miniGame) :
		Message(STATE_APPLE_CONTROLS), miniGame_(miniGame) {}

	AppleMiniGame* miniGame_;
};
#endif /* MESSAGES_H_ */
