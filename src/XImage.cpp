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
	if (mAlignment == Left) {
		gl::draw(mTexture);
	}
	else if (mAlignment == Center) {
		float x_offset = 0.5*(mWidth - mTexture->getWidth());
		float y_offset = 0.5*(mHeight - mTexture->getHeight());
		gl::draw(mTexture, glm::vec2(x_offset, y_offset));
	}
	else {
		gl::draw(mTexture);
	}
    // and then any children will be draw after this
}

void XImage::loadXml( ci::XmlTree &xml )
{
	XRect::loadXml(xml);

	// get/set properties from xml
	if (xml.hasAttribute("texture")) {
		setTexture(xml.getAttributeValue<std::string>("texture"));
	}
	if (xml.hasAttribute("alignment")) {
		setAlignment(xml.getAttributeValue<std::string>("alignment"));
	}
}

void XImage::setTexture(const std::string &path) {
	mTexturePath = path;
	mTexture = gl::Texture::create(loadImage(app::loadAsset(path)));

	// if width and height have not been set, default to default texture's size
	if (mWidth == 0) {
		mWidth = (float)mTexture->getWidth();
	}
	if (mHeight == 0) {
		mHeight = (float)mTexture->getHeight();
	}
}

void XImage::setAlignment(const std::string &alignment) {
	if (alignment == "left") {
		mAlignment = Left;
	}
	else if (alignment == "center") {
		mAlignment = Center;
	}
	else {
		mAlignment = Left;
	}
}

std::string XImage::getAlignment() const {
	if (mAlignment == Left) {
		return "left";
	}
	else if (mAlignment == Center) {
		return "center";
	}
	else {
		return "left";
	}
}