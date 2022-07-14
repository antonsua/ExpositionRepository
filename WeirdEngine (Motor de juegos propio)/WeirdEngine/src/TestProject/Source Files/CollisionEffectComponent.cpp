#include "CollisionEffectComponent.h"

#include <iostream>
#include <Container.h>
#include <Messages_defs.h>
#include <PhysicsComponent.h>
#include <ComponentFactory.h>
#include <Vector3.h>


CREATE_REGISTER(CollisionEffect);

CollisionEffectComponent::CollisionEffectComponent(Container* e) 
{
	_name = "CollisionEffect";
	_parent = e;
}

void CollisionEffectComponent::Init(std::unordered_map<std::string, std::string>& param) 
{
	_pc = static_cast<PhysicsComponent*>(_parent->getComponent("Physics"));

	setUpdate();
}

void CollisionEffectComponent::update(Container* c, float time)
{
	if (_pc->isColliding() && !buffActive)
	{
		doEffect();
		buffActive = true;
		startTime = clock(); //Start timer
	}
	if (buffActive)
	{
		secondsPassed = (clock() - startTime) / CLOCKS_PER_SEC;
		if (secondsPassed >= effectTime)
		{
			secondsPassed = 0;
			buffActive = false;
			undoEffect();
		}
	}
}

void CollisionEffectComponent::doEffect()
{
	_parent->globalSend(this, msg::Colision(msg::Player, msg::Broadcast, _name, true));
}

void CollisionEffectComponent::undoEffect()
{
	_parent->globalSend(this, msg::Colision(msg::Player, msg::Broadcast, _name, false));
}