#include <WEManager.h>

#include <iostream>
#include <CEGUI/CEGUI.h>

#include "Game.h"
#include "Utilities\Vector3.h"
#include "Utilities\Vector4.h"

Game Game::instance;

Game::Game() {
	_weM = new WEManager();
	changeScene = false;
	generateScene = Escenas::None;
}

Game::~Game() {
	delete _weM;
}

void Game::Init() {
	// Iniciamos el gm
	_weM->Init();

	//Escena de menus
	GenerateMainScene();
}

void Game::GenerateMainScene() {
	changeScene = false;
	_weM->setGUIVisible(false);
	// Generamos la escena
	_weM->generateScene("nivel1", Vector4{ 0.2, 0.0, 0.2, 0.8 });
}

void Game::GenerateMenuScene() {
	changeScene = false;
	_weM->generateScene("menu", Vector4{ 0.2, 0.0, 0.2, 0.8 });
	_weM->setGUIVisible(true);
	_weM->loadLayout("EmptyWindow");

	// A�adir a los botones los eventos correspondientes
	_weM->createButton("TaharezLook/Button", "PlayButton", "PLAY", { 0.4f, 0.3f, 0.1f, 0.2f }, { 0.0, 0.0 ,0.0 ,0.0 });
	_weM->addEventToButton("PlayButton", &Game::EventStart);
	_weM->createButton("TaharezLook/Button", "ExitButton", "EXIT", { 0.4f, 0.5f, 0.1f, 0.2f }, { 0.0, 0.0 ,0.0 ,0.0 });
	_weM->addEventToButton("ExitButton", &Game::EventEnd);
}

void Game::GeneratePauseScene() {
	changeScene = false;
	//_weM->generateScene("pause", "pause", Vector4{ 0.2, 0.0, 0.2, 0.8 });
	_weM->setGUIVisible(true);
	_weM->loadLayout("EmptyWindow");

	// A�adir a los botones los eventos correspondientes
	_weM->createButton("TaharezLook/Button", "PlayButton", "PLAY", { 0.4f, 0.3f, 0.1f, 0.2f }, { 0.0, 0.0 ,0.0 ,0.0 });
	_weM->addEventToButton("PlayButton", &Game::EventStart);
	_weM->createButton("TaharezLook/Button", "ExitButton", "EXIT", { 0.4f, 0.5f, 0.1f, 0.2f }, { 0.0, 0.0 ,0.0 ,0.0 });
	_weM->addEventToButton("ExitButton", &Game::EventEnd);
}

void Game::EventEnd() {
	instance._weM->close();
}

void Game::EventStart() {
	instance.changeScene = true;
	instance.generateScene = Escenas::Nivel;
}


bool Game::update() {
	bool state = _weM->update();
	if (changeScene) {
		switch (generateScene) {
		case Escenas::MainMenu:
			GenerateMenuScene();
			break;
		case Escenas::Nivel:
			GenerateMainScene();
			break;
		case Escenas::Pause:
			GeneratePauseScene();
			break;
		default:
			break;
		}
		
	}

	return state;
}
