#ifndef VALUE_RC_H_
#define VALUE_RC_H_

#include "message_RC.h"

class Value_RC : public Message_RC
{
public:
	Value_RC();
	Value_RC(int digits, Resources::FontId font, Resources::ColorId color);
	Value_RC(int digits, Resources::FontId font, Resources::ColorId color, spriteData* data);
	virtual ~Value_RC();

	virtual void render(Entity* o, Uint32 time);

private:
	string getTextFormated(int value); //adds digits
	int numOfDigits_, previousValue_;
};

#endif /* VALUE_RC_H_ */