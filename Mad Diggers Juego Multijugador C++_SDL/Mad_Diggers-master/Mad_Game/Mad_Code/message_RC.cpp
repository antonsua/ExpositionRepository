#include "Message_RC.h"

Message_RC::Message_RC()
{
}

Message_RC::Message_RC(Resources::FontId font, Resources::ColorId color, string msg) :
	font_(font), color_(color)
{
	setMsg(msg);
}

Message_RC::Message_RC(Resources::FontId font, Resources::ColorId color, string msg, spriteData* data) :
	ImageRenderer(data), font_(font), color_(color)
{
	SDL_assert(data_->scale_.getX() > 0.09 && data_->scale_.getY() > 0.09); //negative scale
	setMsg(msg);
}


Message_RC::~Message_RC()
{
	if (image_ != nullptr) image_->close();
	delete image_;
}

///////////////////////////////////////////////////////////////////

void Message_RC::render(Entity* o, Uint32 time)
{
	if (updateMsg_) updateMsg(o->getGame());
	ImageRenderer::render(o, time);
}

void Message_RC::updateMsg(Game* game)
{
	updateMsg_ = false;

	if (image_ != nullptr) image_->close();

	image_ = new Texture(game->getRenderer(), msg_,
		*game->getResources()->getFont(font_),
		*game->getResources()->getSDLColor(color_));
}

void Message_RC::setMsg(string msg)
{
	updateMsg_ = true;
	msg_ = msg;
}

string Message_RC::getMsg() const
{
	return msg_;
}

void Message_RC::setFont(Resources::FontId font)
{
	updateMsg_ = true;
	font_ = font;
}

void Message_RC::setColor(Resources::ColorId color)
{
	updateMsg_ = true;
	color_ = color;
}
