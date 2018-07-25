#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "XUI.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace xui;

class XUITestApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

	void onSceneLoadTryEvent(XUI::SceneLoadEventResponse response);
	void onSceneLoadSuccessEvent(XUI::SceneLoadEventResponse response);
	void onSceneLoadFailureEvent(XUI::SceneLoadFailureEventResponse response);
	void consoleOut(std::string msg);

	// XUI
	XUIRef mXUI;
};

void XUITestApp::setup() {
	// create XUI and hook up scene load events
	mXUI = XUI::create();
	mXUI->registerSceneLoadTryEvent(this, &XUITestApp::onSceneLoadTryEvent);
	mXUI->registerSceneLoadSuccessEvent(this, &XUITestApp::onSceneLoadSuccessEvent);
	mXUI->registerSceneLoadFailureEvent(this, &XUITestApp::onSceneLoadFailureEvent);
	mXUI->registerConsoleOut(this, &XUITestApp::consoleOut);

	// ui setup
	mXUI->loadScene("ui.xml");
}

void XUITestApp::mouseDown( MouseEvent event )
{
}

void XUITestApp::update()
{
}

void XUITestApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

void XUITestApp::consoleOut(std::string msg)
{
	app::console() << msg << std::endl;
}

void XUITestApp::onSceneLoadTryEvent(XUI::SceneLoadEventResponse response)
{
	app::console() << "Loading XUI Scene..." << std::endl;
}

void XUITestApp::onSceneLoadSuccessEvent(XUI::SceneLoadEventResponse response)
{
	app::console() << "XUI Load Success" << std::endl;
}

void XUITestApp::onSceneLoadFailureEvent(XUI::SceneLoadFailureEventResponse response)
{
	// output error and send it to code editor
	app::console() << response.mError << std::endl;
}

CINDER_APP( XUITestApp, RendererGl, [&](App::Settings *settings) {
	settings->setFullScreen(false);
	settings->setMultiTouchEnabled(true);
})
