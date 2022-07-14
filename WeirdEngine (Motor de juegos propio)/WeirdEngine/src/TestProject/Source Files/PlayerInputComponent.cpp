#include "PlayerInputComponent.h"

#include <iostream>

#include <Vector3.h>
#include <Messages_decl.h>
#include <Messages_defs.h>

//#include <PhysicsComponent.h>
#include "Container.h"
#include "ComponentFactory.h"

CREATE_REGISTER(PlayerInput);

PlayerInputComponent::PlayerInputComponent(Container* e) : InputComponent(e) {
    _listener = new PlayerInputListener(e);
    _name = "Player" + _name;
    _parent->getWEManager()->addKeyListener(_listener, _name);
}

void PlayerInputComponent::Init(std::unordered_map<std::string, std::string>& param) {
    
}

PlayerInputListener* PlayerInputComponent::getKeyListener() {
    return _listener;
}

InputMouseListener* PlayerInputComponent::getMouseListener(){
    return nullptr;
}

//-----------------------LISTENER-------------------------
PlayerInputListener::PlayerInputListener(Container* ow) {
    _owner = ow;
}

PlayerInputListener::~PlayerInputListener() {}

bool PlayerInputListener::keyPressed(const OIS::KeyEvent& ke) {

    switch (ke.key) {
    case OIS::KC_W:
        std::cout << "Adelante\n";
        _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(0, 0, 20)));
        
        //Implementar en cada uno de estos el comportamiento con physics
        //static_cast<PhysicsComponent*>(_owner->getComponent("Physics"))->move(Vector3(0,0,10));
        break;
    case OIS::KC_S:
        std::cout << "Atras\n";
        _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(0, 0, -20)));
        //static_cast<PhysicsComponent*>(_owner->getComponent("Physics"))->move(Vector3(0, 0, -10));
        break;
    case OIS::KC_A:
        std::cout << "Izquierda\n";
        _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(20, 0, 0)));
        //static_cast<PhysicsComponent*>(_owner->getComponent("Physics"))->move(Vector3(10, 0, 0));
        break;
    case OIS::KC_D:
        std::cout << "Derecha\n";
        _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(-20, 0, 0)));
        //static_cast<PhysicsComponent*>(_owner->getComponent("Physics"))->move(Vector3(-10, 0, 0));
        break;
    case OIS::KC_SPACE:
        std::cout << "Barra Espaciadora\n";
        _owner->localSend(this, msg::Jump(msg::Player, msg::Broadcast, Vector3(0, 500, 0)));
        //static_cast<PhysicsComponent*>(_owner->getComponent("Physics"))->jump(Vector3(0, 500, 0));
        break;
    default:
        break;
    }

    return true;
}

bool PlayerInputListener::keyReleased(const OIS::KeyEvent& ke) {
    std::cout << "PlayerInput Relased\n";
    switch (ke.key) {
    case OIS::KC_W:
        std::cout << "Adelante back\n";
        _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(0, 0, -20)));

        //Implementar en cada uno de estos el comportamiento con physics
        //static_cast<PhysicsComponent*>(_owner->getComponent("Physics"))->move(Vector3(0,0,10));
        break;
    case OIS::KC_S:
        std::cout << "Atras\n";
        _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(0, 0, 20)));
        //static_cast<PhysicsComponent*>(_owner->getComponent("Physics"))->move(Vector3(0, 0, -10));
        break;
    case OIS::KC_A:
        std::cout << "Izquierda\n";
        _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(-20, 0, 0)));
        //static_cast<PhysicsComponent*>(_owner->getComponent("Physics"))->move(Vector3(10, 0, 0));
        break;
    case OIS::KC_D:
        std::cout << "Derecha\n";
        _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(20, 0, 0)));
        //static_cast<PhysicsComponent*>(_owner->getComponent("Physics"))->move(Vector3(-10, 0, 0));
        break;
    //case OIS::KC_SPACE:
    //    std::cout << "Barra Espaciadora\n";
    //    _owner->localSend(this, msg::Jump(msg::Player, msg::Broadcast, Vector3(0, 500, 0)));
    //    //static_cast<PhysicsComponent*>(_owner->getComponent("Physics"))->jump(Vector3(0, 500, 0));
     //   break;
    default:
        break;
    }
    return true;
}