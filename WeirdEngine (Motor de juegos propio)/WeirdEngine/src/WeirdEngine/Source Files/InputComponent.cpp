#include "InputComponent.h"
#include "Messages_decl.h"

InputComponent::InputComponent(Container* e) {
	_name = "Input";
	_parent = e;
}

Container* InputComponent::getParent() const {
	return _parent;
}