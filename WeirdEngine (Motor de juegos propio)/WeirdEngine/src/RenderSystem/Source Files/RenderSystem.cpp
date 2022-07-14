#include "RenderSystem.h"
#include "WindowRenderer.h"

#include <Utilities/Vector3.h>
#include <Utilities/Vector4.h>

#include <iostream>

//Cegui
#include "GUI.h"
#include <OIS.h>

//Ogre
#include <Ogre.h>
#include <OgrePrerequisites.h>
#include <OgreResourceGroupManager.h>
#include <OgreMeshManager.h>
#include <OgreLogManager.h>
#include <OgreLog.h>
#include <OgreBuildSettings.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreCompositorManager.h>

RenderSystem* RenderSystem::instance_ = nullptr;

//Singleton
bool RenderSystem::initSingleton() {
	if (instance_ == nullptr) {
		instance_ = new RenderSystem();

		return true;
	}
	return false;
}

RenderSystem* RenderSystem::getSingleton() {
	return instance_;
}

// Render
void RenderSystem::draw(float t) {
	WindowRenderer::getSingleton()->handleEvents();
	WindowRenderer::getSingleton()->renderFrame(t);
}

// Constructora / Destructora
RenderSystem::RenderSystem() {
	WindowRenderer::initSingleton();

	guiManager = new GUI();
	guiManager->Init();
	guiManager->InitResources();
}

RenderSystem::~RenderSystem() {
	guiManager->destroy();
	delete guiManager;
}

//-------------------------------------------------
//Carga de materiales
void RenderSystem::materialGeneration(std::string nameOfResourceGroup) {
	Ogre::MaterialManager& materialManager = Ogre::MaterialManager::getSingleton();

	Ogre::ResourceGroupManager& mRgMgr = Ogre::ResourceGroupManager::getSingleton();
	mRgMgr.createResourceGroup(nameOfResourceGroup);

	// Textures directory path
	std::string textureDirectory = relativeResourcesPath+ "textures";
	mRgMgr.addResourceLocation(textureDirectory, "FileSystem", nameOfResourceGroup);

	// Initialise all resources
	mRgMgr.initialiseAllResourceGroups();

	// Load the desired resource group
	mRgMgr.loadResourceGroup(nameOfResourceGroup);
}

//---------------------------ESCENA---------------------------------
// Crear una escena
void RenderSystem::createScene(std::string sceneName) {
	Ogre::SceneManager* sMng = WindowRenderer::getSingleton()->getRoot()->createSceneManager();
	mScnMgr = sMng;

	currentScene = sceneName;

	scenes.erase(sceneName);
	scenes.insert({ sceneName, sMng });
}

// Indica cual es la escena a renderizar
void RenderSystem::setRenderingScene(std::string sceneName) {
	mScnMgr = scenes.find(sceneName)->second;

	camera = mScnMgr->getCamera(sceneName + "cam");

	currentScene = sceneName;
}

// Limpia las entidades de la escena activa actualmente
void RenderSystem::clearScene() {
	mScnMgr->destroyAllEntities();
}

Ogre::SceneNode* RenderSystem::createLight(std::string name, LightTypes type, Ogre::ColourValue diffuse, Ogre::ColourValue specular) {
	Ogre::Light* light = mScnMgr->createLight(name);
	light->setType(Ogre::Light::LightTypes(type));
	light->setDiffuseColour(diffuse);
	light->setSpecularColour(specular);

	Ogre::SceneNode* mLightNode = mScnMgr->getRootSceneNode()->createChildSceneNode(name);
	mLightNode->attachObject(light);

	return mLightNode;
}

// Luz ambiente a una escena
void RenderSystem::setAmbientLight(Ogre::ColourValue color) {
	mScnMgr->setAmbientLight(color);
}

void RenderSystem::setSkyBox(std::string matName, Ogre::Real distance) {
	mScnMgr->setSkyBox(true, matName, distance);
}

void RenderSystem::setSkyPlane(std::string matName, Ogre::Real scale, Ogre::Real tiling, Ogre::Real xseg, Ogre::Real yseg) {
	mScnMgr->setSkyPlane(true, Ogre::Plane(Ogre::Vector3::UNIT_Z, -50), matName, scale, tiling, true, 1.0, xseg, yseg);
}

std::string RenderSystem::getCurrentScene()
{
	return currentScene;
}
//----------------------------------------------




//------------------ENTIDADES-----------------
//Añadir una entidad a la escena que este renderizandose
Ogre::SceneNode* RenderSystem::addOgreEntity(std::string name, std::string mesh_name, std::string material) {
	Ogre::Entity* mEntity = mScnMgr->createEntity(name, mesh_name + ".mesh");
	Ogre::SceneNode* mNode = addEmpty(name);
	
	mEntity->setMaterialName(material);

	mNode->attachObject(mEntity);

	return mNode;
}

Ogre::SceneNode* RenderSystem::getSceneNode(std::string name) {
	return getEntityByName(name)->getParentSceneNode();
}

//Coger una entidad de la escena
Ogre::Entity* RenderSystem::getEntityByName(std::string name) {
	return mScnMgr->getEntity(name);
}

// Devuelve la pos de una entidad de la escena
const Ogre::Vector3 RenderSystem::getEntityPos(std::string name) {
	return mScnMgr->getEntity(name)->getParentSceneNode()->getPosition();
}

// Da la pos a una entidad de la escena
void RenderSystem::setEntityPos(std::string name, Ogre::Vector3 &p) {
	getEntityByName(name)->getParentNode()->setPosition(p);
}

//Dar material a una entidad de la escena
void RenderSystem::setMaterial(std::string entity, std::string matName) {
	getEntityByName(entity)->setMaterialName(matName);
}

//Dar un material a una entidad
void RenderSystem::setMaterial(Ogre::Entity* ent, std::string matName) {
	ent->setMaterialName(matName);
}

// Crear un nodo vacio
Ogre::SceneNode* RenderSystem::addEmpty(std::string name) {
	return mScnMgr->getRootSceneNode()->createChildSceneNode(name);
}

//------------------------------------------



//------------------------GUI----------------------------
//Carga una layout de los archivos de layouts
void RenderSystem::setLayout(std::string layoutName) {
	guiManager->loadLayout(layoutName);
}

// Activa o desactiva si se ven los elementos de cegui
void RenderSystem::setGUIVisible(bool b) {
	guiManager->setVisible(b);
}

bool RenderSystem::getGUIvis() {
	return guiManager->getVisible();
}

void RenderSystem::createButton(std::string type, std::string widgetName, std::string text, Vector4 Perc, Vector4 Pixels) {
	guiManager->createButton(type, Perc, Pixels, text, widgetName);
}

void RenderSystem::addEventToButton(const std::string& name, CEGUI::SubscriberSlot f) {
	guiManager->addEventToButton(name, f);
}

//------------------------OIS----------------------------
bool RenderSystem::mouseMoved(const OIS::MouseEvent& me) {
	guiManager->onOISMouseEvent(me);
	return true;
}

bool RenderSystem::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id) {
	guiManager->onOISMousePressed(me, id);
	return true;
}

bool RenderSystem::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id) {
	guiManager->onOISMouseReleased(me, id);
	return true;
}


//--------------------CAMARA--------------------------
//--Generales--
//Obtener la camara activa
Ogre::Camera* RenderSystem::getCamera() {
	return camera;
}

//Obtener el nodo de la camara activa
Ogre::SceneNode* RenderSystem::getCameraNode() {
	return camera->getParentSceneNode();
}

//Obtener el viewport de la camara activa
Ogre::Viewport* RenderSystem::getViewport() {
	return camera->getViewport();
}

//Mover la camara principal de la escena
void RenderSystem::moveCam(Ogre::Real x, Ogre::Real y, Ogre::Real z) {
	mScnMgr->getCamera(currentScene + "cam")->getParentSceneNode()->setPosition(x, y, z);
}

//Hacer que la camara principal mire a un lugar en especifico
void RenderSystem::camLookAt(Ogre::Vector3 v) {
	mScnMgr->getCamera(currentScene + "cam")->getParentSceneNode()->lookAt(v, Ogre::Node::TS_WORLD);
}

void RenderSystem::rotateCam(Ogre::Quaternion q) {
	mScnMgr->getCamera(currentScene + "cam")->rotate(q);
}


//--------Especificos--------
//Añadir una camara a una escena
void RenderSystem::addCamera() {
	std::string cName = currentScene + "cam";
	Ogre::Camera* mCamera = nullptr;
	mCamera = mScnMgr->createCamera(cName);

	Ogre::SceneNode* mCamNode = nullptr;
	mCamNode = mScnMgr->getRootSceneNode()->createChildSceneNode("n" + cName);
	mCamNode->attachObject(mCamera);

	mCamNode->setPosition(0, 0, 0);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	//If (far/near)>2000 then you will likely get 'z fighting' issues.
	mCamera->setNearClipDistance(21.0f);
	mCamera->setFarClipDistance(40000.0f);
}

void RenderSystem::addCameraToEnt(std::string entName) {
	std::string cName = currentScene + "cam";
	Ogre::Camera* mCamera = nullptr;
	mCamera = mScnMgr->createCamera(cName);

	Ogre::SceneNode* mCamNode = nullptr;
	//Ogre::SceneNode* mCamNode = getEntityByName(entName)->getParentSceneNode()->createChildSceneNode("n" + cName);

	// HUESOS COUT
	/*auto skeleton = getEntityByName(entName)->getSkeleton();
	auto bones = skeleton->getBones();
	for (auto i = 0; i < bones.size(); i++) {
		std::cout << bones[i]->getName() << "\n";
	}*/

	try {
		//mCamNode->setPosition(getEntityByName(entName)->getSkeleton()->getBone("Joint1")->getPosition());
		getEntityByName(entName)->getSkeleton()->getBone("Head")->addChild(mCamNode);
		mCamNode->attachObject(mCamera);
	}
	catch (const std::exception & e) {
		mCamNode = getEntityByName(entName)->getParentSceneNode()->createChildSceneNode("n" + cName);
		mCamNode->attachObject(mCamera);
		mCamNode->setPosition(mCamNode->getPosition().x, mCamNode->getPosition().y + 150, mCamNode->getPosition().z -20);
	}

	//If (far/near)>2000 then you will likely get 'z fighting' issues.
	mCamera->setNearClipDistance(3.0f);
	mCamera->setFarClipDistance(4000.0f);
}

//Añadir un vp a una camara con un color y un ZOrder
void RenderSystem::addVpToCam(Ogre::ColourValue c) {
	WindowRenderer::getSingleton()->getWin()->removeAllViewports();

	float viewportWidth = 1.0f;
	float viewportHeight = 1.0f;
	float viewportLeft = (1.0f - viewportWidth) * 0.5f;
	float viewportTop = (1.0f - viewportHeight) * 0.5f;
	unsigned short mainViewportZOrder = 100;

	Ogre::Camera* camera = mScnMgr->getCamera(currentScene + "cam");

	Ogre::Viewport* vp = WindowRenderer::getSingleton()->getWin()->addViewport(camera,
		mainViewportZOrder, viewportLeft, viewportTop, viewportWidth, viewportHeight);

	vp->setAutoUpdated(true);

	//Para CEGUI
	vp->setOverlaysEnabled(false);
	vp->setClearEveryFrame(true);

	// Color for the viewPort
	vp->setBackgroundColour(c);

	// I choose the visual ratio of the camera. To make it looks real, I want it the same as the viewport. 
	float ratio = Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight());
	camera->setAspectRatio(ratio);
}
//----------------------------------------------------


//----------------------------------------------------
inline Ogre::SceneNode* RenderSystem::getRootNode() {
	return mScnMgr->getRootSceneNode();
}

inline void RenderSystem::setSceneManager(Ogre::SceneManager* sm) {
	mScnMgr = sm;
}
//-------------------------------------------------