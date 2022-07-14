#ifndef BOARDBEESMANAGER_H_
#define BOARDBEESMANAGER_H_

#include "BoardBee.h"
#include "Emitter.h"
#include "jsonReader.h"

#include "ShapeRenderer.h"

class BoardBeesManager : public GameObject, public Emitter, public Listener
{
public:
	BoardBeesManager(Game* game, int numPlayers, jsonReader* jr);
	virtual ~BoardBeesManager();

	virtual void handleEvents(Uint32 time, const SDL_Event& event); //nothing
	virtual void update(Uint32 time); //nothing
	virtual void render(Uint32 time);

	virtual void receive(Message* msg);

	///////////////////////////////////////////////////////////////////

	//void interactRoll(BoardPlayer* player);

private:
	//constants
	const bool debug_ = false;

	const double beesWidth_, beesHeight_;	//w, h of the bee
	const Vector2D beesDir_;

	const int beesTime_;
	const bool complexMove_;

	const int beesRepMin_, beesRepMax_; //beeMovement
	const int beesRotMin_, beesRotMax_;
	const int beesDisMin_, beesDisMax_;

	const Vector2D topLeftCorner_; //limits bee movements
	const Vector2D botRightCorner_;

	const Vector2D bubbleOffset_;
	const Vector2D bubbleScale_;

	const Vector2D resizeScale_;
	const int resizeTime_;
	const double lastMovesMargin_;

	///////////////////////////////////////////////////////////////////

	void initBees();
	void setAllInactive();

	void createBee(Vector2D squarePos, int squareNum, BoardPlayer* player, bool lastBee);
	BoardBee* getBee(int numPlayer);
	BoardBee* resetBee (BoardBee* bee, int numPlayer);

	void setGotoPos(BoardBee* bee);
	void endBeeDance(BoardBee * bee);
	void endBeeResize(BoardBee * bee, bool ending);
	void endBeeMove(BoardBee * bee);

	Vector2D getSimplePosition(BoardBee * bee);
	bool isInside(Vector2D point);
	Vector2D getDefinitivePoint(BoardBee * bee);
	Vector2D getPoint(BoardBee * bee, double dis, double rot);
	Vector2D midPoint(double margin);

	///////////////////////////////////////////////////////////////////

	vector<BoardBee*> bees_;
	Vector2D spawnPoint_;

	vector<ShapeRenderer>shape_bees_RC_;
	ShapeRenderer shape_honey_bee_RC_;
	vector<ShapeRenderer>shape_bubble_RC_;
	spriteData bubbleData_;

	int numOfActiveBees_; //active bees
	int flyingBees_; //active bees
};

#endif /* BOARDBEESMANAGER_H_ */
