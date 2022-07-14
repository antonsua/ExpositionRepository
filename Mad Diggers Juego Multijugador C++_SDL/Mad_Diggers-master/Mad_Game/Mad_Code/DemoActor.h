//Mad_diggers

#ifndef DEMOACTOR_H_
#define DEMOACTOR_H_

#include "Entity.h"

//Specific object using some components
//So in the states we just do new DemoActor

class DemoActor: public Entity
{
public:
	DemoActor(Game* game);
	DemoActor(Game* game, vector<EntityComponent*> components);
	virtual ~DemoActor();

	virtual void init();
	//H, U, R comes from Entity
};

#endif /* DEMOACTOR_H_ */
