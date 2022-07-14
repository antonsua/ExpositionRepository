#include "ApplePlayerController.h"
#include "ApplePlayer.h"
#include "ApplesManager.h"

ApplePlayerController::ApplePlayerController(SDL_Keycode left, SDL_Keycode right, SDL_Keycode shake, SDL_Keycode exploit,
	ApplePlayer* player, AppleTree* tree) :
	left_(left), right_(right), shake_(shake), exploit_(exploit), tree_(tree)
{
	registerListener(player);
	playerSRC_ = player->getShapeRC();
}

ApplePlayerController::~ApplePlayerController()
{
}

void ApplePlayerController::handleEvents(Entity * o, Uint32 time, const SDL_Event & event)
{
	Vector2D velocity = o->getVelocity();

	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == left_) {
			keysHeld[0] = true;

		}
		else if (event.key.keysym.sym == right_) {
			keysHeld[1] = true;

		}
		if (event.key.keysym.sym == shake_) {
			send(&Message(SHAKING_TREE));
		}
		if (event.key.keysym.sym == exploit_ && tree_->getTicks() > 0) {
			send(&Message(DETONATE_TREE));
		}
	}
	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == left_)keysHeld[0] = false;
		if (event.key.keysym.sym == right_)keysHeld[1] = false;

	}

	if (keysHeld[0] || keysHeld[1]) {
		if (keysHeld[0]) {
			velocity.set(-PLAYER_VEL, 0);
			playerSRC_->setFlipOrientation(SDL_FLIP_NONE);
		}
		if (keysHeld[1]) {
			velocity.set(PLAYER_VEL, 0);
			playerSRC_->setFlipOrientation(SDL_FLIP_HORIZONTAL);
		}
	}
	else if (gamePadActive) {
		if (padVelocity < 0) {
			velocity.set(-PLAYER_VEL, 0);
			playerSRC_->setFlipOrientation(SDL_FLIP_NONE);
		}
		else {
			playerSRC_->setFlipOrientation(SDL_FLIP_HORIZONTAL);
			velocity.set(PLAYER_VEL, 0);
		}
	}
	else velocity.set(0, 0);

	o->setVelocity(velocity);

}

void ApplePlayerController::receive(Message * msg)
{
	switch (msg->id_)
	{
	case DPAD_LEFT:
		gamePadActive = true;
		padVelocity = -PLAYER_VEL;
		break;
	case DPAD_RIGHT:
		gamePadActive = true;
		padVelocity = PLAYER_VEL;
		break;
	case A:
		send(&Message(DETONATE_TREE));
		break;
	case X:
		send(&Message(SHAKING_TREE));
		break;
	default:
		gamePadActive = false;
		break;
	}
}
