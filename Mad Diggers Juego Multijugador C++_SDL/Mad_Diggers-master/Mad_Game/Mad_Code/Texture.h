//Mad_Diggers

#ifndef TEXTURE_H_
#define TEXTURE_H_

//#include "sdl_includes.h"
#include "Font.h" //brings sdl and string

using namespace std;

class Texture
{
public:
	Texture();
	//creates and loads new texture from file
	Texture(SDL_Renderer* renderer, string fileName, int cols = 1, int fils = 1);
	//creates and loads new texture gerenated from given font, color (default black) and text
	Texture(SDL_Renderer* renderer, string text, const Font& font, const SDL_Color color);

	virtual ~Texture();

	//loads new texture from file
	bool loadFromImg(SDL_Renderer* renderer, string fileName);

	//loads new spriteSheet from file (cols, fils)
	bool loadFromSpriteSheet(SDL_Renderer* renderer, string fileName, int cols, int fils);

	//loads new texture gerenated from given font, color (default black) and text
	bool loadFromText(SDL_Renderer * renderer, string texto,
		Font const& font, SDL_Color color = { 0, 0, 0, 255 });

	//closes the current texture
	void close();

	int getWidth() const;
	int getHeight() const;
	int getCols() const;
	int getFils() const;

	void render(SDL_Renderer* renderer, int x, int y) const;
	void render(SDL_Renderer* renderer, SDL_Rect const& dest,
		SDL_Rect* clip = nullptr) const;
	void render(SDL_Renderer* renderer, SDL_Rect const& dest,
		double angle, SDL_Rect* clip = nullptr) const;

	void render(SDL_Renderer* renderer, SDL_Rect const& dest,
		SDL_RendererFlip flip, SDL_Rect* clip = nullptr);

	void renderFrame(int col, int fil, SDL_Renderer* renderer, int x, int y) const;
	void renderFrame(int col, int fil, SDL_Renderer* renderer, SDL_Rect const& dest,
		double angle = 0) const;

	SDL_Rect getRectFrame(int frameCol, int frameFil);
	void modulateAlpha(float alpha0to1);
	void modulateColor(SDL_Color color);

private:
	//pointer to the texture
	SDL_Texture *texture_;

	int width_;
	int height_;

	int cols_;
	int fils_;

	bool areEqualColors(SDL_Color const& a, SDL_Color const& b) const;
	SDL_Color mColor_;

	

};

#endif /* TEXTURE_H_ */
