#include "SDLGame.h"


SDLGame::SDLGame(string windowTitle, int width, int height) :
	windowTitle_(windowTitle), width_(width), height_(height)
{
	initSDL();
	initLoadingScreen();
	initResources();
}

SDLGame::~SDLGame() {
	closeResources();
	closeLoadingScreen();
	closeSDL();
}

// initialize SDL (ttf, mixer, image, create window and renderer, etc)
void SDLGame::initSDL() {
	SDL_Init(SDL_INIT_EVERYTHING);

	// SDL Fonts
	TTF_Init();

	// SDL Mixer (Music, Sound, etc)
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	// SDL Image
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);

	// Create window .
	window_ = SDL_CreateWindow(windowTitle_.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width_, height_, SDL_WINDOW_SHOWN);

	// Create the renderer
	renderer_ = SDL_CreateRenderer(window_, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Clear screen (background color).
	SDL_SetRenderDrawColor(renderer_, 0, 100, 100, 255);  // Dark grey.
	SDL_RenderClear(renderer_);
	SDL_RenderPresent(renderer_);

	// initialize the seed of the random number generator;
	srand(static_cast<unsigned int>(time(NULL)));
}

// close all SDL resources
void SDLGame::closeSDL() {

	SDL_DestroyRenderer(renderer_);
	renderer_ = nullptr;

	SDL_DestroyWindow(window_);
	window_ = nullptr;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();

	SDL_Quit();
}

void SDLGame::initLoadingScreen() {

	SDL_RenderClear(renderer_);

	loading_ = new Texture (renderer_, "images/menu/LoadingMenu.png");

	loading_->render(renderer_, RECT(0, 0, getWindowWidth(), getWindowHeight()));
	SDL_RenderPresent(renderer_);
}

void SDLGame::closeLoadingScreen() {
	if (loading_ != nullptr) delete loading_;
}

// initialize the SDLResources object
void SDLGame::initResources() {
	resources_ = new Resources(this);
}

// close the  SDLResources object (frees all memory)
void SDLGame::closeResources() {
	delete resources_;
}

///////////////////////////////////////////////////////////////////

SDL_Window* SDLGame::getWindow() const {
	return window_;
}

SDL_Renderer* SDLGame::getRenderer() const {
	return renderer_;
}

const Resources* SDLGame::getResources() const {
	return resources_;
}

int SDLGame::getWindowWidth() const {
	return width_;
}

int SDLGame::getWindowHeight() const {
	return height_;
}

SDL_Joystick* SDLGame::getController(){
	return controller_;
}

///////////////////////////////////////////////////////////////////

int SDLGame::getRnd() {
	return rand();
}
int SDLGame::getRnd(int max) {
	return getRnd(0, max);
}
int SDLGame::getRnd(int min, int max)
{
	//+1 to add max
	int amplitude = max - min + 1;

	return rand() % amplitude + min;
}
