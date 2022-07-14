//#include "Manager.h"
//
//BoardSquaresManager::BoardSquaresManager(Game* game) : GameObject(game),
//rect_RC_(), text_RC_(), debug_RC_()
//{
//	initSquares();
//}
//
//BoardSquaresManager::~BoardSquaresManager()
//{
//	for (auto square : bees_)
//	{
//		delete square;
//	}
//	bees_.clear();
//}
//
/////////////////////////////////////////////////////////////////////////////////
//
//void BoardSquaresManager::handleInput(Uint32 time, const SDL_Event & event)
//{
//	//noting
//}
//
//void BoardSquaresManager::update(Uint32 time)
//{
//	for (auto square : bees_)
//	{
//		//only updatea active ones
//		if (square->isActive()) square->update(time);
//	}
//}
//
//void BoardSquaresManager::render(Uint32 time)
//{
//	for (auto square : bees_)
//	{
//		if (square->isActive()) square->render(time);
//	}
//}
//
/////////////////////////////////////////////////////////////////////////////////
//
//void BoardSquaresManager::receive(Message* msg) {
//	switch (msg->id_)
//	{
//	case BULLET_ASTEROID_COLLISION: {
//		//cast to get the specific msg type
//		BulletAstroidCollision* MsgBAColission = static_cast<BulletAstroidCollision*>(msg);
//		destroyBoardSquare(MsgBAColission->square_);
//		break;
//	}
//	case ASTEROID_FIGHTER_COLLISION: {
//		BoardSquareFighterCollision* MsgBAColission = static_cast<BoardSquareFighterCollision*>(msg);
//		destroyBoardSquare(MsgBAColission->square_);
//		break;
//	}
//
//	case ROUND_START: {
//		initSquares();
//		break;
//	}
//	}
//}
//
/////////////////////////////////////////////////////////////////////////////////
//
//void BoardSquaresManager::initSquares()
//{
//	const int initialAteroids = 3, initialGen = 1;
//	const double maxVel = 0.5, decimals = 1000;
//	const int width = game_->getWindowWidth(), height = game_->getWindowHeight();
//
//	setAllInactive();
//	for (size_t i = 0; i < initialAteroids; i++) {
//
//		Vector2D pos;
//		int border = game_->getRnd(3); //4 options
//
//		switch (border)
//		{
//		case 0: pos.set(game_->getRnd(width), 0); break;
//		case 1: pos.set(game_->getRnd(width), height); break;
//		case 2: pos.set(0, game_->getRnd(height)); break;
//		case 3: pos.set(width, game_->getRnd(height)); break;
//		}
//
//		double velX = (double)game_->getRnd(-maxVel * decimals, maxVel * decimals) / decimals;
//		double velY = (double)game_->getRnd(-maxVel * decimals, maxVel * decimals) / decimals;
//		Vector2D vel(velX, velY);
//
//		createBee(initialGen, pos, vel);
//	}
//}
//
//void BoardSquaresManager::createBee(int generations, Vector2D pos, Vector2D vel) {
//	BoardSquare* tmpBoardSquare = getSquares(); //gets an inactive or new one
//
//	tmpBoardSquare->setGenerations(generations);
//	tmpBoardSquare->setPosition(pos);
//	tmpBoardSquare->setVelocity(vel);
//
//	const int minSize = 20;
//	tmpBoardSquare->setWidth(minSize * (generations + 1));
//	tmpBoardSquare->setHeight(minSize * (generations + 1));
//}
//
//
//void BoardSquaresManager::setAllInactive()
//{
//	numOfSquares_ = 0;
//	for (auto square : bees_)
//	{
//		square->setActive(false);
//	}
//}
//
//std::vector<BoardSquare*>& BoardSquaresManager::getSquares()
//{
//	return bees_;
//}
//
//BoardSquare * BoardSquaresManager::getBee()
//{
//	numOfSquares_++;
//	//bool found = false; //lazy?
//
//	std::vector<BoardSquare*>::iterator it = bees_.begin();
//	while (it != bees_.end())
//	{
//		if (!(*it)->isActive()) {
//			(*it)->toggleActive();
//			return *it;
//		}
//		else ++it;
//	}
//
//	//no inactive found
//	BoardSquare* tmpBoardSquare = new BoardSquare(game_);
//	tmpBoardSquare->addRenderComponent(&square_image_RC);
//	tmpBoardSquare->addRenderComponent(&square_debug_RC_);
//	tmpBoardSquare->addPhysicsComponent(&square_CircularMotion_PC);
//	tmpBoardSquare->addPhysicsComponent(&square_Rotation_PC);
//
//	bees_.push_back(tmpBoardSquare);
//	return tmpBoardSquare;
//}
