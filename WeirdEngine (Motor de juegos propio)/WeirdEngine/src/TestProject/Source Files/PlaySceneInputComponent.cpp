#include "PlaySceneInputComponent.h"

#include <iostream>

#include <Container.h>
#include <Messages_defs.h>
#include <ComponentFactory.h>

CREATE_REGISTER(PlaySceneInput);

PlaySceneInputComponent::PlaySceneInputComponent(Container* e) : InputComponent(e){
    _listener = new WEInputListener(e);
    _name = "PlayScene" + _name;
    _parent->getWEManager()->addKeyListener(_listener, _name);
}

void PlaySceneInputComponent::Init(std::unordered_map<std::string, std::string>& param) {
    PauseMenu = OIS::KC_ESCAPE;
}

// Cuando reacciona al teclado
WEInputListener* PlaySceneInputComponent::getKeyListener() {
    return _listener;
}

// Cuando reacciona al raton
InputMouseListener* PlaySceneInputComponent::getMouseListener() {
    return nullptr;
}

////-----------------------LISTENER-------------------------
WEInputListener::WEInputListener(Container* ow) {
    _owner = ow;
}

WEInputListener::~WEInputListener() {}

bool WEInputListener::keyPressed(const OIS::KeyEvent& ke) {
    switch (ke.key) {
    case OIS::KC_ESCAPE:
        _owner->globalSend(this, msg::Close_Win(msg::WEManager, msg::Broadcast));
        break;
    case OIS::KC_SPACE:
        std::cout << "Funciona\n";
        //_owner->localSend(this, msg::Prueba(msg::Player, msg::Broadcast));
        //_owner->send(this, msg::Prueba(msg::WEManager, msg::Broadcast));
        break;
    default:
        break;
    }

    return true;
}

bool WEInputListener::keyReleased(const OIS::KeyEvent& ke) {
    return true;
}