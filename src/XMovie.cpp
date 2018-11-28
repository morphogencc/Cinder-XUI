#include "cinder/app/App.h"
#include "cinder/ImageIO.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "XMovie.h"

using namespace ci;
using namespace xui;

XMovieRef XMovie::create()
{
    XMovieRef ref = XMovieRef( new XMovie() );
    return ref;
}

XMovieRef XMovie::create( ci::XmlTree &xml )
{
	XMovieRef ref = XMovie::create();
	ref->loadXml( xml );

	return ref;
}

void XMovie::draw(float opacity)
{
    gl::color( mColor * ColorA(1.0f, 1.0f, 1.0f, mOpacity * opacity) );
	mMovie->draw(0,0,mWidth,mHeight);
}

void XMovie::update( double elapsedSeconds ){
	if (mMovie) {
		mMovie->update();
	}
}

void XMovie::loadXml( ci::XmlTree &xml )
{
	XRect::loadXml(xml);

	// get/set properties from xml
	if ( xml.hasAttribute( "path" ) )
	{
		mMovie = std::shared_ptr<ciWMFVideoPlayer>(new ciWMFVideoPlayer());
		mMovie->loadMovie(app::getAssetPath(xml.getAttributeValue<std::string>("path")));
		mMovie->play();
	}

	mIsLooping = (xml.getAttributeValue("loop", 0) == 1 || xml.getAttributeValue<std::string>("loop", "") == "true");
	mIsFullscreen = (xml.getAttributeValue("fullscreen", 0) == 1 || xml.getAttributeValue<std::string>("fullscreen", "") == "true");

	setLoop(mIsLooping);
	setFullscreen(mIsFullscreen);
}

void XMovie::setFullscreen(bool fullscreen) {
	mIsFullscreen = fullscreen;
	if (mIsFullscreen) {
		setPos(ci::vec2(0,0));
		mWidth = ci::app::getWindowWidth();
		mHeight = ci::app::getWindowHeight();
	}
}