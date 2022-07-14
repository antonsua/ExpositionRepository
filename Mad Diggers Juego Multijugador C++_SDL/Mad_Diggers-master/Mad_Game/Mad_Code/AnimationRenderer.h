#ifndef ANIMATIONRENDERER_H_
#define ANIMATIONRENDERER_H_

#include "EntityRenderComponent.h"
#include "Emitter.h"

#define MS_IN_SECOND 1000 //ms
struct spriteSheetData
{
	Vector2D scale_, offset_; //on top of object
	bool rotation_; //check direction and rotate render accordingly

	size_t
		//textureCols_, textureFils_,	//loaded in resources
		frameStartCol_, frameStartFil_, //if 0,0 -> auto set to min/max
		frameEndCol_, frameEndFil_;		//the first frame is 1,1 not 0,0

	Uint32 fps_; //frames / MS_IN_SECOND

	bool loop_, stay_, //render even when static (start == end, loop ended or not started, etc)
		drawRealPosition_ = false;
};

class AnimationRenderer : public EntityRenderComponent, public Emitter
{
public:
	AnimationRenderer(Texture* image, spriteSheetData* data, bool autoStart);
	virtual ~AnimationRenderer();

	void start();
	void cancel();
	void stop();

	void setImage(Texture* image);
	void setColor(SDL_Color* color);

	virtual void render(Entity* o, Uint32 time);

	void updateFrame(Uint32 time);

private:
	Texture* image_;
	SDL_Color *color_ = nullptr;

	spriteSheetData* data_;
	bool on_, autoStart_;
	size_t frameCol_, frameFil_;
	Uint32 lastframe_, frameTimer_;
};

#endif /* ANIMATIONRENDERER_H_ */
