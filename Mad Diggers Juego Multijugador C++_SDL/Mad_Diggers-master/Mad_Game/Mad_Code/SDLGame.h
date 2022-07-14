//Mad_Diggers

#ifndef SDLGAME_H_
#define SDLGAME_H_

#include "Resources.h" //brings all libraries too

class SDLGame {

public:

	SDLGame(string windowTitle, int width, int height);
	virtual ~SDLGame();

	// returns a pointer to the SDL window
	SDL_Window* getWindow() const;
	// returns a pointer to the SDL renderer
	SDL_Renderer* getRenderer() const;

	// returns the window width
	int getWindowWidth() const;
	// returns the window height
	int getWindowHeight() const;

	// returns a pointer to the resources
	const Resources* getResources() const;

	// returns a pointer to the game controller
	SDL_Joystick* getController();

	virtual void start() = 0; // implemented by subclasses
	virtual void stop() = 0;

	//returns a random positive int
	int getRnd();
	//returns a random int [0, max]
	int getRnd(int max);
	//returns a random int [min, max]
	int getRnd(int min, int max);

private:

	void initSDL();
	void closeSDL();

	void initLoadingScreen();
	void closeLoadingScreen();

	void initResources();
	void closeResources();

protected:

	// game's window
	SDL_Window* window_;
	// game's renderer
	SDL_Renderer* renderer_;
	// game controller
	SDL_Joystick* controller_ = nullptr;

	// resource (textures, font, music, etc)
	Resources* resources_;

	Texture* loading_;

	// window title
	string windowTitle_;

	// window width
	int width_;
	// window height
	int height_;
};

#endif /* SDLGAME_H_ */
