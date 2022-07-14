#pragma once
#include "LinearMath/btAlignedObjectArray.h"
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btHashMap.h"
#include <Ogre.h>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <cstdlib>

class PhysicsEngine
{
public:
	struct bulletObject {
	public:
		btTransform startingTransform;
		int id;
		bool hit;
		btRigidBody* body;
		btVector3 size;
		bulletObject(btRigidBody* b, int i, bool hE) : body(b), id(i), haveEffect(hE), hit(false) {};
		bool haveEffect;
		void setHit(bool _hit)
		{
			hit = _hit;
		}
		bool getHit()
		{
			return hit;
		};
	};
	void initObjects();
	void reset();
	int basicMesh(Ogre::SceneNode* newNode, btVector3 collSize, bool gravity, std::string name);
	void addForce(int id, btVector3 fDirection);
	void changeVelocity(int id, btVector3 vDirection);
	void checkColliding(int id);
	void setPosition(int id, btVector3 newPosition);
	bool physicsLoop(float frameRate);

	bool isColliding(int id);
	btVector3 linearVelocity(int id);
	btVector3 position(int id);

private:
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	std::vector<btCollisionShape*> collisionShapes;
	std::map<std::string, btRigidBody*> physicsAccessors;
	std::list<bulletObject> bulletOBs;
};
