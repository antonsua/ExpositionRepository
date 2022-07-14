#pragma once
#include <CollisionEffectComponent.h>

class AnclaEffectComponent : public CollisionEffectComponent
{
public:
	AnclaEffectComponent(Container* e);
	~AnclaEffectComponent() {};

	void doEffect();
	void undoEffect();
};

