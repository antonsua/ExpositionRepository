#pragma once

#include <string>
#include <map>
#include <OIS.h>

namespace Ogre {
	class OverlayManager;
	class Camera;
	class OverlayContainer;
	class Overlay;
	class OverlayElement;
	class TextAreaOverlayElement;
	class SceneManager;
	class Viewport;
	class SceneNode;
	class Entity;
	class Light;
	class ColourValue;
	class AnimationState;

	template <int dims, typename T> class Vector;
	typedef float Real;
	typedef Vector<3, Real> Vector3;
	class Quaternion;
};

namespace CEGUI {
	class SubscriberSlot;
}

class GUI;

class Vector3;
class Vector4;

class RenderSystem : public OIS::MouseListener {
private:
	Ogre::SceneManager* mScnMgr = nullptr;
	Ogre::Camera* camera = nullptr;
	std::string currentScene;

	// Contains Scene names and the SceneManager attached to
	std::map<std::string, Ogre::SceneManager*> scenes;

	static RenderSystem* instance_;
	
	RenderSystem();
	~RenderSystem();

	//Cegui (UI)
	GUI* guiManager;
#if defined _DEBUG
	std::string relativeResourcesPath = "../../../resources/";
#else
	std::string relativeResourcesPath = "resources/";
#endif

public:
	static bool initSingleton();
	static RenderSystem* getSingleton();

	void draw(float t);

	//-------------Entidades-----------------
	// Adds an Ogre entity to the scene and returns the SceneNode containing it4
	Ogre::SceneNode* addOgreEntity(std::string name, std::string mesh_name, std::string material);
	
	// Adds an empty node to the scene
	Ogre::SceneNode* addEmpty(std::string name);

	Ogre::SceneNode* getSceneNode(std::string name);

	// Returns the entity attached to the scene with the given name
	Ogre::Entity* getEntityByName(std::string name);	

	const Ogre::Vector3 getEntityPos(std::string name);
	void setEntityPos(std::string name, Ogre::Vector3 &p);

	// Sets the material to entity
	void setMaterial(std::string entity, std::string matName);

	// Sets the material to entity with entity access
	void setMaterial(Ogre::Entity* ent, std::string matName);

	//-----------------------------
	// Gets the root SceneNode
	inline Ogre::SceneNode* getRootNode();

	// Change the SceneManager
	inline void setSceneManager(Ogre::SceneManager* sm);

	// Generates the different Resource Groups where take the materials
	void materialGeneration(std::string nameOfResourceGroup);

	//------------ESCENA------------
	// Creates a new scene and adds it to the scenes dictionary with the given key
	void createScene(std::string sceneName);

	//---Luces---
	enum LightTypes
	{
		/// Point light sources give off light equally in all directions, so require only position not direction
		LT_POINT = 0,
		/// Directional lights simulate parallel light beams from a distant source, hence have direction but no position
		LT_DIRECTIONAL = 1,
		/// Spotlights simulate a cone of light from a source so require position and direction, plus extra values for falloff
		LT_SPOTLIGHT = 2
	};


	// Creates a light and adds the lightNode to the scene
	Ogre::SceneNode* createLight(std::string name, LightTypes type, Ogre::ColourValue diffuse, Ogre::ColourValue specular);

	// Sets the ambient light of the rendering scene
	void setAmbientLight(Ogre::ColourValue color);

	//---Cielo---
	// Adds a skybox to the current scene
	void setSkyBox(std::string matName, Ogre::Real distance = 5000);

	// Adds a skyplane to the current scene
	void setSkyPlane(std::string matName, Ogre::Real scale = 1, Ogre::Real tiling = 1, Ogre::Real xseg = 100, Ogre::Real yseg = 100);

	// Sets the displayed scene to the scene given by parameter
	void setRenderingScene(std::string sceneName);

	// Destroy all render entities of the rendering scene
	void clearScene();

	// Gets the name of the displayed scene
	std::string getCurrentScene();


	//----------------CAMARA----------------
	// Sets up a camera in the actual rendering scene
	void addCamera();
	void addCameraToEnt(std::string entName);
	// Adds a viewport to a camera with the color especified
	void addVpToCam(Ogre::ColourValue c);

	// Moves the main cam of the rendering scene to the specified position
	void moveCam(Ogre::Real x, Ogre::Real y, Ogre::Real z);
	// Makes the camera look in a specific direction
	void camLookAt(Ogre::Vector3 v);
	// Rotates the camera
	void rotateCam(Ogre::Quaternion q);

	// Returns the camera to modify camera attributes 
	Ogre::Camera* getCamera();

	// Get the camera node to modify position, rotation, orientation ...
	Ogre::SceneNode* getCameraNode();

	// Get the viewport
	Ogre::Viewport* getViewport();

	// Get the current SceneManager of the scene
	Ogre::SceneManager* getCurrentSceneManager() { return mScnMgr; };


	//--------------------CEGUI----------------------
	void setLayout(std::string layoutName);
	void setGUIVisible(bool b);
	bool getGUIvis();
	void createButton(std::string type, std::string widgetName, std::string text, Vector4 Perc, Vector4 Pixels);
	void addEventToButton(const std::string& name, CEGUI::SubscriberSlot f);

	//---------------------OIS-------------------------
	// Raton
	virtual bool mouseMoved(const OIS::MouseEvent& me);
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);
};