#pragma once

#include <stack>
#include <string>
#include <json.hpp>

namespace msg {
	struct Message;
}

namespace CEGUI {
	class SubscriberSlot;
}

namespace Ogre {
	class Camera;
}

class Scene;
class Container;
class EntityC;

class WindowRenderer;
class RenderSystem;
class InputManager;
class InputKeyListener;
class InputMouseListener;
class PhysicsEngine;
class DataManager;
class AudioManager;

class Vector3;
class Vector4;
using json = nlohmann::json;

class WEManager {
	friend class EntityC;
public:
	//Constructoras
	WEManager();
	~WEManager();

	// Inicializa
	void Init();

	//Update
	bool update();

	//---------Escena--------
	// Crea la escena leyendo del archivo
	void generateScene(std::string sceneName, Vector4 VpColor);
	// Cambiar el estado de los componentes que lo requieran
	void switchComponentsState();
	// Añadir widgets a la escena activa
	void createButton(std::string type, std::string widgetName, std::string text, Vector4 Perc, Vector4 Pixels);
	void addEventToButton(std::string name, CEGUI::SubscriberSlot f);
	// Cargar una layout de cegui
	void loadLayout(std::string layoutName);
	//Activar/desactivar el renderizado de cegui
	void setGUIVisible(bool b);
	bool getGUIvis();

	//Luz
	void setLight(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

	// RenderSystem
	RenderSystem* getRenderSystem();
	void setSkyPlane(std::string name);

	//Metodos para la camara
	void addCameraToScene(Vector4 colors);
	void addCameraToEntity(std::string entityName, Vector4 colors);
	void addVpToCam(Vector4 colors); //Vector4->rgba
	void moveCam(Vector3 pos);
	void camLookAt(Vector3 pos);
	void rotateCam(Vector4 quat);
	Ogre::Camera* getCam();

	//Input
	void addKeyListener(InputKeyListener* iL, std::string name);
	void addMouseListener(InputMouseListener* iL, std::string name);
	void removeKeyListener(std::string name);
	void removeMouseListener(std::string name);

	// Sonido
	AudioManager* getAudioManager();
	/*
	void playSound(std::string name);
	void createSound(std::string name);
	void stopSound(std::string name);
	*/

	//----------Mensajes------
	void send(const void* senderObj, const msg::Message& msg);
	void receive(const void* senderObj, const msg::Message& msg);

	// Metodos para la pila
	void pushScene(Scene* newScene);
	void popScene();

	// Reset de la escena
	void restart();

	// Cerrado del juego
	static void close();
	// Fin de la app
	static bool end;

	//TimeDeltaTime
	float timeDeltaTime();
	float actualFrameRate();

private:
	//-----------SISTEMAS------------
	//Physics
	PhysicsEngine* py;
	//LectorDatos
	DataManager* dM;
	//Rendering
	WindowRenderer* windowRenderer;
	RenderSystem* renderSystem;
	//Audio
	AudioManager* audioManager;
	//Input Mng
	InputManager* mInputManager;
	//------------------------------------

	//Pila de escenas
	std::stack<Scene*> escenas;

	//TimeDeltaTime
	float timeDeltaTimeVar = 0.16;
	float startTime = 0;

	//Creacion de escena
	Container* CreateEntity(std::string& id, json prefabs, uint32_t n_entities, Vector3 position_);
	Vector3 setProperPosition(int row, int column, int layer, char xyz[3], float size_tiles, float size_layer);
	void generateEntities(Scene* scene, std::vector<std::vector<std::string>> map, json prefabs);
	void addComponentsToScene(Scene* scene, json prefabs);

	// Reset de la escena
	void reset();
	bool rst;

	//cegui en la escena
	void setCeguiLayout(std::string layoutName);
};