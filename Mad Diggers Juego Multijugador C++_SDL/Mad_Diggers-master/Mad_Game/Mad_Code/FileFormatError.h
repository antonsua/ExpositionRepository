//Mad_Diggers

#pragma once
#include "SDLError.h"

class FileFormatError : public SDLError
{
public:
	FileFormatError(const string& m) : SDLError("Incorrect format at loaded file: " + m) {};
	//~FileFormatError();
};

