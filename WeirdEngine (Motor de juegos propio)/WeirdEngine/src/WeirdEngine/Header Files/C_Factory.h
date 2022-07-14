#pragma once

class Component;
class Container;

class CompFactory {
public:
	virtual Component* Create(Container* e) = 0;
};