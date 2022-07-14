#include "GUI.h"
#include <iostream>

#include "Utilities\Vector4.h"

GUI::GUI() {
	ogre_renderer = nullptr;
	m_context = nullptr;
	m_root = nullptr;
}

void GUI::Init() {
	if (ogre_renderer == nullptr) {
		ogre_renderer = &CEGUI::OgreRenderer::bootstrapSystem();

		CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
		CEGUI::Scheme::setDefaultResourceGroup("Schemes");
		CEGUI::Font::setDefaultResourceGroup("Fonts");
		CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
		CEGUI::ScriptModule::setDefaultResourceGroup("Scripts");
	}

	m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	m_context = &CEGUI::System::getSingleton().createGUIContext(ogre_renderer->getDefaultRenderTarget());
	m_context = &CEGUI::System::getSingleton().getDefaultGUIContext();
}

void GUI::InitResources() {
	loadScheme("TaharezLook");
	loadScheme("AlfiskoSkin");
	loadScheme("Generic");
	loadScheme("HUDDemo");
	setFont("DejaVuSans-10");

	setMouseCursor("TaharezLook/MouseArrow");
}

void GUI::destroy() {
	CEGUI::System::getSingleton().destroyGUIContext(*m_context);
}

void GUI::setVisible(bool rend) {
	ogre_renderer->setRenderingEnabled(rend);
}

bool GUI::getVisible() {
	return ogre_renderer->isRenderingEnabled();
}

void GUI::loadLayout(const std::string& layoutName) {
	m_root = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(layoutName + ".layout", "Layouts");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_root);
}

void GUI::loadScheme(const std::string& schemeFile) {
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile+ ".scheme");
}

void GUI::setFont(const std::string& fontFile) {
	CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
	m_context->setDefaultFont(fontFile);
}

void GUI::setMouseCursor(const std::string& schemeFile) {
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(schemeFile);
}

//-----------------------------------BOTONES------------------------------------------
//Crear Boton
void GUI::createButton(const std::string& type, Vector4 Percents, Vector4 Pixels, const std::string& text, const std::string& name) {
	CEGUI::PushButton* pb = static_cast<CEGUI::PushButton*>(createWidget(type, Percents, Pixels, name));
	//addEventToButton(name, &GUI::pruebaEvent);
	pb->setText(text);
}

void GUI::addEventToButton(const std::string& name, CEGUI::SubscriberSlot f) {
	CEGUI::Window *w = m_root->getChild(name);
	w->subscribeEvent(CEGUI::PushButton::EventClicked, f);
}

bool GUI::pruebaEvent(const CEGUI::EventArgs&) {
	std::cout << "Repuesta!!!\n";
	return true;
}

//-----------------------------------GENERAL WIDGET------------------------------------------------
CEGUI::Window* GUI::createWidget(const std::string& type, Vector4 Percents, Vector4 Pixels, const std::string& name) {
	CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	m_root->addChild(newWindow);
	setWidgetDestRect(newWindow, Percents, Pixels);
	return newWindow;
}

void GUI::setWidgetDestRect(CEGUI::Window* widget, Vector4 Percents, Vector4 Pixels) {
	widget->setPosition(CEGUI::UVector2(CEGUI::UDim(Percents.x, Pixels.x), CEGUI::UDim(Percents.y, Pixels.y)));
	widget->setSize(CEGUI::USize(CEGUI::UDim(Percents.w, Pixels.w), CEGUI::UDim(Percents.z, Pixels.z)));
}

//-----------------------INPUT---------------------------------
CEGUI::MouseButton GUI::convertButton(OIS::MouseButtonID buttonID) {
	switch (buttonID) {
	case OIS::MB_Left:
		return CEGUI::MouseButton::LeftButton;
	case OIS::MB_Right:
		return CEGUI::MouseButton::RightButton;
	case OIS::MB_Middle:
		return CEGUI::MouseButton::MiddleButton;
	default:
		return CEGUI::MouseButton::NoButton;
	}
}

void GUI::onOISMouseEvent(const OIS::MouseEvent& evnt) {
	m_context->injectMouseMove(evnt.state.X.rel, evnt.state.Y.rel);
}

void GUI::onOISMousePressed(const OIS::MouseEvent& evnt, OIS::MouseButtonID id) {
	CEGUI::MouseButton key = convertButton(id);
	m_context->injectMouseButtonDown(key);
}

void GUI::onOISMouseReleased(const OIS::MouseEvent& evnt, OIS::MouseButtonID id) {
	CEGUI::MouseButton key = convertButton(id);
	m_context->injectMouseButtonUp(key);
}

void GUI::onOISKeyEvent(const OIS::KeyEvent& evnt) {

}

const CEGUI::OgreRenderer* GUI::getRenderer() {
	return ogre_renderer;
}

const CEGUI::GUIContext* GUI::getContext() {
	return m_context;
}
