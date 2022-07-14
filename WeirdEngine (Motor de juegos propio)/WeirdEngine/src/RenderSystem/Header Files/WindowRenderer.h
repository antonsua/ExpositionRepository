#pragma once

#include <OgreFrameListener.h>
#include <SDL.h>
#undef main

namespace Ogre {
	class RenderWindow;
	class RenderSystem;
	class Root;
	class Viewport;
}

class WindowRenderer : public Ogre::FrameListener
{
private:
	//We want it singleton
	static WindowRenderer* instance_; 

	Ogre::Root* mRoot = nullptr; // ogre root
	Ogre::RenderWindow* mWindow = nullptr; // ogre window
	//SDL_Window* sdlWin = nullptr; // window handled by SDL
	Ogre::RenderSystem* renderSystem = nullptr;

	
	// private constructor because of singleton pattern
	WindowRenderer();
	~WindowRenderer();

	void initWindow();
	void createRoot();
	void setupWindow();
	void initializeResources();
	void setupResources();
	
public:
	static WindowRenderer* getSingleton();
	static bool initSingleton();

	void removeVp();
	void renderFrame(float t);
	bool handleEvents();

	// Called when the frame starts rendering
	virtual bool frameStarted(const Ogre::FrameEvent& evt) { return true; };

	// Called when the frame ends rendering
	virtual bool frameEnded(const Ogre::FrameEvent& evt) { return true; };

	//Virtual methods, dont really need to be changed
	virtual void windowMoved(Ogre::RenderWindow* rw) { (void)rw; };
	virtual void windowResized(Ogre::RenderWindow* rw) { (void)rw; };
	virtual bool windowClosing(Ogre::RenderWindow* rw) { return true; };
	virtual void windowClosed(Ogre::RenderWindow* rw) { (void)rw; }
	virtual void windowClosed();
	virtual void windowFocusChange(Ogre::RenderWindow* rw) { (void)rw; };

	inline  Ogre::Root* getRoot() { return mRoot; };
	inline Ogre::RenderWindow* getWin() { return mWindow; };
};

