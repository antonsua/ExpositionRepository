#include "ApplesManager.h"
#include "AppleMiniGame.h"


ApplesManager::ApplesManager()
{
}

ApplesManager::ApplesManager(Game* game, AppleMiniGame* applMG) : GameObject(game),
objs_()
{

	registerListener(applMG);
	players_ = applMG->getPlayers();
}


ApplesManager::~ApplesManager()
{
	for (Apple* o : objs_)
		delete o;
}

Apple* ApplesManager::getObject(int colorIdentifier, const Resources::ColorId appleColor)
{
	typename std::vector<Apple*>::iterator it = objs_.begin();
	while (it != objs_.end() && (*it)->isActive()) {
		it++;
	}
	Apple* a = nullptr;
	if (it == objs_.end()) {
		a = new Apple(game_, appleColor);
		initializeObject(a, colorIdentifier);
		objs_.push_back(a);
	}
	else {
		a = *it;
		a->switchComponents(a->getRendererComp(), new ShapeRenderer(game_, Resources::s_hive, appleColor));
		a->setIdentifier(colorIdentifier);
		a->setVelocity(Vector2D(0, rand() % MAX_VEL + MIN_VEL));

	}

	return a;

}

void ApplesManager::initializeObject(Apple * o, int colorIdentifier)
{
	o->setIdentifier(colorIdentifier);
	o->addComponent(new AppleController(game_, o, this, colorIdentifier));
	o->setVelocity(Vector2D(0, rand() % MAX_VEL + MIN_VEL));

}

void ApplesManager::generateApple(int colorIdentifier, Resources::ColorId color)
{
	Apple* aux = getObject(colorIdentifier, color);
	aux->setActive(true);
	setRandomPosition(aux);
}

Resources::ColorId ApplesManager::getColorbyID(int colorIdentifier) const
{

	switch (colorIdentifier)
	{
	case 1:
		return Resources::c_Red;
		break;
	case 2:
		return Resources::c_Green;
		break;
	case 3:
		return Resources::c_Blue;
		break;
	case 4:
		return Resources::c_Pink;
		break;
	}
}

void ApplesManager::update(Uint32 time)
{
	for (auto it : objs_) {
		if (it->isActive()) {
			it->update(time);
		}
	}
	checkColl();
}

void ApplesManager::render(Uint32 time)
{
	for (auto it : objs_) {
		if (it->isActive()) {
			it->render(time);
		}

	}
}

void ApplesManager::receive(Message * msg)
{
	switch (msg->id_)
	{
	case SPAWN_APPLES:
		spawnApples(static_cast<SpawnApplesMG*>(msg));
		break;
	case APPLE_TOUCHED_FLOOR:
		send(&AppleDown(static_cast<AppleDown*>(msg)->colorIdentifier_));
		break;
	}
}

void ApplesManager::setRandomPosition(Apple * &a)
{
	a->setPosition(Vector2D((rand() % (game_->getWindowWidth() - INIT_POS_OFFSET_X) + 
		a->getWidth()), rand() % MAX_RND + MIN_RND));
}

void ApplesManager::spawnApples(SpawnApplesMG* msg)
{
	int auxColorID = msg->colorIdentifier_;
	Resources::ColorId auxColor = getColorbyID(auxColorID);

	for (int i = 0; i < msg->numberOfApples_; i++) {
		generateApple(auxColorID, auxColor);
	}
}

bool ApplesManager::rectangleCircleColl(const Circle &c, const RectanglePhysics &r) const
{
	float distX = abs(c.x - r.A.x - r.w / 2);
	float distY = abs(c.y - r.A.y - r.h / 2);

	if (distX > (r.w / 2 + c.r)) { return false; }
	if (distY > (r.h / 2 + c.r)) { return false; }

	if (distX <= (r.w / 2)) { return true; }
	if (distY <= (r.h / 2)) { return true; }

	float dx = distX - r.w / 2;
	float dy = distY - r.h / 2;
	return (dx*dx + dy * dy <= (c.r*c.r));
}

void ApplesManager::checkColl()
{
	bool found = false;
	for (auto a : objs_) {
		if (a->isActive()) {
			for (auto p : players_) {
				if (p != nullptr && !found && rectangleCircleColl(a->getCircle(), p->getRectangle()))
				{
					found = true;
					a->setActive(false);
					send(&PlayerGotApple(a->getIdentifier()));
				}
			}
		}
	}
}

