#pragma once
#include <OISMouse.h>
class WEManager;

class InputMouseListener :public OIS::MouseListener{
public:
	InputMouseListener(WEManager* ow);
	~InputMouseListener() {};

private:
	virtual bool mousePressed(const OIS::MouseEvent& ke);
	virtual bool mouseReleased(const OIS::MouseEvent& ke);

	WEManager* _owner;
};

