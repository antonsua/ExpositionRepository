#pragma once

class WEManager;

enum Escenas {
	None, MainMenu, Nivel, Pause
};

class Game {
public:
	Game();
	~Game();

	void Init();
	bool update();

	static Game instance;
private:
	WEManager* _weM;

	void GenerateMainScene();
	void GenerateMenuScene();
	void GeneratePauseScene();

	//Eventos
	static void EventEnd();
	static void EventStart();

	int generateScene;
	bool changeScene;
};