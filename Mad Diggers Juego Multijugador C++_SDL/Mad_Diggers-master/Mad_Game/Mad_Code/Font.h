//Mad_Diggers

#ifndef FONT_H_
#define FONT_H_

#include "sdl_includes.h"
#include <string>

class Font {

public:

	Font();
	//creates and loads new font from file with given size
	Font(std::string fileName, int size);
	virtual ~Font();

	//loads new font from file with given size
	bool load(std::string fileName, int size);
	//closes the current font
	void close();

	//returns a surface with the rendered text using current font and color
	SDL_Surface* renderText(std::string text, SDL_Color color) const;

private:

	//pointer to the font
	TTF_Font *font_;
};

#endif /* FONT_H_ */
