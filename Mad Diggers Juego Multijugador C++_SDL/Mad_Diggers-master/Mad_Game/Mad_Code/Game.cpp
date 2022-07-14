#include "GameStateMachine.h" //fowarded
#include "Game.h"

#include "DemoMiniGame.h"
#include "PongMiniGame.h"
#include "BoardState.h"
#include "SumoMiniGame.h"
#include "SumoManager.h"

const string Game::_WINDOW_TITLE_ = "MAD GAME";

Game::Game() : SDLGame(_WINDOW_TITLE_, _WINDOW_WIDTH_, _WINDOW_HEIGHT_)
{
	Entity::initDebug();
	initGame();
}

Game::~Game()
{
	closeGame();
}

//creates the gameStateMachine, pushes the first state...
void Game::initGame() {
	// hide cursor
	SDL_ShowCursor(0);

	// create the machine and sound manager
	soundManager_ = new SoundManager(this);
	gameStateMachine_ = new GameStateMachine(this);

	exit_ = false;
}

//destroys the gameStateMachine
void Game::closeGame() {

	cout << endl << "closing game..." << endl;

	delete soundManager_;
	delete gameStateMachine_;
}

///////////////////////////////////////////////////////////////////

//main game loop, ends with exit_
void Game::run()
{
	exit_ = false;
	while (!exit_) {

		Uint32 startTime = SDL_GetTicks();

		handleEvents(startTime); //can set exit
		if (!exit_)
		{
			update(startTime);
			render(startTime);
		}

		//if the frame time is bigger than _MS_BETWEEN_FRAMES_ we just skip teh delay
		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < _MS_BETWEEN_FRAMES_)
			SDL_Delay(_MS_BETWEEN_FRAMES_ - frameTime);
	}
}

void Game::start() {
	run();
}

void Game::stop() {
	exit_ = true;
}

///////////////////////////////////////////////////////////////////

GameStateMachine * Game::getGSM()
{
	return gameStateMachine_;
}

///////////////////////////////////////////////////////////////////

//handle main SDL events (Ex. quit) and call the gameStateMachine machine update
void Game::handleEvents(Uint32 time)
{
	SDL_Event event;
	//global events that stops propagation handled here
	bool propagation = true;

	while (SDL_PollEvent(&event)) {

		//window x botton - close game
		if (event.type == SDL_QUIT)
		{
			propagation = false;
			stop();
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			//case SDLK_ESCAPE:
			//	propagation = false;
			//	stop();
			//	break;

			case SDLK_f:
				propagation = false;
				toggleFullscreen();
				break;

			case SDLK_m:
				sendToSM(&Message(VOLUP));
				break;
			case SDLK_n:
				sendToSM(&Message(VOLDOWN));
				break;
			}
		}

		if (propagation) gameStateMachine_->handleEvents(time, event);
	}
}
void Game::logControls() //handled by game
{
	cout << endl << "///// CONTROLS ///// board /////" << endl;
	cout << "//  " << endl;
	cout << "//  * ESC : Exit game" << endl;
	cout << "//  * F : Full screen" << endl;
}

//sends message to Sound Manager specifically
void Game::sendToSM(Message * msg)
{
	soundManager_->receive(msg);
}

//calls gameStateMachine update
void Game::update(Uint32 time)
{
	gameStateMachine_->update(time);
}

//clears, calls gameStateMachine update and presents
void Game::render(Uint32 time)
{
	gameStateMachine_->render(time);
}

///////////////////////////////////////////////////////////////////

//switches between fullscreen and the original window size
void Game::toggleFullscreen()
{
	int flags = SDL_GetWindowFlags(window_);

	if (flags & SDL_WINDOW_FULLSCREEN) {
		SDL_SetWindowFullscreen(window_, 0);
	}
	else {
		SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
	}
}