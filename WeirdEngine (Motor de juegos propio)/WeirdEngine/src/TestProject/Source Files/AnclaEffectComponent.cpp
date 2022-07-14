#include "AnclaEffectComponent.h"

#include <iostream>
#include <Container.h>
#include <Messages_defs.h>
#include <PhysicsComponent.h>
#include <ComponentFactory.h>
#include <Vector3.h>

CREATE_REGISTER(AnclaEffect);

AnclaEffectComponent::AnclaEffectComponent(Container* e) : CollisionEffectComponent(e)
{
	_name = "AnclaEffect";
}

void AnclaEffectComponent::doEffect()
{
	_parent->globalSend(this, msg::Colision(msg::Player, msg::Broadcast, "Ancla", true));
}

void AnclaEffectComponent::undoEffect()
{
	_parent->globalSend(this, msg::Colision(msg::Player, msg::Broadcast, "Ancla", false));
}
