#pragma once
#include "Entity.h"
#include "ShapeRenderer.h"
class Apple : public Entity
{
	const int APPLE_WIDHT = 45;
	const int APPLE_HEIGHT = 45;
public:
	Apple(Game* game,Resources::ColorId appleColor);
	~Apple();
	
	void update(Uint32 time);

	void setIdentifier(const int n);
	int getIdentifier() const { return colorIdentifier_; };

	ShapeRenderer* getRendererComp() { return &renderComp_; };
private:
	void updateCircle();

	int colorIdentifier_;

	ShapeRenderer renderComp_;
	

};

