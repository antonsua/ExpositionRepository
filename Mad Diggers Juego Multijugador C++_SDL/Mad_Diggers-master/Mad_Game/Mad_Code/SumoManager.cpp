#include "SumoManager.h"
#include "Entity.h"


SumoManager::SumoManager(Game* game) : GameObject(game)
{
	minRect_ = { 322,220,153,158 };
	minArea_ = game_->getResources()->getImageTexture(Resources::i_minArea2P);
	//???? -> esta mierda? si no es entity no se puede mover junto con el mundo fisico btw
	//existe entity + imagerenderer, y tambien ocupa dos lineas loll
}

SumoManager::~SumoManager()
{
}

float SumoManager::dotProduct(Vector2D a, Vector2D b) const
{
	//Calculates dotProduct of a and b
	return a.getX() * b.getX() + a.getY() * b.getY();
}

double SumoManager::distance(double x1, double y1, double x2, double y2)
{
	//Return the distance between the two points
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
bool SumoManager::check_collision(Circle &A, Circle &B)
{
	//If the distance between the centers of the circles is less than the sum of their radii
	return (distance(A.x, A.y, B.x, B.y) < (A.r + B.r));

}
Vector2D SumoManager::velPerpen2Tangent(Entity* i, Entity* o)const
{
	//Calculates de vector perpendicular to the tangent of the collision vector
	Vector2D relativeVelocity = Vector2D(o->getVelocity().getX() - i->getVelocity().getX(),
		o->getVelocity().getY() - i->getVelocity().getY());

	float length = dotProduct(relativeVelocity, tangentVector);
	Vector2D velocityComponentTangent = tangentVector * length;

	return  relativeVelocity - velocityComponentTangent;
}

void SumoManager::setBounceVelocities(Entity* i, Entity* o) const
{
	//Set de velocities of the bounce to both the objects
	Vector2D velPerpendicular2Tangent = velPerpen2Tangent(i, o);

	o->setVelocity(Vector2D(o->getVelocity().getX() - velPerpendicular2Tangent.getX(),
		o->getVelocity().getY() - velPerpendicular2Tangent.getY()));

	i->setVelocity(Vector2D(i->getVelocity().getX() + velPerpendicular2Tangent.getX(),
		i->getVelocity().getY() + velPerpendicular2Tangent.getY()));
}

void SumoManager::impassableCircles(Entity* i, Entity* o)
{
	//Makes a repositioning of the circles in order to make them impassable
	double angle = std::atan2(i->getCircle().y - o->getCircle().y,
		i->getCircle().x - o->getCircle().x);

	float distanceBetweenCircles = distance(o->getCircle().x, o->getCircle().y,
		i->getCircle().x, i->getCircle().y);

	if (distanceBetweenCircles <= i->getCircle().r + o->getCircle().r)//AQUI ES SI SE HAN CHOCADO O NO SÑOR SEVILLLLAAAA
	{
		game_->sendToSM(&Message(SUMO_BOUNCE));
		float distanceToMove = o->getCircle().r + i->getCircle().r - distanceBetweenCircles;
		i->setPosition(Vector2D(i->getPosition().getX() + (std::cos(angle)*distanceToMove),
			i->getPosition().getY() + (std::cos(angle)*distanceToMove)));
	}
}

void SumoManager::checkOutFromArea(const int& i)
{
	if (!check_collision(collisionGroup_[0]->getCircle(), collisionGroup_[i]->getCircle()) && collisionGroup_[i]->isActive()) {

		collisionGroup_[i]->setActive(false);

		//mandar mensaje
		Message_OutFromArea m = Message_OutFromArea(i-1); //mensaje i-1 (teniendo en cuenta el fondo) del jugador que ha salido
		send(&m);
		if (checkLastActive())
		{
			Message_OutFromArea m1 = Message_OutFromArea(getLastIntActive()-1);
			send(&m1);
			Message m = MINIGAME_GAME_OVER;
			send(&m);
		}
	}

}

int SumoManager::getLastIntActive()
{
	int lastPLyer = 0;
	for (int i = 0; i < collisionGroup_.size(); i++)
		if (collisionGroup_[i]->isActive())lastPLyer = i;
	return lastPLyer;
}

bool SumoManager::checkLastActive()
{
	int contador = 0;
	for (auto it : collisionGroup_) {
		if (it->isActive()) contador++;
	}
	return contador < 3;
}


void SumoManager::bounceCalculation(Entity* i, Entity* o)
{
	//Main method of the circle's bounce, calculates the tangent and sets de velocity
	// of the bounce
	tangentVector.setY(-(i->getCircle().x - o->getCircle().x));
	tangentVector.setX(i->getCircle().y - o->getCircle().y);

	tangentVector.normalize();

	setBounceVelocities(i, o);

}
void SumoManager::update(Uint32 time)
{
	bool found = false;
	for (int i = 1; i < collisionGroup_.size(); i++)
	{
		for (int j = 1; j < collisionGroup_.size(); j++)
		{
			if (!found && collisionGroup_[i] != collisionGroup_[j]
				&& check_collision(collisionGroup_[i]->getCircle(), collisionGroup_[j]->getCircle()))
			{
				//Make the balls not passable through
				impassableCircles(collisionGroup_[i], collisionGroup_[j]);

				//Calculates de bounce of the balls
				bounceCalculation(collisionGroup_[i], collisionGroup_[j]);

				found = true;

			}
			checkOutFromArea(i);
		}
	}
}
void SumoManager::render(Uint32 time)
{
	minArea_->render(game_->getRenderer(), minRect_); //lel
}
void SumoManager::addCollisionObject(Entity* o)
{
	collisionGroup_.push_back(o);
}



