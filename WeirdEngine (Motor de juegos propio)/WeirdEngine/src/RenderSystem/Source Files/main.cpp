#include <iostream>
#include <OgreColourValue.h>

#include "WindowRenderer.h"
#include "RenderSystem.h"
#undef main


int main() {
	WindowRenderer* renderManager = WindowRenderer::getSingleton();
	RenderSystem* renderSystem = RenderSystem::getSingleton();

	renderSystem->materialGeneration("Mat");
	
	renderSystem->createScene("Scene");

	Ogre::SceneNode* n = renderSystem->addOgreEntity("Ninja", "ninja");
	Ogre::Entity* e = renderSystem->getEntityByName("Ninja");

	Ogre::SceneNode* l = renderSystem->createLight("Light", renderSystem->LT_DIRECTIONAL,
		Ogre::ColourValue(0.8f, 0.3f, 0.3f), Ogre::ColourValue(1.0f, 1.0f, 1.0f));

	renderSystem->setAmbientLight(Ogre::ColourValue(0.2f, 0.0f, 0.2f, 1.0f));


	bool exit_ = false;

	while (!exit_) {
		SDL_Event evt;

		while (SDL_PollEvent(&evt)) {
			if (evt.type == SDL_QUIT) {
				exit_ = true;
			}

			renderManager->handleEvents(evt);
		}
		//Ogre::WindowEventUtilities::messagePump();
		renderManager->renderFrame(0);
	}

	return 0;
}