
#pragma once
#include "Emitter.h"
#include "GameObject.h"
#include "SumoPlayer.h"


struct Message_OutFromArea : Message {
	Message_OutFromArea(int player) :
		Message(SUMOGAME_OUT_FROM_AREA), player_(player) {
	}
	 int player_;
};

class SumoManager : public GameObject,public Emitter
{

public:
	SumoManager(Game* game);
	~SumoManager();

	virtual void handleEvents(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	void addCollisionObject(Entity* o); // lo añade al grupo de colisiones

	double distance(double x1, double y1, double x2, double y2);
	bool check_collision(Circle & A, Circle & B);
	float dotProduct(Vector2D a, Vector2D b) const;

	//BOUNCE CALCULATION METHODS
	void bounceCalculation(Entity* i, Entity* o);
	void setBounceVelocities(Entity* i, Entity* o) const;
	Vector2D velPerpen2Tangent(Entity* i, Entity* o)const;

	//IMPASSABLE AND AREA EXIT DETECTION
	void impassableCircles(Entity* i, Entity* o);
	void checkOutFromArea(const int& i);

	int getLastIntActive();

	bool checkLastActive();

private:
	Texture* minArea_;
	SDL_Rect minRect_;
	Vector2D tangentVector;
	std::vector<Entity*> collisionGroup_;

};

