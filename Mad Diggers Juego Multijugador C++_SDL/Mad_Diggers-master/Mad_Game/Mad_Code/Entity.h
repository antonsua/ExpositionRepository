#ifndef ENTITY_H_
#define ENTITY_H_

#include "Transformable.h"
#include "GameObject.h"


class EntityComponent;
class SkeletonRenderer; //for debug

class Entity: public GameObject, public Transformable
{
public:
	Entity(Game* game);
	Entity() {};
	Entity(Game* game, vector<EntityComponent*> components);
	virtual ~Entity();

	virtual void handleEvents(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	virtual void addComponent(EntityComponent* c);
	virtual void delComponent(EntityComponent* c);
	virtual void switchComponents(EntityComponent* cRemoved, EntityComponent* cAdded);
	virtual void delAllComponents();

	void toggleDebugSingle();
	static void toggleDebugGlobal();
	static void initDebug();

	virtual int getSomeValue() { return -1; }

protected:
	virtual void endMovement(bool timeOut) {};
	virtual void endResizing() {};

private:
	vector<EntityComponent*> components_;

	static SkeletonRenderer debug_RC; //global component
	bool debugBody_; //single entity
};
#endif /* ENTITY_H_ */
