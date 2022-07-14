#include "AppleTimer.h"



AppleTimer::AppleTimer(Game* game) : Entity(game)
{
	setHeight(104);
	setWidth(354);
	renderData = { Vector2D(0.6,0.6), Vector2D(game->getWindowWidth()/2-getWidth()/2,-6), false, false, };
	renderMSG_ = Message_RC (Resources::f_Hack_Bold_64, Resources::c_Honey, "",&renderData);
	addComponent(&renderMSG_);
}


AppleTimer::~AppleTimer()
{
}

void AppleTimer::update(Uint32 time)
{
	renderMSG_.setMsg("Time: " + to_string((int)(get_countDown_ticks() / 1000.0f)));
}


