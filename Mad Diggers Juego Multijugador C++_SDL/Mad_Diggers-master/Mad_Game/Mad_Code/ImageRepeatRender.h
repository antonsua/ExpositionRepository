#pragma once
#include "ImageRenderer.h"

class ImageRepeatRender :
	public ImageRenderer
{
public:
	ImageRepeatRender(Texture* image, double width, double height);
	ImageRepeatRender();
	virtual ~ImageRepeatRender();
	virtual void render(Entity* o, Uint32 time);

protected:	
	double width_;		//horizontal scale
	double height_;	//vertical scale
};

