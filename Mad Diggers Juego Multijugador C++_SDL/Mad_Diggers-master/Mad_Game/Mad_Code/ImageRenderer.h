#ifndef IMAGERENDERER_H_
#define IMAGERENDERER_H_

#include "EntityRenderComponent.h"
#include "Emitter.h"

class ImageRenderer: public EntityRenderComponent, public Emitter {

public:
	ImageRenderer();
	ImageRenderer(Texture* image);
	ImageRenderer(spriteData* data);
	ImageRenderer(Texture* image, spriteData* data);

	virtual ~ImageRenderer();

	void setImage(Texture* image);
	void setAlpha(float alpha0to1);

	void fadeToAlpha(float alpha0to1, Uint32 timeMS, MessageId fadeEndMsg = BOARD_ROLL_PointsFaded);
	void waveAlpha(float alpha0to1Min, float alpha0to1Max, Uint32 timeMS, MessageId fadeEndMsg = BOARD_ROLL_PointsFaded);
	void stopWaveAlpha(float alpha0to1Min);

	void stopFading();

	void activateFlip();	void setFlipOrientation(SDL_RendererFlip flip);

	virtual void render(Entity* o, Uint32 time);

protected:
	void fade(Uint32 time);

	//overrride if required (ex. send different msg)
	virtual void fadeEnd() { send(&Message(fadeEndMsg_)); };
	MessageId fadeEndMsg_;

	Texture* image_;		//pointer to the image to render
	spriteData* data_;

	Uint32 fadeTime_, wavingTime_;
	bool waving_ = false, fading_ = false, fadingOut_;
	float fadeSpeed_, alpha_ = 1, alphaTarget_;
	float waveAlphaMin_, waveAlphaMax_;

	bool flipOn_ = false;
	SDL_RendererFlip flip_ = SDL_FLIP_NONE;
};

#endif /* IMAGERENDERER_H_ */








