#pragma once
#include <CollisionEffectComponent.h>

class RespawnEffectComponent: public CollisionEffectComponent
{
public:
	RespawnEffectComponent(Container* e);
	~RespawnEffectComponent() {};

	void doEffect();

};

