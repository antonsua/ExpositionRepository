//Mad_Diggers

#pragma once
#include "SDLError.h"

class FileNotFoundError : public SDLError
{

public:
	FileNotFoundError(const string& m) : SDLError("File " + m + " not found") {};
	virtual ~FileNotFoundError() {};
};