#include "PlatformManager.h"



PlatformManager::PlatformManager(Game* game, stack<int> *p_playersTurnsOrder, int gamemode) : GameObject(game), p_playersTurnsOrder_(p_playersTurnsOrder), basicPhysics(), gamemode_(gamemode)
{
	basicPhysics = new BasicMotionPhysics();
	renderAnim = new AnimationRenderer(game_->getResources()->getSpriteSheetTexture(Resources::ss_SumoCD), &animData_, false);
	blockRender = new ImageRepeatRender(game_->getResources()->getImageTexture(Resources::i_pBlock), 20, 20);
	trapRender = new ShapeRenderer(game_, Resources::s_beehive, Resources::c_Yellow_light);
	finishRender = new ImageRenderer(game_->getResources()->getImageTexture(Resources::i_gem));
	level = 0;
	while (p_playersTurnsOrder->size() != 0)
		p_playersTurnsOrder->pop();

	initFinish();
	initPlayers();
	initLevels();
	createLevel(level);
}

void PlatformManager::initPlayers()
{
	infos.push_back({ SDLK_a, SDLK_d, SDLK_w, SDLK_s, Resources::_DEFAULT_PLAYERS_COLORS_ID_[0] });
	infos.push_back({ SDLK_g, SDLK_j, SDLK_y, SDLK_h, Resources::_DEFAULT_PLAYERS_COLORS_ID_[1] });
	infos.push_back({ SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN, Resources::_DEFAULT_PLAYERS_COLORS_ID_[2] });
	infos.push_back({ SDLK_KP_4, SDLK_KP_6, SDLK_KP_8, SDLK_KP_2, Resources::_DEFAULT_PLAYERS_COLORS_ID_[3] });

	for (int i = 0; i < infos.size(); i++)
	{
		GamePadComponent* gamepad = new GamePadComponent(i);
		PlatformGameComponent* pgc = new PlatformGameComponent(infos[i].left, infos[i].right, infos[i].up, infos[i].down, 0.4, 4, 4.5, i);
		gamepad->registerListener(pgc);
		registerListener(pgc);
		playerRender.push_back(new ShapeRenderer(game_, Resources::s_BeeKeeper, infos[i].color));
		playerRender[i]->activateFlip();
		playerComponent.push_back(pgc);
		gamepads.push_back(gamepad);
		createPlayer(i);
	}
}

void PlatformManager::initFinish()
{
	finish = new Entity(game_);
	finish->addComponent(finishRender);
	finish->setWidth(35);
	finish->setHeight(30);
	finish->setPosition({ 150,60 });
	countEntity = new Entity(game_);
	countEntity->setWidth(320);
	countEntity->setHeight(240);
	countEntity->setPosition(Vector2D(game_->getWindowWidth() /2 - 160, game_->getWindowHeight() / 2 - 120));
	countEntity->addComponent(renderAnim);
	renderAnim->registerListener(this);
}

void PlatformManager::playerFinish(int p)
{
	playerWin.push_back(p);
	players[p]->setActive(false);
	if (playerWin.size() == 3 - level) {
		start = true;
		blockRender->setAlpha(1.0);
		blockRender->fadeToAlpha(0.0, 2000);
		trapRender->setAlpha(1.0);
		trapRender->fadeToAlpha(0.0, 2000);
		finishRender->setAlpha(1.0);
		finishRender->fadeToAlpha(0.0, 2000);
		for each (ShapeRenderer* var in playerRender)
		{
			var->setAlpha(1.0);
			var->fadeToAlpha(0.0, 2000);
		}
	}
}


PlatformManager::~PlatformManager()
{
	for each (Entity* var in players)
	{
		delete var;
	}
	for each (Entity* var in platforms)
	{
		delete var;
	}
	for each (Entity* var in traps)
	{
		delete var;
	}
	for each (ShapeRenderer* var in playerRender)
	{
		delete var;
	}
	for each (PlatformGameComponent* var in playerComponent)
	{
		delete var;
	}
	for each (PatrolPhysics* var in platformPhysics)
	{
		delete var;
	}
	delete finishRender;
	delete blockRender;
	delete renderAnim;
	delete basicPhysics;
	delete finish;
	delete countEntity;
}

void PlatformManager::update(Uint32 time)
{
	if(!start)
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->isActive()) {
			players[i]->update(time);
			if (players[i]->getVelocity().getX() > 0.2)
				playerRender[i]->setFlipOrientation(SDL_FLIP_HORIZONTAL);
			else if (players[i]->getVelocity().getX() < -0.2)
				playerRender[i]->setFlipOrientation(SDL_FLIP_NONE);
			if (players[i]->getPosition().getY() > game_->getWindowHeight() + 10) {
				send(&Message_TrapCollision(i));
				game_->sendToSM(& Message(PLATFORM_DEATH));
			}
		}
	}
	for each (Entity* var in platforms)
	{
		if (var->isActive()) var->update(time);
	}
	for each (Entity* var in traps)
	{
		if (var->isActive()) var->update(time);
	}
	if (countEntity->isActive())
		countEntity->update(time);
	updateCollision(time);
	if (timer.checkRunning() && timer.checkCountdown(time))
		endLevel();
}

void PlatformManager::render(Uint32 time)
{
	for each (Entity* var in players)
	{
		if (var->isActive()) 
			var->render(time);
	}
	for each (Entity* var in platforms)
	{
		if (var->isActive())
			var->render(time);
	}
	for each (Entity* var in traps)
	{
		if (var->isActive())
			var->render(time);
	}
	if (finish->isActive())
		finish->render(time);
	if (countEntity->isActive())
		countEntity->render(time);
}

void PlatformManager::handleEvents(Uint32 time, const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_1)
			nextLevel();
	}
	if(!start)
		for each (Entity* var in players)
		{
			if (var->isActive())
				var->handleEvents(time, event);
		}
}

void PlatformManager::receive(Message * msg)
{
	if (msg->id_ == ANIMATION_ENDED) {
		start = false;
	}
}

bool PlatformManager::checkEnd()
{
	return end;
}

void PlatformManager::collisionEvents(Physical * o1, Physical * o2)
{
	
	if (checkCollisionTop(o1, o2)) {
		if (o1->getVelocity().getY() <= 0 || o2->getVelocity().getY() > 0) {
		o1->setVelocity(Vector2D(o1->getVelocity().getX(), 1));
		o1->setPosition(Vector2D(o1->getPosition().getX(), o2->getPosition().getY() + o2->getHeight()));
		}
	}
	if (checkCollisionBot(o1, o2)) {
		if (o2->getVelocity().getY() != 0 || o1->getVelocity().getY() > 0.1)
			o1->setPosition(Vector2D(o1->getPosition().getX(), o2->getPosition().getY() - o1->getHeight()));
		if (o1->getVelocity().getY() > 0)
			o1->setVelocity(Vector2D(o1->getVelocity().getX(), 0));
		if (o2->getVelocity().getX() != 0)
			o1->setPosition(o1->getPosition() + o2->getVelocity());
		if (o2->getVelocity().getY() > 0) 
			o1->setVelocity(Vector2D(o1->getVelocity().getX(), o2->getVelocity().getY()));
	}
	if (checkCollisionRight(o1, o2) && (o1->getVelocity().getX() > 0 || o2->getVelocity().getX() < 0)) {
		o1->setPosition(Vector2D(o2->getPosition().getX() - o1->getWidth(), o1->getPosition().getY()));
		o1->setVelocity(Vector2D(0, o1->getVelocity().getY()));
	}
	if (checkCollisionLeft(o1, o2) && (o1->getVelocity().getX() < 0 || o2->getVelocity().getX() > 0)) {
		o1->setPosition(Vector2D(o2->getPosition().getX() + o2->getWidth(), o1->getPosition().getY()));
		o1->setVelocity(Vector2D(0, o1->getVelocity().getY()));
	}
	
}


void PlatformManager::updateCollision(Uint32 time)
{
	for (int i = 0; i < players.size(); i++)
	{

		if (checkCollision(players[i], finish) && players[i]->isActive() && !start) {
			playerFinish(i);
			if(playerWin.size() == 3 - level)
				timer.startCountdown(time, 2500);
		}

		if (players[i]->isActive()) {

			send(&Message_PlatformCollision(i, true));
			for each (Entity* var in platforms)
			{
				if (var->isActive()) {
					collisionEvents(players[i], var);
					if (checkCollision(Vector2D(players[i]->getPosition().getX() + 3, players[i]->getPosition().getY() + players[i]->getHeight() + 1), players[i]->getWidth() - 3, var)) 
						send(&Message_PlatformCollision(i, false));
				}
			}
			for each (Entity* var in traps)
			{
				if (var->isActive()) {
					if (checkCollision(players[i], var)) {
						send(&Message_TrapCollision(i));
						game_->sendToSM(& Message(PLATFORM_DEATH));
					}
				}
			}
		}
	}
}

void PlatformManager::createPlayer(int numPlayer)
{
	Entity* player = new Entity(game_);
	player->setActive(true);
	player->addComponent(gamepads[numPlayer]);
	player->addComponent(playerComponent[numPlayer]);
	player->addComponent(playerRender[numPlayer]);
	player->addComponent(basicPhysics);
	send(& Message_TrapCollision(numPlayer));
	player->setWidth(25);
	player->setHeight(25);
	players.push_back(player);
}

Entity* PlatformManager::createPlatform(Vector2D position, double width, double height, bool trap)
{
	Entity* platform = new Entity(game_);
	platform->setActive(true);
	platform->setPosition(position);
	platform->setWidth(width);
	platform->setHeight(height);
	if (trap) {
		platform->addComponent(trapRender);
		traps.push_back(platform);	}
	else {
		platform->addComponent(blockRender);
		platforms.push_back(platform);
	}
	return platform;
}

void PlatformManager::createPlatform(Vector2D position, double width, double height, bool trap, Vector2D velocity, Uint32 turnTime)
{
	Entity* platform = createPlatform(position,width,height,trap);
	platformPhysics.push_back(new PatrolPhysics(velocity, turnTime));
	platform->addComponent(platformPhysics.back());
	platform->addComponent(basicPhysics);
}

void PlatformManager::createLevel(int i)
{
	start = true;
	for each (Entity* var in platforms)
	{
		var->setActive(false);
	}
	for each (Entity* var in traps)
	{
		var->setActive(false);
	}
	finish->setPosition({ levels[i].finishX, levels[i].finishY });
	for each (PlatformGameComponent* var in playerComponent)
	{
		var->setIniPosition({ levels[i].startX, levels[i].startY });
	}
	for each (Entity* var in players)
	{
		var->setPosition({ levels[i].startX, levels[i].startY });
	}
	for each (ShapeRenderer* var in playerRender)
	{
		var->setAlpha(0.0);
		var->fadeToAlpha(1.0, 2000);
	}
	for each (platformInfo var in levels[i].platforms)
	{
		createPlatform({var.x, var.y}, var.w, var.h, var.trap);
	}
	for each (mobilePlatform var in levels[i].mobileplatforms)
	{
		createPlatform({ var.platform.x, var.platform.y }, var.platform.w, var.platform.h, var.platform.trap, {var.velX, var.velY}, var.turnTime);
	}
	blockRender->setAlpha(0.0);
	blockRender->fadeToAlpha(1.0, 2000);
	trapRender->setAlpha(0.0);
	trapRender->fadeToAlpha(1.0, 2000);
	finishRender->setAlpha(0.0);
	finishRender->fadeToAlpha(1.0, 2000);
	renderAnim->start();
}

void PlatformManager::nextLevel()
{
	
	level++;
	if (level > 2) {
		end = true;
		if(playerWin.size() == 1)
			p_playersTurnsOrder_->push(playerWin[0]);
	}
	else {
		for (int i = 0; i < playerWin.size(); i++)
		{
			players[playerWin[i]]->setPosition(Vector2D(-1, game_->getWindowHeight()));
			players[playerWin[i]]->setActive(true);
		}
		playerWin = vector<int>{};
		createLevel(level);
	}
}

void PlatformManager::endLevel()
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->isActive()) {
			p_playersTurnsOrder_->push(i);
			players[i]->setActive(false);
		}
	}
	if (gamemode_ == 0)
		nextLevel();
	else if (gamemode_ == 1) {
		for (int i = playerWin.size() - 1; i >= 0; i--) {
			p_playersTurnsOrder_->push(playerWin[i]);
		}
		end = true;
	}
}

void PlatformManager::initLevels()
{
	levelInfo level;
	vector<platformInfo> platforms, platforms1, platforms2;
	vector<mobilePlatform> mplatforms, mplatforms1, mplatforms2;
	switch (gamemode_)
	{
	case 0:
	{
		//LEVEL 1
		platforms.push_back({ 0,0 , 20, 600, false });
		platforms.push_back({ 790, 0 , 20, 600, false });
		platforms.push_back({ 0,0 , 800, 20, false });
		platforms.push_back({ 405, 100, 40, 600, false });
		platforms.push_back({ 500, 20, 40, 400, false });
		platforms.push_back({ 0,560 , 80, 40, false });
		platforms.push_back({ 190,520 , 40, 80, false });
		platforms.push_back({ 260,480 , 40, 120, false });
		platforms.push_back({ 310,440 , 40, 160, false });
		platforms.push_back({ 80,370 , 180, 20, false });
		platforms.push_back({ 80,350 , 60, 20, false });
		platforms.push_back({ 20,330 , 60, 60, false });
		platforms.push_back({ 445,520 , 120, 80, false });
		platforms.push_back({ 610,480 , 40, 120, false });
		platforms.push_back({ 690,440 , 40, 160, false });
		platforms.push_back({ 720, 290 , 60, 20, false });
		platforms.push_back({ 570, 290 , 60, 20, false });
		platforms.push_back({ 640, 210 , 60, 20, false });
		platforms.push_back({ 690, 130 , 60, 20, false });
		mplatforms.push_back({ { 130, 250 , 60, 20, false }, 2.2, 0, 1400 });
		mplatforms.push_back({ { 100, 120 , 60, 20, false }, 2.5, 0, 1200 });
		mplatforms.push_back({ { 230, 180 , 60, 20, false }, -2, 0, 1200 });
		mplatforms.push_back({ { 570, 365 , 60, 20, false }, 2, 0, 1100 });
		level.platforms = platforms;
		level.mobileplatforms = mplatforms;
		level.finishX = 705;
		level.finishY = 60;
		level.startX = 40;
		level.startY = 500;
		levels.push_back(level);
		//LEVEL 2
		platforms1.push_back({ 0,0 , 40, 600, false });
		platforms1.push_back({ 0,560 , 800, 40, false });
		platforms1.push_back({ 760, 0 , 40, 600, false });
		platforms1.push_back({ 0,0 , 800, 40, false });
		platforms1.push_back({ 0,150 , 720, 20, false });
		platforms1.push_back({ 100,320 , 800, 20, false });
		platforms1.push_back({ 0,440 , 720, 20, false });
		for (int i = 0; i < 5; i++) {
			platforms1.push_back({ 160 + (double)i * 140,40 , 20, 40, false });
			platforms1.push_back({ 100 + (double)i * 140,110 , 20, 40, false });
		}
		for (int i = 0; i < 4; i++) {
			platforms1.push_back({ 160 + (double)i * 180,280 , 60, 40, false });
			platforms1.push_back({ 130 + (double)i * 160,220 , 40, 20, false });
		}
		for (int i = 0; i < 4; i++) {
			platforms1.push_back({ 100 + (double)i * 180,380 , 20, 20, false });
			platforms1.push_back({ 120 + (double)i * 180,380 , 20, 60, false });
			platforms1.push_back({ 140 + (double)i * 180,400 , 20, 40, false });
		}
		for (int i = 0; i < 3; i++) {
			mplatforms1.push_back({ { 120 + (double)i * 180, 540 , 60, 20, false }, 2, 0, 1200 });
			mplatforms1.push_back({ { 260 + (double)i * 180, 460 , 60, 20, false }, -2, 0, 1200 });
		}
		level.platforms = platforms1;
		level.mobileplatforms = mplatforms1;
		level.finishX = 60;
		level.finishY = 500;
		level.startX = 50;
		level.startY = 60;
		levels.push_back(level);
		//LEVEL 3
		platforms2.push_back({ 150, 490 , 80, 120, false });
		platforms2.push_back({ 500,130 , 40, 20, false });
		platforms2.push_back({ 260,125 , 40, 20, false });
		platforms2.push_back({ 535,480 , 100, 20, false });
		platforms2.push_back({ 535,360 , 80, 20, false });
		platforms2.push_back({ 740,405 , 80, 200, false });
		platforms2.push_back({ 230,540 , 220, 100, false });
		platforms2.push_back({ 260,320 , 20, 60, false });
		platforms2.push_back({ 260,430 , 20, 60, false });
		platforms2.push_back({ 330,300 , 20, 60, false });
		platforms2.push_back({ 330,420 , 20, 60, false });
		platforms2.push_back({ 390,320 , 20, 60, false });
		platforms2.push_back({ 390,430 , 20, 60, false });
		platforms2.push_back({ 450,330 , 20, 60, false });
		platforms2.push_back({ 150,240 , 20, 60, false });
		platforms2.push_back({ 50,170 , 20, 60, false });
		platforms2.push_back({ 450,440 , 20, 180, false });
		platforms2.push_back({ 0,0 , 20, 600, false });
		platforms2.push_back({ 780,0 , 20, 600, false });
		platforms2.push_back({ 0,560 , 80, 40, false });
		level.platforms = platforms2;
		level.mobileplatforms = mplatforms2;
		level.finishX = 720;
		level.finishY = 100;
		level.startX = 40;
		level.startY = 500;
		levels.push_back(level);
	}
		break;
	case 1:
		if (game_->getRnd(1) == 0) {
			platforms2.push_back({ 150, 560 , 460, 60, false });
			platforms2.push_back({ 5, 140, 80, 20, false });
			platforms2.push_back({ 80,70 , 20, 100, false });
			platforms2.push_back({ 0,0 , 20, 600, false });
			platforms2.push_back({ 0,560 , 80, 40, false });
			mplatforms2.push_back({ { 730, 540 , 60, 20, false }, 0, -2.5, 1400 });
			mplatforms2.push_back({ { 610, 120 , 60, 20, false }, 0, 2.5, 1400 });
			mplatforms2.push_back({ { 510, 100 , 60, 20, false }, -1.5, 0, 1500 });
			mplatforms2.push_back({ { 230, 60 , 60, 20, false }, -1.5, 0, 1500 });
			mplatforms2.push_back({ { 360, 160 , 60, 20, false }, -1.5, 0, 1500 });
			mplatforms2.push_back({ { 400, 80 , 60, 20, false }, 1.5, 0, 1500 });
			mplatforms2.push_back({ { 120, 40 , 60, 20, false }, 1.5, 0, 1500 });
			mplatforms2.push_back({ { 250, 140 , 60, 20, false }, 1.5, 0, 1500 });
			mplatforms2.push_back({ { 100, 470 , 30, 30, true }, 4.5, 0, 1800 });
			platforms2.push_back({ 150, 535 , 25, 25, true });
			platforms2.push_back({ 250, 535 , 25, 25, true });
			platforms2.push_back({ 350, 535 , 25, 25, true });
			platforms2.push_back({ 450, 535 , 25, 25, true });
			platforms2.push_back({ 575, 535 , 25, 25, true });
			level.platforms = platforms2;
			level.mobileplatforms = mplatforms2;
			level.finishX = 20;
			level.finishY = 90;
			level.startX = 40;
			level.startY = 500;
			levels.push_back(level);
		}
		else {
			platforms1.push_back({ 0,560 , 100, 40, false });
			mplatforms1.push_back({ { 170, 500 , 60, 20, false }, 0, -1, 1300 });
			mplatforms1.push_back({ { 380, 500 , 80, 20, false }, 1, 0, 3000 });
			platforms1.push_back({ 330, 450 , 60, 20, false });
			platforms1.push_back({ 680, 450 , 80, 20, false });
			platforms1.push_back({ 750, 375 , 60, 20, false });
			platforms1.push_back({ 330, 80 , 100, 20, false });
			platforms1.push_back({ 600, 330 , 40, 20, false });
			platforms1.push_back({ 390, 290 , 60, 20, false });
			platforms1.push_back({ 245, 240 , 60, 20, false });
			platforms1.push_back({ 245, 120 , 60, 20, false });
			platforms1.push_back({ 105, 175 , 60, 20, false });
			mplatforms1.push_back({ { 250, 470 , 40, 40, true }, 0, -4, 640 });
			mplatforms1.push_back({ { 463, 440 , 35, 35, true }, 0, -3.5, 720 });
			mplatforms1.push_back({ { 550, 300 , 35, 35, true }, 0, 3.5, 720 });
			mplatforms1.push_back({ { 180, 240 , 50, 50, true }, 0, -4.8, 840 });
			platforms1.push_back({ 680, 360 , 30, 30, true });
			platforms1.push_back({ 450, 280 , 30, 30, true });
			level.platforms = platforms1;
			level.mobileplatforms = mplatforms1;
			level.finishX = 370;
			level.finishY = 40;
			level.startX = 40;
			level.startY = 500;
			levels.push_back(level);
		}
		break;
	case 2:
		break;
	default:
		break;
	}
}
//platforms.push_back({ 150, 490 , 80, 120, false });
//platforms.push_back({ 0, 420, 80, 20, false });
//platforms.push_back({ 140,350 , 80, 20, false });
//platforms.push_back({ 5, 300 , 80, 20, false });
//platforms.push_back({ 140,240 , 80, 20, false });
//platforms.push_back({ 5,180 , 80, 20, false });
//platforms.push_back({ 500,130 , 80, 20, false });
//platforms.push_back({ 260,125 , 80, 20, false });
//platforms.push_back({ 655,480 , 100, 20, false });
//platforms.push_back({ 740,400 , 80, 200, false });
//for (int i = 0; i < 5; i++)
//	platforms.push_back({ 350 + (double)i * 25,110 , 25, 25, true });
//for (int i = 0; i < 5; i++)
//	platforms.push_back({ 350 + (double)i * 25,0 , 25, 25, true });
//for (int i = 0; i < 10; i++)
//	platforms.push_back({ 678,140 + 30 * (double)i , 30, 30, true });
//for (int i = 0; i < 10; i++)
//	platforms.push_back({ 600,140 + 30 * (double)i , 30, 30, true });
//for (int i = 0; i < 4; i++)
//	platforms.push_back({ 708 + 30 * (double)i,140  , 30, 30, true });
//platforms.push_back({ 0,420 , 20, 180, false });
//platforms.push_back({ 0,560 , 80, 40, false });
//level.platforms = platforms;
//level.mobileplatforms = mplatforms;
//level.finishX = 740;
//level.finishY = 320;
//level.startX = 40;
//level.startY = 500;
//levels.push_back(level);