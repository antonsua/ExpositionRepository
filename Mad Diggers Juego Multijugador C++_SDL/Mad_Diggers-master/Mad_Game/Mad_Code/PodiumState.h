#pragma once
#include "GameState.h"
#include "Listener.h"
#include "ImageRenderer.h"
#include "GoodTimer.h"
#include "GamePadComponent.h"

#include "AnimationRenderer.h"

const Vector2D NEXT_BUTTON_SIZE(199, 57);


class PodiumState :public GameState, public Listener
{
public:
	PodiumState(Game* game, std::stack<int>* playersinOrder, bool ending);
	~PodiumState();

	void initMiniPlayers();

	virtual void initState();
	virtual void closeState();
	void virtual handleEvents(Uint32 time, const SDL_Event event);
	void virtual update(Uint32 time);

	void receive(Message* msg);
private:
	const bool ending_;

	std::stack<int> playersinOrder_;
	Entity* podium_;
	Entity* padEntity_;
	Entity* next_;
	ImageRenderer podiumRender_;
	ImageRenderer nextRC_;
	GamePadComponent padIC_;
	GoodTimer timer;
	bool start = true;
	bool pause = true;

	//mini players

	const int numPlayers_;
	const Vector2D miniPlayersOffset_;
	const double miniPlayerW_, miniPlayerH_, miniplayersScaleTime_;


	vector<AnimationRenderer> mini_player_Animation_;
	vector<Entity*> mini_players_;
	vector<float> playersMove;
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

