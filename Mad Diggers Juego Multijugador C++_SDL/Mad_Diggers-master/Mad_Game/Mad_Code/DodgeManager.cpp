#include "DodgeManager.h"

DodgeManager::DodgeManager(Game * game, stack<int>* p_playersTurnsOrder): GameObject(game), p_playersTurnsOrder_(p_playersTurnsOrder)
{
	basicPhysics = new BasicMotionPhysics();
	renderAnim = new AnimationRenderer(game_->getResources()->getSpriteSheetTexture(Resources::ss_SumoCD), &animData_, false);
	bulletRender = new ImageRenderer(game->getResources()->getImageTexture(Resources::i_bullet));
	terrainRender = new ImageRenderer(game->getResources()->getImageTexture(Resources::i_terrain));

	initPlayers();
	initGame();
}

void DodgeManager::initPlayers()
{
	infos.push_back({ SDLK_a, SDLK_d, SDLK_w, SDLK_s, Resources::_DEFAULT_PLAYERS_COLORS_ID_[0] });
	infos.push_back({ SDLK_g, SDLK_j, SDLK_y, SDLK_h, Resources::_DEFAULT_PLAYERS_COLORS_ID_[1] });
	infos.push_back({ SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN, Resources::_DEFAULT_PLAYERS_COLORS_ID_[2] });
	infos.push_back({ SDLK_KP_4, SDLK_KP_6, SDLK_KP_8, SDLK_KP_2, Resources::_DEFAULT_PLAYERS_COLORS_ID_[3] });

	for (int i = 0; i < infos.size(); i++)
	{
		GamePadComponent* gamepad = new GamePadComponent(i);
		DodgeComponent* dodgeC = new DodgeComponent(infos[i].left, infos[i].right, infos[i].up, infos[i].down, 0.4, 5, i);
		gamepad->registerListener(dodgeC);
		registerListener(dodgeC);
		playerRender.push_back(new ShapeRenderer(game_, Resources::s_BeeKeeper, infos[i].color));
		playerRender[i]->activateFlip();
		playerComponent.push_back(dodgeC);
		gamepads.push_back(gamepad);
		createPlayer(i);
	}
}

DodgeManager::~DodgeManager()
{
	for each (Entity* var in players)
	{
		delete var;
	}
	for each (ShapeRenderer* var in playerRender)
	{
		delete var;
	}
	for each (DodgeComponent* var in playerComponent)
	{
		delete var;
	}
	delete terrainRender;
	delete bulletRender;
	delete renderAnim;
	delete basicPhysics;
	delete countEntity;
	delete terrain;
}

void DodgeManager::update(Uint32 time)
{
	if (!start) {
		if (timer.checkRunning()) {
			timer.checkCountdown(time);
		}
		else {
			int rand = game_->getRnd(7);
			shootBarrage(rand);
			double tmpMult = roundMult;
			if (tmpMult > 8)
				tmpMult = 8;
			tmpMult -= 1;
			timer.startCountdown(time, 4000 /tmpMult);
			roundMult += 0.07;
		}
	}
	else if (!countEntity->isActive() && timer.checkRunning() && timer.checkCountdown(time)) 
			end = true;

	double tmpX, tmpY;
	if(!start)
	for each (Entity* var in players)
	{
		if (var->isActive()) {
			var->update(time);
			tmpX = var->getPosition().getX();
			tmpY = var->getPosition().getY();
			if (tmpX < 100)
				var->setPosition({ 100, var->getPosition().getY() });
			else if(tmpX > 700 - var->getWidth())
				var->setPosition({ 700 - var->getWidth(), var->getPosition().getY() });
			if (tmpY < 80)
				var->setPosition({ var->getPosition().getX(), 80 });
			else if (tmpY > 520 - var->getHeight())
				var->setPosition({ var->getPosition().getX(),  520 - var->getHeight() });
		}
	}
	if(!start)
	for each (Entity* var in bullets)
	{
		if (var->isActive()) {
			var->update(time);
			if (var->getPosition().getX() < -200 || var->getPosition().getX() > 1000 ||
				var->getPosition().getY() < -200 || var->getPosition().getY() > 800)
				var->setActive(false);
		}
	}
	if (countEntity->isActive())
		countEntity->update(time);
	updateCollision(time);

}

void DodgeManager::render(Uint32 time)
{
	if (terrain->isActive())
		terrain->render(time);
	for each (Entity* var in players)
	{
		if (var->isActive())
			var->render(time);
	}
	for each (Entity* var in bullets)
	{
		if (var->isActive())
			var->render(time);
	}
	if (countEntity->isActive())
		countEntity->render(time);


}

void DodgeManager::handleEvents(Uint32 time, const SDL_Event & event)
{
	if (!start)
		for each (Entity* var in players)
		{
			if (var->isActive())
				var->handleEvents(time, event);
		}
}

void DodgeManager::receive(Message * msg)
{
	if (msg->id_ == ANIMATION_ENDED) {
		start = false;
		countEntity->setActive(false);
	}
}

bool DodgeManager::checkEnd()
{
	return end;
}

void DodgeManager::collisionEvents(Physical * o1, Physical * o2)
{
}

void DodgeManager::updateCollision(Uint32 time)
{
	for (size_t i = 0; i < players.size(); i++)
	{
		if (players[i]->isActive()) {
			if (players[i]->getVelocity().getX() > 0.2)
				playerRender[i]->setFlipOrientation(SDL_FLIP_HORIZONTAL);
			else if (players[i]->getVelocity().getX() < -0.2)
				playerRender[i]->setFlipOrientation(SDL_FLIP_NONE);
			for each (Entity* var in bullets)
				if (var->isActive() && checkCollision(players[i], var)) {
					players[i]->setActive(false);
					var->setActive(false);
					p_playersTurnsOrder_->push(i);
					game_->sendToSM(&Message(DODGE_DEATH));
					if (p_playersTurnsOrder_->size() == 3)
						endGame(time);
				}
		}
	}
}

void DodgeManager::createPlayer(int numPlayer)
{
	Entity* player = new Entity(game_);
	player->setActive(true);
	player->addComponent(gamepads[numPlayer]);
	player->addComponent(playerComponent[numPlayer]);
	player->addComponent(playerRender[numPlayer]);
	player->addComponent(basicPhysics);
	player->setPosition({ 300.0 + numPlayer * 80.0,200.0 });
	player->setWidth(25);
	player->setHeight(25);
	players.push_back(player);
	playerRender[numPlayer]->setAlpha(0.0);
	playerRender[numPlayer]->fadeToAlpha(1.0, 3000);
}

void DodgeManager::endGame(Uint32 time)
{
		int i = 0;
		while (!players[i]->isActive())
			i++;
		p_playersTurnsOrder_->push(i);
		start = true;
		timer.startCountdown(time, 3000);
		bulletRender->fadeToAlpha(0.0, 1000);
		for each (ShapeRenderer* var in playerRender)
		{
			var->fadeToAlpha(0.0, 3000);
		}
		terrainRender->fadeToAlpha(0.0, 3000);
}

Entity * DodgeManager::getBullet()
{
	for each (Entity* var in bullets)
		if (!var->isActive())
			return var;
	Entity* bullet = new Entity(game_);
	bullet->addComponent(bulletRender);
	bullet->addComponent(basicPhysics);
	bullet->setWidth(33);
	bullet->setHeight(22);
	bullets.push_back(bullet);
	return bullet;
}

void DodgeManager::shootBullet(Vector2D pos, Vector2D vel)
{
	Entity* bullet = getBullet();
	bullet->setActive(true);
	bullet->setPosition(pos);
	bullet->setVelocity(vel);
	Vector2D dir = vel;
	dir.normalize();
	bullet->setDirection(dir);
}

void DodgeManager::shootBarrage(int side)
{
	int rand, rand2;
	if (side >= 0 && side < 8) {
		rand = game_->getRnd(5);
		if (rand < 3)
			rand = 3;
		else if (rand < 5)
			rand = 4;
		randomOrder(bulletsPos[side]);
		for (int i = 0; i < rand; i++) {
			rand2 = game_->getRnd(40);
			shootBullet(bulletsPos[side][i] - (bulletsVel[side] * rand2), bulletsVel[side] * roundMult * 0.7);
		}
	}
	game_->sendToSM(&Message(DODGE_SHOT));
}

void DodgeManager::randomOrder(vector<Vector2D>& vec)
{
	int rand, size;
	Vector2D tmp;
	size = vec.size();
	for (size_t i = 0; i < size; i++)
	{
		rand = game_->getRnd(size - 1);
		tmp = vec[rand];
		vec[rand] = vec[i];
		vec[i] = tmp;
	}
}


void DodgeManager::initGame()
{
	bulletsPos.push_back({ { -20, 105 },{ -20, 145 },{ -20, 185 },{ -20, 225 },{ -20, 265 },{ -20, 305 },{ -20, 345 },{ -20, 385 } });
	bulletsPos.push_back({ { -110,510 },{ -80, 540 },{ -50, 570 },{ -20, 600 },{  10, 630 },{  40, 660 },{  70, 690 },{ 100, 720 } });
	bulletsPos.push_back({ { 135, 600 },{ 195, 600 },{ 255, 600 },{ 315, 600 },{ 375, 600 },{ 435, 600 },{ 495, 600 },{ 555, 600 } });
	bulletsPos.push_back({ { 710, 690 },{ 740, 660 },{ 770, 630 },{ 800, 600 },{ 830, 570 },{ 860, 540 },{ 890, 510 },{ 920, 480 } });
	bulletsPos.push_back({ { 800, 105 },{ 800, 145 },{ 800, 185 },{ 800, 225 },{ 800, 265 },{ 800, 305 },{ 800, 345 },{ 800, 385 } });
	bulletsPos.push_back({ { 710,-110 },{ 740, -80 },{ 770, -50 },{ 800, -20 },{ 830,  10 },{ 860,  40 },{ 890,  70 },{ 920, 100 } });
	bulletsPos.push_back({ { 135, -20 },{ 195, -20 },{ 255, -20 },{ 315, -20 },{ 375, -20 },{ 435, -20 },{ 495, -20 },{ 555, -20 } });
	bulletsPos.push_back({ { -110, 70 },{ -80,  40 },{ -50,  10 },{ -20, -20 },{  10, -50 },{  40, -80 },{  70,-110 },{ 100,-140 } });
	countEntity = new Entity(game_);
	countEntity->setWidth(320);
	countEntity->setHeight(240);
	countEntity->setPosition(Vector2D(game_->getWindowWidth() / 2 - 160, game_->getWindowHeight() / 2 - 120));
	countEntity->addComponent(renderAnim);
	renderAnim->registerListener(this);
	renderAnim->start();
	terrain = new Entity(game_);
	terrain->setWidth(600);
	terrain->setHeight(440);
	terrain->setPosition(Vector2D(100, 80));
	terrain->addComponent(terrainRender);
	terrainRender->setAlpha(0.0);
	terrainRender->fadeToAlpha(1.0, 1000);
	bulletRender->setAlpha(0.0);
	bulletRender->fadeToAlpha(1.0, 1000);
}

