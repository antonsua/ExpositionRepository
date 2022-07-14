#pragma once

#include "EntityC.h"
#include <vector>

class Component;
class InputComponent;

/*
 *
 */
class Container : public EntityC {
	friend class EntityC;
public:
	//Container();
	Container(std::string id, WEManager* wem);
	virtual ~Container();

	virtual void update(float time);

	// Añadir un componente
	void AddComponent(Component* c);
	void AddComponent(InputComponent* c);
	// Quitar un componente
	void DelComponent(Component* c);
	void DelComponent(InputComponent* c);
	// Des/activar un componente
	void activeComponent(std::string s);
	// Comprobar si tiene un componente
	bool hasComponent(std::string s);
	// Obtener un componente
	Component* getComponent(std::string s);
	InputComponent* getInputComponent(std::string s);

	void reset(); // removes all components

	virtual void receive(const void* senderObj, const msg::Message& msg);

	// used by components to send message at the level of container
	void localSend(const void* senderObj, const msg::Message& msg);

	// this will be used by components to send message globally
	void globalSend(const void* senderObj, const msg::Message& msg);
private:
	void broadcastToLocalComponents(const void* senderObj, const msg::Message& msg);

	template<typename T>
	struct wrapper {
		bool active;
		T* data;

		bool operator==(const wrapper<T>& other) const {
			return other.data == data;
		}
	};

	template<typename T>
	void AddC(std::vector<wrapper<T>>& v, T* c);

	template<typename T>
	bool hasC(std::vector<wrapper<T>>& v, T* c);

	template<typename T>
	void removeC(std::vector<wrapper<T>>& v, T* c);

	std::vector<wrapper<Component>> _components;
	std::vector<wrapper<InputComponent>> _InputComponents;
};

template<typename T>
inline void Container::AddC(std::vector<wrapper<T>>& v, T* c) {

	if (c == nullptr)
		return;

	wrapper<T> r = { true, c };

	auto position = std::find(v.begin(), v.end(), r);

	if (position != v.end()) {
		(*position).active = true;
	}
	else {
		v.push_back(r);
	}
}

template<typename T>
inline bool Container::hasC(std::vector<wrapper<T>>& v, T* c) {
	wrapper<T> r = { true, c };
	auto position = std::find(v.begin(), v.end(), r);

	return position != v.end();
}

template<typename T>
inline void Container::removeC(std::vector<wrapper<T>>& v, T* c) {
	if (c == nullptr)
		return;

	wrapper<T> r = { true, c };
	auto position = std::find(v.begin(), v.end(), r);

	if (position != v.end()) {
		(*position).active = false;
	}
}
