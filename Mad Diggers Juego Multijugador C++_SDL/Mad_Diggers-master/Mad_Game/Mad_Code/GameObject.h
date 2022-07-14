//Mad_Diggers

#pragma once

#include "Game.h"
#include "Vector2D.h"
#include "Activable.h" //be activable

class GameObject : public Activable
{
public:
	GameObject() {};
	GameObject(Game* game);
	virtual ~GameObject();

	Game* getGame() const;

	// abstract methods to be implemented in sub-classes
	virtual void handleEvents(Uint32 time, const SDL_Event& event) = 0;
	virtual void update(Uint32 time) = 0;
	virtual void render(Uint32 time) = 0;

	bool isKilled() const;
	void kill();

protected:
	Game* game_; // pointer to the game

	bool killed_;   // indicates if the object is dead
};

