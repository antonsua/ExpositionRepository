#pragma once

#include <string>
#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules\Ogre\Renderer.h>
#include <OIS.h>

class Vector4;

class GUI {
public:
	GUI();

	void Init();
	void InitResources();
	void destroy();

	// Cambia el estado de renderizado de todos los elementos de CEGUI
	void setVisible(bool rend);
	bool getVisible();

	// Carga de layouts, schemes y fuentes
	void loadLayout(const std::string& layoutName);
	void loadScheme(const std::string& schemeFile);
	void setFont(const std::string& fontFile);

	void setMouseCursor(const std::string& schemeFile);
	void createButton(const std::string& type, Vector4 Percents, Vector4 Pixels, const std::string& text, const std::string& name = "");
	void addEventToButton(const std::string& name, CEGUI::SubscriberSlot f);

	static bool pruebaEvent(const CEGUI::EventArgs& e);

	static void setWidgetDestRect(CEGUI::Window* widget, Vector4 Percents, Vector4 Pixels);

	CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
	void onOISMouseEvent(const OIS::MouseEvent& evnt);
	void onOISMousePressed(const OIS::MouseEvent& evnt, OIS::MouseButtonID id);
	void onOISMouseReleased(const OIS::MouseEvent& evnt, OIS::MouseButtonID id);
	void onOISKeyEvent(const OIS::KeyEvent& evnt);

	const CEGUI::OgreRenderer* getRenderer();
	const CEGUI::GUIContext* getContext();
private:
	CEGUI::OgreRenderer* ogre_renderer;
	CEGUI::GUIContext* m_context;
	CEGUI::Window* m_root;

	CEGUI::Window* createWidget(const std::string& type, Vector4 Percents, Vector4 Pixels, const std::string& name = "");
};