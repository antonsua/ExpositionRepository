#include "WindowRenderer.h"
#include "EasyDefines.h"

#include <exception>

//Ogre
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreFileSystemLayer.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreStringConverter.h>

//SDL
#include <SDL_video.h>
#include <SDL_syswm.h>

WindowRenderer* WindowRenderer::instance_ = nullptr;

WindowRenderer::WindowRenderer() : mRoot(0) {
	initWindow();
}

void WindowRenderer::initWindow() {
	createRoot();
	setupResources();
	setupWindow();
	initializeResources();
	mRoot->addFrameListener(this);
}

WindowRenderer::~WindowRenderer() {
	if (mWindow != nullptr) {
		mRoot->destroyRenderTarget(mWindow);
		mWindow = nullptr;
	}

	delete mRoot;
	mRoot = nullptr;
}

WindowRenderer* WindowRenderer::getSingleton() {
	return instance_;
}

bool WindowRenderer::initSingleton() {
	if (instance_ == nullptr) {
		instance_ = new WindowRenderer();
		return true;
	}
	return false;
}

void WindowRenderer::createRoot()
{
	try
	{
		std::string configFileName = "";
#ifdef _DEBUG
		std::string pluginsFileName = "plugins_d.cfg";
		std::string logFileName = "Ogre_d.log";
#else
		std::string pluginsFileName = "plugins.cfg";
		std::string logFileName = "Ogre.log";
#endif

		mRoot = new Ogre::Root(pluginsFileName, configFileName, logFileName);

		// Asignar desde los plugins disponibles un sistema de renderizado
		const Ogre::RenderSystemList& lRenderSystemList = mRoot->getAvailableRenderers();
		if (lRenderSystemList.size() == 0) {
			MWARNING("Sorry, no rendersystem was found.");
		}
		
		renderSystem = lRenderSystemList[0];
		mRoot->setRenderSystem(renderSystem);
	}
	catch (Ogre::Exception & e) {
		MWARNING("!!!!Ogre::Exception!!!!" << e.what());
	}
	catch (std::exception & e) {
		MWARNING("!!!!std::exception!!!!" << e.what());
	}
}

void WindowRenderer::setupWindow() {
	std::string winTitle = "WeirdEngineWin";
	unsigned int winWidth = 1000;
	unsigned int winHeight = 800;
	unsigned int screenWidth = 0;
	unsigned int screenHeight = 0;

	//Creamos la ventana de Ogre
	mWindow = mRoot->initialise(true, winTitle);
	//mWindow->setFullscreen(true, 1920, 1080);

	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	screenWidth = desktop.right;
	screenHeight = desktop.bottom;

	mWindow->resize(winWidth, winHeight);
	mWindow->reposition(screenWidth / 2 - winWidth / 2, screenHeight / 2 - winHeight / 2);
	mWindow->windowMovedOrResized();
}

void WindowRenderer::initializeResources() {
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void WindowRenderer::setupResources() {
	Ogre::ConfigFile cf;
#if _DEBUG
	cf.load("resources_d.cfg");
#else
	cf.load("resources.cfg");
#endif

	std::string sec, type, arch;
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;

	//secciones
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci)
	{
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		//elementos de cada seccion
		for (i = settings.begin(); i != settings.end(); ++i)
		{
			type = i->first;
			arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;

	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);
}

void WindowRenderer::removeVp() {
	mWindow->removeAllViewports();
}

void WindowRenderer::renderFrame(float t) {
	mRoot->renderOneFrame();
}

bool WindowRenderer::handleEvents() {
	bool handled = false;
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_WINDOWEVENT_RESIZED:
			std::cout << "Resized\n";
			break;
		case SDL_WINDOWEVENT_MOVED:
			std::cout << "Moved\n";
			break;
		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
				std::cout << mWindow->getWidth() << ", " << mWindow->getHeight() << "\n";
				mWindow->windowMovedOrResized();
				windowResized(mWindow);
				handled = true;
			}
			break;

		case SDL_QUIT:
			windowClosed(mWindow);
			break;

		default:
			break;
		}
	}

	return handled;
}

void WindowRenderer::windowClosed()
{
	mWindow->destroy();
	//SDL_DestroyWindow(sdlWin);
}
