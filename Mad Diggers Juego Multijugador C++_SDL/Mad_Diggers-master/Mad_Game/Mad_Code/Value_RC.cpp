#include "Value_RC.h"

Value_RC::Value_RC()
{
}

Value_RC::Value_RC(int digits, Resources::FontId font, Resources::ColorId color) :
	Message_RC(font, color, "sample"), numOfDigits_(digits), previousValue_(-1)
{
}

Value_RC::Value_RC(int digits, Resources::FontId font, Resources::ColorId color, spriteData* data) :
	Message_RC(font, color, "sample", data), numOfDigits_(digits), previousValue_(-1)
{
}

Value_RC::~Value_RC()
{
}

///////////////////////////////////////////////////////////////////

void Value_RC::render(Entity* o, Uint32 time)
{
	//update value before render
	int value = o->getSomeValue();

	if (value != previousValue_)
	{
		previousValue_ = value;
		setMsg(getTextFormated(value));
	}

	Message_RC::render(o, time);
}

string Value_RC::getTextFormated(int value)
{
	for (size_t i = 1; i <= numOfDigits_; i++)
	{
		if (value < pow(10, i)) {
			string extraZeros = "";
			for (size_t j = 0; j < numOfDigits_ - i; j++) extraZeros += "0";
			return extraZeros + to_string(value);
		}
	}
	return to_string(value);
}