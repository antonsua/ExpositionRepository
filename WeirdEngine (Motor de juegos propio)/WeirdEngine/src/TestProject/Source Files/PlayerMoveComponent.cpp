#include "PlayerMoveComponent.h"

#include <iostream>
#include <Container.h>
#include <Messages_defs.h>
#include <PhysicsComponent.h>
#include <ComponentFactory.h>
#include <Vector3.h>
#include <ctime>
#include <cstdlib>

CREATE_REGISTER(PlayerMove);

PlayerMoveComponent::PlayerMoveComponent(Container* e) {
	_name = "PlayerMove";
	_parent = e;
	_velocity = new Vector3(0,0,0);
}

void PlayerMoveComponent::Init(std::unordered_map<std::string, std::string>& param) {
	_pc = static_cast<PhysicsComponent*>(_parent->getComponent("Physics"));
	setUpdate();
}

void PlayerMoveComponent::update(Container* c, float time)
{
	_pc->checkColliding();
	if (_pc->isColliding())
	{
		//std::cout << "[" << _pc->GetID() << "]: " << "Está colisionando" << std::endl;
	}

	_pc->move(*_velocity);

}

void PlayerMoveComponent::receive(Container* c, const msg::Message& _msg)
{
	switch (_msg.type_)
	{
	case msg::MOVE: {
		const msg::Move _m = static_cast<const msg::Move&>(_msg);
		Vector3 v = _m._dir;
		if (slowedDown)
		{
			if (std::abs(v.x) >= 20) v.x = v.x / 2;
			if (std::abs(v.y) >= 20) v.y = v.y / 2;
			if (std::abs(v.z) >= 20) v.z = v.z / 2;
		}
		*_velocity += v;
		break;
	}
	case msg::JUMP: {
		const msg::Jump _m = static_cast<const msg::Jump&>(_msg);
		_pc->jump(_m._dir);
		//w_velocity += _m._dir;
		break;
	}
	case msg::COLISION: {
		const msg::Colision _m = static_cast<const msg::Colision&>(_msg);
		if (_m._type == "AnclaEffect")
		{
			slowedDown = _m._doIt;
			if (slowedDown)
			{
				if (std::abs(_velocity->x) >= 20) _velocity->x = _velocity->x / 2;
				if (std::abs(_velocity->y) >= 20) _velocity->y = _velocity->y / 2;
				if (std::abs(_velocity->z) >= 20) _velocity->z = _velocity->z / 2;
			}
			else
			{
				if (std::abs(_velocity->x) <= 10) _velocity->x = _velocity->x * 2;
				if (std::abs(_velocity->y) <= 10) _velocity->y = _velocity->y * 2;
				if (std::abs(_velocity->z) <= 10) _velocity->z = _velocity->z * 2;
			}
			if (slowedDown) {
				std::cout << "holi";
				_pc->jump(Vector3(0, 500, 0));
			}
		}
		//_pc->jump(_m._dir);
		//w_velocity += _m._dir;
		break;
	}
	default:
		break;
	}
}
