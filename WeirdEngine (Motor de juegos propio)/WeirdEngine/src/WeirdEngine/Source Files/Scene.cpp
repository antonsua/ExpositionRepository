#include "Scene.h"
#include <Messages_defs.h>
#include <Messages_decl.h>

#include <Container.h>

Scene::Scene(std::string id, WEManager* wem) : Container (id, wem) {
	_weM = wem;
	_id = id;
}

void Scene::update(float t) {
	for (auto i = entidades.begin(); i != entidades.end(); ++i) {
		static_cast<Container*>(*i)->update(t);
	}
}

void Scene::addEntity(Container * e) {
	entidades.push_back(e);
}

Container* Scene::getEntity(std::string entName) {
	for (Container* e : entidades) {
		if (e->GetEntityName() == entName) {
			return e;
		}
	}
	return nullptr;
}

void Scene::receive(const void* senderObj, const msg::Message& msg) {
	Container::receive(senderObj, msg);

	for (Container* e : entidades) {
		if (senderObj != e) {
			if (msg.destination_ == msg::Broadcast || msg.destination_ == e->getId())
				e->receive(senderObj, msg);
		}
	}
}