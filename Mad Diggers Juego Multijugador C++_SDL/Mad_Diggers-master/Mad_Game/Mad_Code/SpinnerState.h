#pragma once

#include "GameState.h"

#include "Entity.h"
#include "SpinnerManager.h"
#include "Spinner.h"
#include "ImageRenderer.h"
#include "AnimationRenderer.h"

class SpinnerState :public GameState, public Listener
{
public:
	SpinnerState(Game* game, MessageId* nextMinigame, int numPlayers);
	~SpinnerState();

	void handleEvents(Uint32 time, const SDL_Event event);
	void update(Uint32 time);
	void render(Uint32 time);

	void receive(Message* msg);

protected:
	void initState();
	void closeState();

private:
	void MoveWorld();

	MessageId* nextMinigame_; //pointer from boardState
	bool moving_, fromLeft_;

	///////////////////////////////////////////////////////////////////////////
	///constants
	const int numPlayers_;

	const Vector2D outWorldVel_;

	const Vector2D miniPlayersOffset_, miniplayersScaleEnd_;
	const double miniPlayerY_, miniPlayerW_, miniPlayerH_, miniplayersScaleTime_;

	const double msgY_, msgWaveMin_, msgWaveMax_, msgWaveTime_;

	///////////////////////////////////////////////////////////////////////////

	SpinnerManager* manager_;


	//spinner time animation
	Entity* snpinerMsg_;
	//ImageRenderer spinnerMsg_RC_;
	//spriteData spinnerMsgData_ = { Vector2D(1,1), Vector2D(0,0), false, false, };
	AnimationRenderer spinnerAnimation_;
	spriteSheetData spinnerAnimData_ =
	{
		Vector2D(1,1),
		Vector2D(0,0),
		false,
		0,0,
		0,0,
		24,
		true,
		true,
		false,
	};
	int animReps_ = 0;

	//mini players
	vector<AnimationRenderer> mini_player_Animation_;
	vector<Spinner*> mini_players_;
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
};