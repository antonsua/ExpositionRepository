#include "Entity.h"

#include "EntityComponent.h"
#include "SkeletonRenderer.h"

//inited by game
SkeletonRenderer Entity::debug_RC = NULL; //inited by initDebug
void Entity::initDebug()
{
	SkeletonRenderer::init();
	debug_RC = SkeletonRenderer();
}

///////////////////////////////////////////////////////////////////////////////

Entity::Entity(Game* game) : Entity(game, vector<EntityComponent*>()) {}

Entity::Entity(Game* game, vector<EntityComponent*> components) :
	GameObject(game), Transformable(), components_(components), debugBody_(false)
{
}

Entity::~Entity()
{
	
}

///////////////////////////////////////////////////////////////////////////////

void Entity::handleEvents(Uint32 time, const SDL_Event& event) {
	for (auto c : components_) {
		if (c->isActive()) c->handleEvents(this, time, event);
	}
}

void Entity::update(Uint32 time) {
	for (auto c : components_) {
		if (c->isActive()) c->update(this, time);
	}
	if (isActive()) Transformable::update(time);
}

void Entity::render(Uint32 time) {
	for (auto c : components_) {
		if (c->isActive()) c->render(this, time);
	}
	if (debugBody_ || debug_RC.isActive()) debug_RC.render(this, time); //afterwards always
}

///////////////////////////////////////////////////////////////////////////////

void Entity::addComponent(EntityComponent * c)
{
	components_.push_back(c);
}

void Entity::delComponent(EntityComponent * c)
{
	std::vector<EntityComponent*>::iterator position = std::find(
		components_.begin(), components_.end(), c);

	if (position != components_.end()) //if found
		components_.erase(position);
}

void Entity::switchComponents(EntityComponent * cRemoved, EntityComponent * cAdded)
{
	std::vector<EntityComponent*>::iterator it = std::find(
		components_.begin(), components_.end(), cRemoved);

	//if not found
	if (it == components_.end()) addComponent(cAdded);
	else *it = cAdded;
}

void Entity::delAllComponents()
{
	components_.clear();
}

///////////////////////////////////////////////////////////////////////////////

void Entity::toggleDebugSingle()
{
	debugBody_ = !debugBody_;
}

void Entity::toggleDebugGlobal()
{
	debug_RC.toggleActive();
}