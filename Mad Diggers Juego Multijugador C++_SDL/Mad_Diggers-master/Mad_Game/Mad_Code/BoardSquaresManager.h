#ifndef BOARDSQUARESMANAGER_H_
#define BOARDSQUARESMANAGER_H_

#include "BoardSquare.h"
#include "BoardBee.h"
#include "Emitter.h"

#include "Value_RC.h"
#include "FillRectRenderer.h"
#include "ShapeRenderer.h"
#include "jsonReader.h"

class BoardSquaresManager : public GameObject, public Emitter, public Listener
{
public:
	BoardSquaresManager(Game* game, int numPlayers, int numSquares, jsonReader* jr);
	virtual ~BoardSquaresManager();

	virtual void handleEvents(Uint32 time, const SDL_Event& event); //nothing
	virtual void update(Uint32 time); //nothing
	virtual void render(Uint32 time);

	virtual void receive(Message* msg);

	virtual std::vector<BoardSquare*>& getSquares();

	///////////////////////////////////////////////////////////////////

	void startRoll(BoardPlayer * player, bool simulation, bool lastRoll);
	void preInteractRoll(BoardBee* bee);
	void interactRoll(BoardPlayer* player, int squareNum, bool lastRoll);

private:
	//constants
	 const bool sumPointsIfOwner_;

	 const double squaresWidth_;	//width of the squares
	 const double squaresHeight_;	//height of the squares

	 const Vector2D squareTextScale_, squareTextOffset_;

	 const double horizontalGap_;	//width of the horizontal gap between squares
	 const double verticalGap_;	//width of the vertical gap between squares

	 const bool hexTiled_;
	 const double horizontalHexGap_;	//width of the horizontal gap between squares
	 const double verticalHexGap_;	//width of the vertical gap between squares

	 const int squaresInitialNumber_;	//start in 0 or 1 or etc

	 const int cols_; //cnumber of cols in which the squares are fitted
	 const Vector2D topLeftBoardCorner_; //position of the top-left corner
	 const int squareMinDigits_; //minimun digits

	///////////////////////////////////////////////////////////////////

	static const Resources::ColorId _DEFAULT_SQUARES_COLOR_ID_; //default square color id

	static const Resources::FontId _DEFAULT_TEXT_FONT_ID_; //default text font id
	static const Resources::ColorId _DEFAULT_TEXT_COLOR_ID_; //default text color ids

	///////////////////////////////////////////////////////////////////

	void initSquares();
	void setAllInactive();
	BoardSquare * resetSquare(BoardSquare* square);

	BoardSquare* getSquare();
	void createSquare(int value, int boardPosition, Vector2D pos);

	int getBoardCol(int boardPositon); //based of the number of cols of the board
	int getBoardFil(int boardPositon); //based of the number of cols of the board

	///////////////////////////////////////////////////////////////////

	vector<BoardSquare*> squares_;

	Value_RC value_RC_;
	spriteData valueData_;

	FillRectRenderer rect_base_RC_;
	vector<FillRectRenderer> rect_players_RC_; //based on player's colors
	ShapeRenderer shape_base_RC_;
	vector<ShapeRenderer >shape_players_RC_;

	///////////////////////////////////////////////////////////////////

	SDL_Color* squaresColor_; //unactivated squares color
	vector<SDL_Color*> playersColors_; //each color

	int numSquares_;
	int numOfActiveSquares_; //active squares
};

#endif /* BOARDSQUARESMANAGER_H_ */
