#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIO.h"
#include "XImage.h"

using namespace ci;
using namespace xui;

XImageRef XImage::create()
{
    XImageRef ref = XImageRef( new XImage() );
    return ref;
}

XImageRef XImage::create( ci::XmlTree &xml )
{
	XImageRef ref = XImage::create();
	ref->loadXml( xml );
	return ref;
}

void XImage::draw(float opacity)
{
    // Matrix is already applied so we can draw at origin
    gl::color( mColor * ColorA(1.0f, 1.0f, 1.0f, mOpacity * opacity) );
	gl::draw( mTexture );
    
    // and then any children will be draw after this
}

void XImage::loadXml( ci::XmlTree &xml )
{
	XRect::loadXml(xml);

	// get/set properties from xml
	if (xml.hasAttribute("texture")) {
		setTexture(xml.getAttributeValue<std::string>("texture"));
	}
}

void XImage::setTexture(const std::string &path) {
	mTexturePath = path;
	mTexture = gl::Texture::create(loadImage(app::loadAsset(path)));

	// if width and height have not been set, default to default texture's size
	mWidth = (float)mTexture->getWidth();
	mHeight = (float)mTexture->getHeight();

}