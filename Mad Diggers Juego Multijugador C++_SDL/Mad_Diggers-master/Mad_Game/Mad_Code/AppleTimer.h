#pragma once
#include "Timer.h"
#include "message_RC.h"
#include "Entity.h"
class AppleTimer : public Timer,public Entity
{
public:
	AppleTimer(Game* game);
	~AppleTimer();
	virtual void update(Uint32 time);
private:
	Message_RC renderMSG_;
	spriteData renderData;
};

