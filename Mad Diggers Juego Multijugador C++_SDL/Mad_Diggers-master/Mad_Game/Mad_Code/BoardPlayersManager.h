#ifndef BOARDPLAYERSMANAGER_H_
#define BOARDPLAYERSMANAGER_H_

#include "jsonReader.h"
#include "Emitter.h"

#include "BoardPlayer.h"

#include "Value_RC.h"
#include "message_RC.h"
#include "ShapeRenderer.h"
#include "AnimationRenderer.h"

class BoardPlayersManager : public GameObject, public Emitter, public Listener
{
public:
	BoardPlayersManager(Game* game, int numPlayers, jsonReader* jr);
	virtual ~BoardPlayersManager();

	virtual void handleEvents(Uint32 time, const SDL_Event& event); //nothing
	virtual void update(Uint32 time); //nothing
	virtual void render(Uint32 time);

	virtual void receive(Message* msg);

	virtual std::vector<BoardPlayer*>& getPlayers();
	virtual std::vector<int> getPlayersScores();

	std::stack<int> getPlayersOrdered();

private:
	//constants
	const double playerWidth_;	//width of the player in the boardState
	const double playerHeight_;	//height of the player in the boardState

	const double boardVerticalGap_;		//width of the vertical gap between squares
	const Vector2D topLeftBoardCorner_;	//position of the top-left corner

	const Vector2D playerHeadScale_, playerHeadOffset_;

	const Vector2D pointsTextScale_, pointsTextOffset_;
	const Vector2D pointsEventsTextScale_, pointsEventsTextOffset_, pointsEventsInternOffset_;
	const double pointsShowUpScale_, pointsShowUpOffset_;

	const double playerQueuedScaleX_, playerQueuedScaleY_;
	const Vector2D playerQueuedOffset_, playerQueuedBoardCorner_;

	const Vector2D bubbleOffset_, bubbleScale_;

	const Vector2D showUpOffset_, showUpScale_;
	const int showUpDelay_;

	const int playerInitialNumber_, playerInitialPoints_;		//start in 0 or 1 or etc
	const int playerPointsMinDigits_;	//minimun digits

	const int playerPointsEventsFadeTime_, playerUpdatePositionsTime_, spinnerMsgFade_, spinnerAnimTimes_;

   ///////////////////////////////////////////////////////////////////

	static const Resources::ColorId _COLOR_PLAYER_NAME_TEXT_; //default player name text color id

	static const Resources::FontId _F_DEFAULT_TEXT_, _F_POINTSEVENTS_; //fonts
	static const Resources::ColorId _C_POINTS_TEXT_, _C_POINTSEVENTS_ADD_, _C_POINTSEVENTS_SUB_; //colors

	///////////////////////////////////////////////////////////////////

	void initPlayers();
	void setAllInactive();
	BoardPlayer* resetPlayer(BoardPlayer * player, int numPlayer);

	BoardPlayer* getPlayer(int numPlayer);
	void createPlayer(int numPlayer, int points, Vector2D pos);

	///////////////////////////////////////////////////////////////////

	void updatePlayersPos();
	queue<int> getOrderedPlayers(bool reversed = false);

	void showUpPlayer(bool reverse);
	void updatePointEvents(int points, int numPlayer);
	void endPointsUpdates();
	void endTurnActions();
	void nextTurnActions();

	void initQueuedPlayers();
	void orderDrawingQueue(std::stack<int> p_playersTurnsOrder);
	void renderQueuedPlayerPos();

	///////////////////////////////////////////////////////////////////

	vector<BoardPlayer*> players_;
	vector<Entity*> playersQueued_;
	//vector<pair<Entity*>> playersQueued_;
	list <Entity*> drawingQueue_;

	//main players
	vector<ShapeRenderer> head_players_RC_;
	spriteData headData_;

	//main points
	vector<Value_RC> points_RC_;
	vector<spriteData> pointsData_;

	//every player has 4 different pointsEvents_RC_
	vector<vector<Message_RC>> pointsEvents_Vector_RC_;
	vector<spriteData> pointsEventsData_;

	//mini players queued
	vector<AnimationRenderer> mini_player_Animation_;
	spriteSheetData miniAnimData_ =
	{
		Vector2D(1,1),
		Vector2D(0,0),
		false,
		0,0,
		0,0,
		10,
		true,
		true,
		false,
	};

	//spinner time animation
	Entity* snpinerMsg_;
	AnimationRenderer spinnerAnimation_;
	spriteSheetData spinnerAnimData_ =
	{
		Vector2D(1,1),
		Vector2D(0,0),
		false,
		0,0,
		0,0,
		20,
		true,
		true,
		false,
	};
	int animReps_ = 0;
	//ImageRenderer spinnerMsg_RC_;
	//spriteData spinnerMsgData_ = { Vector2D(1,1), Vector2D(0,0), false, false, };

	vector<ShapeRenderer>shape_bubble_RC_; //unused
	spriteData bubbleData_;

	///////////////////////////////////////////////////////////////////

	stack<int> p_playersTurnsOrder_;
	int showUpPlayerNumber_, updatedPlayers_, pointsFading_;
	bool waitingFade_, waitingForReverseShow_;

	int numPlayers_;
	int numOfActivePlayers_; //active squares
};

#endif /* BOARDSQUAREMANAGER_H_ */
