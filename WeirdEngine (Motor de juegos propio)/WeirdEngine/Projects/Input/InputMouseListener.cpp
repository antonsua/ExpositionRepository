#include "InputMouseListener.h"

//#include <WEManager.h>
//#include <Messages_defs.h>
//#include <Messages_decl.h>

#include <iostream>

InputMouseListener::InputMouseListener(WEManager* ow) {
	_owner = ow;
}

bool InputMouseListener::mousePressed(const OIS::MouseEvent& ke) {
	switch (ke.state.buttonDown) {
	case OIS::MB_Left:
		std::cout << "Click Izquierdo\n";
		break;
	case OIS::MB_Right:
		std::cout << "Click derecho\n";
		break;
	case OIS::MB_Middle:
		std::cout << "Click Rueda\n";
		break;
		//_owner->send(this, msg::Close_Win(msg::WEManager, msg::Broadcast));
		//_owner->send(this, msg::Prueba(msg::WEManager, msg::Broadcast));
	default:
		break;
	}

	return true;
}

bool InputMouseListener::mouseReleased(const OIS::MouseEvent& ke){
	return false;
}

