#include "PhysicsEngine.h"
#include <iostream>

void PhysicsEngine::initObjects()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
}

void PhysicsEngine::reset()
{
	for (std::list<bulletObject>::const_iterator it = bulletOBs.begin(); it != bulletOBs.end(); ++it)
	{
		// reset ball
		(*it).body->clearForces();
		btVector3 zeroVector(0, 0, 0);
		(*it).body->setLinearVelocity(zeroVector);
		(*it).body->setAngularVelocity(zeroVector);
		(*it).body->setWorldTransform((*it).startingTransform);
	}
}


int PhysicsEngine::basicMesh(Ogre::SceneNode* newNode, btVector3 collSize, bool gravity, std::string name)
{
	//create the new shape, and tell the physics that is a Box
	//btCollisionShape* newRigidShape = new btBoxShape(collSize);
	btVector3 dim;
	Ogre::AxisAlignedBox df;
	//df = newNode->_getWorldAABB().;
	dim = btVector3(df.getSize().x, df.getSize().y, df.getSize().z);
	btCollisionShape* newRigidShape = new btBoxShape(collSize);
	collisionShapes.push_back(newRigidShape);
	//getCollisionShapes().push_back(newRigidShape);
	btRigidBody* body = nullptr;
	bulletObject newBO = bulletObject(body, 0, false);
	newBO.size = btVector3(collSize);
	//std::cout << "X:" << df.getSize().x << " Y:" << dim.getX() << " Z:" << dim.getX() << std::endl;
	//set the initial position and transform. For this demo, we set the tranform to be none
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(newNode->getOrientation().x, newNode->getOrientation().y, newNode->getOrientation().z, newNode->getOrientation().w));

	//set the mass of the object. a mass of "0" means that it is an immovable object
	btScalar mass;
	if (gravity) mass = 10.1f;
	else mass = 0.0f; //the mass is 0, because the ground is immovable (static)
	btVector3 localInertia(0, 0, 0);
	startTransform.setOrigin(btVector3(newNode->getPosition().x, newNode->getPosition().y, newNode->getPosition().z));
	newRigidShape->calculateLocalInertia(mass, localInertia);
	newBO.startingTransform = startTransform;
	//actually contruvc the body and add it to the dynamics world
	btDefaultMotionState* myMotionState;
	myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);
	newBO.body = new btRigidBody(rbInfo);
	newBO.body->setUserPointer(newNode);

	dynamicsWorld->addRigidBody(newBO.body);

	newBO.body->setCollisionFlags(newBO.body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	newBO.id = dynamicsWorld->getNumCollisionObjects() - 1;
	bulletOBs.push_back(newBO);
	return dynamicsWorld->getNumCollisionObjects() - 1;
}

void PhysicsEngine::addForce(int id, btVector3 fDirection)
{
	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[id];
	btRigidBody* body = btRigidBody::upcast(obj);
	std::cout << "X: " << fDirection.getX() << "Y: " << fDirection.getY() << "Z: " << fDirection.getZ() << "\n";
	if(fDirection.getY() > 0) body->applyCentralImpulse(fDirection);
	else body->applyCentralForce(fDirection);
}

void PhysicsEngine::changeVelocity(int id, btVector3 vDirection)
{
	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[id];
	btRigidBody* body = btRigidBody::upcast(obj);
	body->setLinearVelocity(btVector3(vDirection.x(), body->getLinearVelocity().y(), vDirection.z()));
	body->activate();
}

void PhysicsEngine::checkColliding(int id)
{
	bulletObject* btOb0 = new bulletObject(nullptr, 0, false);
	bool searching = true;
	bool colliding = false;
	std::list<bulletObject>::iterator it = bulletOBs.begin();
	while (searching && it != bulletOBs.end())
	{
		if ((*it).id == id)
		{
			searching = false;
			btOb0 = &(*it);
			float size_x = btOb0->size.getX() / 2/* * 25*/;
			//std::cout << "Tama->o X: " << size_x << std::endl;
			float size_y = btOb0->size.getY() * 25;
			//std::cout << "Tama->o Y: " << size_y << std::endl;
			float size_z = btOb0->size.getZ() / 2/* * 25*/;
			//std::cout << "Tama�o Z: " << size_z << std::endl;
			btTransform f;
			btVector3 s;
			btVector3 d;
			btOb0->body->getCollisionShape()->getAabb(f, s, d);
			int pruebas = 0;
			btTransform trans;
			//std::cout << "[NINJA] Colliding: ";
			bulletObject* collOb0 = new bulletObject(nullptr, 0, false);
			btOb0->setHit(false);
			btOb0->body->getMotionState()->getWorldTransform(trans);
			//std::cout << "[" << "NINJA" << "]" << "Pos Y: " << trans.getOrigin().getY() << std::endl;
			//std::cout << "[" << "NINJA" << "]" << "Pos Z: " << trans.getOrigin().getZ() << std::endl;
			for (std::list<bulletObject>::iterator coll = bulletOBs.begin(); coll != bulletOBs.end(); ++coll)
			{
				if ((*coll).id == btOb0->id) ++coll;
				collOb0 = &(*coll);
				collOb0->setHit(false);
				btTransform trans_coll;
				collOb0->body->getMotionState()->getWorldTransform(trans_coll);
				float distX = std::abs(trans.getOrigin().getX() - trans_coll.getOrigin().getX()) - collOb0->size.getX() / 2/* * 25*/;
				//std::cout << "[" << (*coll).id << "]" << "Dist X: " << distX << std::endl;
				//std::cout << "[" << (*coll).id << "]" << "Pos X: " << trans_coll.getOrigin().getX() << std::endl;
				//std::cout << "[" << (*coll).id << "]" << "Size X (/2): " << (*coll).size.getX() / 2 << std::endl;
				if (distX <= (size_x + 1))
				{
					float distY = std::abs((trans.getOrigin().getY() + (((size_y/1.0f) - (btOb0->size.getY())) - 2)) - trans_coll.getOrigin().getY()) - collOb0->size.getY()/* * 25*/;
					/*std::cout << "[" << (*coll).id << "]" << "Dist Y: " << distY << std::endl;*/
					//std::cout << "[" << (*coll).id << "]" << "Pos Y: " << trans_coll.getOrigin().getY() << std::endl;
					//std::cout << "[" << (*coll).id << "]" << "Size Y (/2): " << (*coll).size.getY() / 2 << std::endl;
					if (distY <= (size_y + 1))
					{
						float distZ = std::abs(trans.getOrigin().getZ() - trans_coll.getOrigin().getZ()) - collOb0->size.getZ() / 2/* * 25*/;
						//std::cout << "[" << (*coll).id << "]" << "Dist Z: " << distZ << std::endl;
						//std::cout << "[" << (*coll).id << "]" << "Pos Z: " << trans_coll.getOrigin().getZ() << std::endl;
						//std::cout << "[" << (*coll).id << "]" << "Size Z (/2): " << (*coll).size.getZ() / 2 << std::endl;
						if (distZ <= (size_z + 1))
						{
							collOb0->setHit(true);
							btOb0->setHit(true);
						}
					}
				}
			}
		}
		++it;
	}
	//std::cout << "\n";
}

void PhysicsEngine::setPosition(int id, btVector3 newPosition)
{
	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[id];
	btTransform trans;
	btRigidBody* body = btRigidBody::upcast(obj);
	trans.getOrigin().setValue(newPosition.getX(), newPosition.getY(), newPosition.getZ());
	body->getMotionState()->setWorldTransform(trans);
}
bool PhysicsEngine::isColliding(int id)
{
	bulletObject btOb0 = bulletObject(nullptr, 0, false);
	bool searching = true;
	bool colliding = false;
	std::list<bulletObject>::iterator it = bulletOBs.begin();
	while (searching && it != bulletOBs.end())
	{
		if ((*it).id == id)
		{
			searching = false;
			btOb0 = (*it);
		}
		++it;
	}

	return btOb0.getHit();
}

btVector3 PhysicsEngine::linearVelocity(int id)
{
	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[id];
	btRigidBody* body = btRigidBody::upcast(obj);
	return body->getLinearVelocity();
}

btVector3 PhysicsEngine::position(int id)
{
	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[id];
	btRigidBody* body = btRigidBody::upcast(obj);
	btTransform trans;
	body->getMotionState()->getWorldTransform(trans);
	return trans.getOrigin();
}


bool PhysicsEngine::physicsLoop(float frameRate)
{
	dynamicsWorld->stepSimulation(frameRate * 0.005, 0);

	for (int i = 0; i < collisionShapes.size(); i++) {
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);

		if (body && body->getMotionState()) {
			btTransform trans;
			body->getMotionState()->getWorldTransform(trans);
			void* userPointer = body->getUserPointer();
			if (userPointer) {
				btQuaternion orientation = trans.getRotation();
				Ogre::SceneNode* sceneNode = static_cast<Ogre::SceneNode*>(userPointer);
				sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
			}
		}
	}
	return true;
}