#ifndef MESSAGE_RC_H_
#define MESSAGE_RC_H_

#include "ImageRenderer.h"

class Message_RC : public ImageRenderer
{
public:
	Message_RC();
	Message_RC(Resources::FontId font, Resources::ColorId color, string msg);
	Message_RC(Resources::FontId font, Resources::ColorId color, string msg, spriteData* data);
	virtual ~Message_RC();

	virtual void render(Entity * o, Uint32 time);
	void updateMsg(Game * game);

	void setMsg(string msg);
	string getMsg() const;
	void setFont(Resources::FontId font);
	void setColor(Resources::ColorId color);

protected:
	virtual void fadeEnd() { ImageRenderer::fadeEnd(); if (alpha_ == 0) toggleActive(); };

private:
	Resources::FontId font_;
	Resources::ColorId color_;
	string msg_;

	bool updateMsg_ = false;
};

#endif /* MESSAGE_RC_H_ */