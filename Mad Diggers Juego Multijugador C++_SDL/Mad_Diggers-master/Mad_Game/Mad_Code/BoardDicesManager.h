#ifndef BOARDDICESMANAGER_H_
#define BOARDDICESMANAGER_H_

#include "jsonReader.h"

#include "BoardDice.h"
#include "Emitter.h"

#include "Value_RC.h"
#include "FillRectRenderer.h"

#include "ShapeRenderer.h"
#include "message_RC.h"

class BoardDicesManager : public GameObject, public Emitter, public Listener
{
public:
	BoardDicesManager(Game* game, int numPlayers, jsonReader* jr);
	virtual ~BoardDicesManager();

	virtual void handleEvents(Uint32 time, const SDL_Event& event); //nothing
	virtual void update(Uint32 time); //nothing
	virtual void render(Uint32 time);

	virtual void receive(Message* msg);

	std::vector<BoardDice*>& getDices();

private:
	//constants
	const double dicesWidth_;	//width of the dices
	const double dicesHeight_;	//height of the dices
	const double selectorScale_; //times dices scale
	const double selectorDelay_;

	const double boardHorizGap_;		//width of the horizontal gap between squares
	const Vector2D topLeftBoardCorner_;	//position of the top-left corner

	const Vector2D msgTextScale_, msgTextOffset_;

	const double rollsTextScaleX_;
	const double rollsTextScaleY_;
	const Vector2D rollsTextOffset_;

	const int rollsMinDigits_;	//minimun digits

	vector<int> dicesValues_;

	///////////////////////////////////////////////////////////////////

	//default dices colors id
	static const Resources::ColorId _DEFAULT_DICES_COLOR_ID_;
	static const Resources::ColorId _DEFAULT_USED_COLOR_ID_;

	static const Resources::FontId _DEFAULT_TEXT_FONT_ID_;				//default text font id
	static const Resources::ColorId _DEFAULT_MSG_NAME_TEXT_COLOR_ID_;	//default message text color id

	static const vector<Resources::ShapeId> _DEFAULT_DICES_SHAPES_ID_;

	///////////////////////////////////////////////////////////////////

	void initDices();

	void initMsg();
	void initSelector();
	Vector2D getUpdatedSelectorPos();
	bool select();

	void setAllInactive();
	BoardDice* resetDice(BoardDice* dice, int numDice);

	BoardDice* getDice(int numDice);
	void createDice(int numDice, bool used, Vector2D pos);

	///////////////////////////////////////////////////////////////////

	int selectedDices_;

	vector<BoardDice*> dices_;
	Entity *selector_, *msg_;
	int numSelected_;

	ShapeRenderer shape_selector_RC_;
	vector<ShapeRenderer> shape_dices_RC_;

	Message_RC text_msg_RC_;				//msg
	spriteData textMsgData_;

	///////////////////////////////////////////////////////////////////

	const int numDices_;
	int numOfActiveDices_; //active squares
};

#endif /* BOARDDICESMANAGER_H_ */
