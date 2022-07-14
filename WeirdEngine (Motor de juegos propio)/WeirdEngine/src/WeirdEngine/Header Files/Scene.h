#pragma once

#include <list>
#include <stack>
#include <string>
#include <Container.h>

namespace msg {
	class Message;
}

class Scene : public Container {
public:
	Scene(std::string id, WEManager* wem);

	//Actualiza las entidades para que llamen a sus componentes
	virtual void update(float t);
	//Añade una entidad a la escena
	void addEntity(Container* e);

	std::string getID() { return _id; };
	Container* getEntity(std::string entName);

	//Receive
	virtual void receive(const void* senderObj, const msg::Message& msg);

	//virtual void send(const void* senderObj, const msg::Message& msg);
private:
	std::string _id;

	//Lista de entidades
	std::list<Container*> entidades;

	WEManager* _weM;

	//Se pueden añadir componentes especificos a las escenas, como uno de input
	//para controlar dependiendo de la escena que teclas queremos escuchar.
};