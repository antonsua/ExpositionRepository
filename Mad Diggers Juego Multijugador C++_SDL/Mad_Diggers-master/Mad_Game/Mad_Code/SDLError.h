//Mad_Diggers

#pragma once

#include <string>
#include <stdexcept>
#include <sstream>

using namespace std;

//we may write more classes

class SDLError : public logic_error
{
public:
	//reuses logic_error
	SDLError(const string& m) : logic_error("SDL error: " + m) {};
	virtual ~SDLError() {};
};

