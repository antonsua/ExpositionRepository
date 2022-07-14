//Mad_Diggers

#include "Texture.h"

Texture::Texture() :
	texture_(nullptr), width_(0), height_(0), mColor_({ COLOR(0x000000ff) })
{
}

Texture::Texture(SDL_Renderer* renderer, string fileName, int cols, int fils) :
	texture_(nullptr), width_(0), height_(0), mColor_({ COLOR(0x000000ff) })
{
	loadFromSpriteSheet(renderer, fileName, cols, fils);
}

Texture::Texture(SDL_Renderer* renderer, string text, const Font& font,
	const SDL_Color color) :
	texture_(nullptr), width_(0), height_(0), mColor_({ COLOR(0x000000ff) })
{
	loadFromText(renderer, text, font, color);
}

Texture::~Texture() {
	close();
}

///////////////////////////////////////////////////////////////////

bool Texture::loadFromImg(SDL_Renderer* renderer, string fileName)
{
	return loadFromSpriteSheet(renderer, fileName, 1, 1);
}

bool Texture::loadFromSpriteSheet(SDL_Renderer* renderer,
	string fileName, int cols, int fils)
{
	cols_ = cols;
	fils_ = fils;

	SDL_Surface* surface = IMG_Load(fileName.c_str());
	if (surface != nullptr) {
		close(); // destroy current texture
		texture_ = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture_ != nullptr) {
			width_ = surface->w / cols;
			height_ = surface->h / fils;
		}
		SDL_FreeSurface(surface);
	}
	return texture_ != nullptr;
}

bool Texture::loadFromText(SDL_Renderer* renderer, string text,
	const Font& font, const SDL_Color color)
{
	SDL_Surface* textSurface = font.renderText(text, color);
	if (textSurface != nullptr) {
		close();
		texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture_ != nullptr) {
			width_ = textSurface->w;
			height_ = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return texture_ != nullptr;
}

void Texture::close() {
	if (texture_ != nullptr) {
		SDL_DestroyTexture(texture_); // delete current texture
		texture_ = nullptr;
		width_ = 0;
		height_ = 0;
	}
}

///////////////////////////////////////////////////////////////////

int Texture::getWidth() const {
	return width_;
}
int Texture::getHeight() const {
	return height_;
}

int Texture::getCols() const {
	return cols_;
}
int Texture::getFils() const {
	return fils_;
}

///////////////////////////////////////////////////////////////////

void Texture::render(SDL_Renderer* renderer, int x, int y) const {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = width_;
	dest.h = height_;
	render(renderer, dest);
}

void Texture::render(SDL_Renderer* renderer, const SDL_Rect& dest,
	SDL_Rect* clip) const {
	if (texture_) {
		SDL_Rect default_clip = { 0, 0, width_, height_ };
		if (clip == nullptr) {
			clip = &default_clip;
		}

		SDL_RenderCopy(renderer, texture_, clip, &dest);
	}
}

void Texture::render(SDL_Renderer* renderer, const SDL_Rect& dest, double angle,
	SDL_Rect* clip) const {
	if (texture_) {
		SDL_Rect default_clip = { 0, 0, width_, height_ };
		if (clip == nullptr) {
			clip = &default_clip;
		}

		//SDL rotates clockwise
		SDL_RenderCopyEx(renderer, texture_, clip, &dest, -angle, nullptr,
			SDL_FLIP_NONE);
	}
}

void Texture::render(SDL_Renderer * renderer, SDL_Rect const & dest, SDL_RendererFlip flip, SDL_Rect * clip)
{
	if (texture_) {
		SDL_Rect default_clip = { 0, 0, width_, height_ };
		if (clip == nullptr) {
			clip = &default_clip;
		}

		SDL_RenderCopyEx(renderer, texture_, clip, &dest, 0, NULL, flip);
		
	}
}



///////////////////////////////////////////////////////////////////

void Texture::renderFrame(int col, int fil, SDL_Renderer* renderer, int x, int y) const {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = width_;
	dest.h = height_;

	SDL_Rect clip;
	clip.x = width_ * col;
	clip.y = height_ * fil;
	clip.w = width_;
	clip.h = height_;

	render(renderer, dest, &clip);
}

void Texture::renderFrame(int col, int fil, SDL_Renderer* renderer, const SDL_Rect& dest, double angle) const {
	if (texture_) {
		SDL_Rect clip;
		clip.x = width_ * col;
		clip.y = height_ * fil;
		clip.w = width_;
		clip.h = height_;

		render(renderer, dest, angle, &clip);
	}
}

///////////////////////////////////////////////////////////////////

SDL_Rect Texture::getRectFrame(int frameCol, int frameFil)
{
	SDL_Rect rect;

	rect.w = getWidth();
	rect.h = getHeight();

	rect.x = rect.w * frameCol;
	rect.y = rect.h * frameFil;

	return rect;
}

void Texture::modulateAlpha(float alpha0to1)
{
	SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND); //activate mode for the texture
	SDL_SetTextureAlphaMod(texture_, alpha0to1 * 255);
}

void Texture::modulateColor(SDL_Color color)
{
	if (!areEqualColors (color, mColor_))
	{
		//reverts any modulations and then applys new one (and stores the color)
		SDL_SetTextureColorMod(texture_, -mColor_.r, -mColor_.g, -mColor_.b);
		SDL_SetTextureColorMod(texture_, color.r, color.g, color.b);
		mColor_ = color;
	}
}



bool Texture::areEqualColors(SDL_Color const& a, SDL_Color const& b) const
{
	return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}
