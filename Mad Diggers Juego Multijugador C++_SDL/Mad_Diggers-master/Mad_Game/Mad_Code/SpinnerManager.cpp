#include "SpinnerManager.h"

vector<MessageId> SpinnerManager::minigameIds = {
	STATE_SUMO,
	STATE_PONG,
	STATE_APPLE,
	STATE_PLATFORM,
	STATE_RACE,
	STATE_DODGE,
};
vector<Resources::ImageId> SpinnerManager::minigameImagesIds = {
	Resources::i_spin_sumo,
	Resources::i_spin_pong,
	Resources::i_spin_apple,
	Resources::i_spin_platform,
	Resources::i_spin_race,
	Resources::i_spin_dodge,
};

///////////////////////////////////////////////////////////////////////////////

SpinnerManager::SpinnerManager(Game* game, jsonReader* jr)
	: GameObject(game), minigame_RC(),
	bgImage_(game->getResources()->getImageTexture(Resources::i_spinBack)),
	fgImage_(game->getResources()->getImageTexture(Resources::i_spinFront)),
	interrogation_RC(game->getResources()->getImageTexture(Resources::i_Interr)),

#define json jr->read()["SpinnerManager"] //Macro to short

	baseTime(json["baseTime"].asDouble()),
	speedReductionFactor(json["speedReductionFactor"].asDouble()),
	repetitionsMin(json["repetitionsMin"].asUInt()),
	repetitionsMax(json["repetitionsMax"].asUInt()),

	spinY(json["spinY"].asDouble()),
	spinH(json["spinH"].asDouble()),
	spinW(json["spinW"].asDouble()),

	bgWtimesSpin(json["bgWtimesSpin"].asDouble()),
	bgHtimesSpin(json["bgHtimesSpin"].asDouble()) {
	///end initi list

	//calculate centered positions
	bgW = bgWtimesSpin * spinW;
	bgH = bgHtimesSpin * spinH;
	bgPos_ = Vector2D(game_->getWindowWidth() / 2 - bgW / 2, spinY);

	double diff = bgH - spinH;
	endPos = bgPos_ + Vector2D(diff /2, diff/2);
	startPos = bgPos_ + Vector2D(bgW - spinW - diff / 2, diff / 2);

	initBackGround();
	initSpinner();
	initForeGround();

	spinOnce();
}

SpinnerManager::~SpinnerManager() {
	for (GameObject* o : objects_) {
		if (o != nullptr) {
			delete o;
		}
	}

	if (idCarrier != nullptr) {
		delete idCarrier;
	}
}

void SpinnerManager::initSpinner() {
	reps = 0;
	lastRep = game_->getRnd(repetitionsMin, repetitionsMax);

	spinner_ = new Spinner(game_);
	objects_.push_back(spinner_);
	spinner_->registerListener(this);

	spinner_->setWidth(spinW);
	spinner_->setHeight(spinH);

	spinner_->addComponent(&interrogation_RC);
}

void SpinnerManager::initBackGround() {
	backGround_ = new Entity(game_);
	objects_.push_back(backGround_);

	backGround_->setPosition(bgPos_);
	backGround_->setWidth(bgW);
	backGround_->setHeight(bgH);

	backGround_->addComponent(&bgImage_);
}

void SpinnerManager::initForeGround() {
	foreGround_ = new Entity(game_);
	objects_.push_back(foreGround_);

	foreGround_->setPosition(bgPos_);
	foreGround_->setWidth(bgW);
	foreGround_->setHeight(bgH);

	foreGround_->addComponent(&fgImage_);
}

///////////////////////////////////////////////////////////////////////////////

void SpinnerManager::handleEvents(Uint32 time, const SDL_Event & event) {
	//nothing
}

void SpinnerManager::render(Uint32 time) {
	for (GameObject* o : objects_) {
		if (o != nullptr && o->isActive()) {
			o->render(time);
		}
	}
}

void SpinnerManager::update(Uint32 time) {
	for (GameObject* o : objects_) {
		if (o != nullptr && o->isActive()) {
			o->update(time);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

void SpinnerManager::spinOnce() {
	reps++;

	spinner_->setPosition(startPos);
	spinner_->moveToPoint(endPos, baseTime * pow(speedReductionFactor, reps));
}

void SpinnerManager::spinLast() {
	reps++;
	pickMinigame();
	spinner_->setPosition(startPos);

	double
		x = game_->getWindowWidth() / 2 - spinW / 2,
		y = endPos.getY();
	spinner_->moveToPoint(Vector2D(x,y), baseTime);
}

void SpinnerManager::receive(Message* msg) {
	if (!isActive()) return;

	switch (msg->id_) {
	case BOARD_SPINNED:
		if (reps < lastRep) {
			spinOnce();
		}
		else if (reps == lastRep) {
			spinLast();
		}
		else send(idCarrier); //end
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////

void SpinnerManager::pickMinigame() {
	int rnd = game_->getRnd(minigameIds.size() - 1);
	minigame_RC.setImage(game_->getResources()->getImageTexture(minigameImagesIds[rnd]));

	idCarrier = new Message(minigameIds[rnd]);
	spinner_->switchComponents(&interrogation_RC, &minigame_RC);

	minigameImagesIds.erase(minigameImagesIds.begin() + rnd);
	minigameIds.erase(minigameIds.begin() + rnd);
}
