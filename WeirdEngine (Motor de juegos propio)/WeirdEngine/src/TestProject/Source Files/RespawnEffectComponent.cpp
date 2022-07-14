#include "RespawnEffectComponent.h"

#include <iostream>
#include <Container.h>
#include <Messages_defs.h>
#include <PhysicsComponent.h>
#include <ComponentFactory.h>
#include <Vector3.h>

RespawnEffectComponent::RespawnEffectComponent(Container* e) : CollisionEffectComponent(e)
{
	_name = "RespawnEffect";
}

void RespawnEffectComponent::doEffect()
{
	//_parent->globalSend(this, msg::Respawn(msg::Player, msg::Broadcast));
}
