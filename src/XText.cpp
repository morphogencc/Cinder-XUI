#include <boost/algorithm/string.hpp>
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "XText.h"

using namespace ci;
using namespace xui;

XTextRef XText::create()
{
    XTextRef ref = XTextRef( new XText() );
    return ref;
}

XTextRef XText::create( ci::XmlTree &xml )
{
	XTextRef ref = XText::create();
	ref->loadXml( xml );
	return ref;
}

void XText::draw(float opacity)
{
    // Matrix is already applied so we can draw at origin
    gl::color( mColor * ColorA(1.0f, 1.0f, 1.0f, mOpacity * opacity) );

	if (mTextBox.getText() != "" && mTextTexture)
		gl::draw(mTextTexture);

    // and then any children will be draw after this
}

void XText::loadXml( ci::XmlTree &xml )
{
	XRect::loadXml(xml);

	// get/set properties from xml
	std::string font = xml.getAttributeValue<std::string>( "font", "" );
	if (font == "")
		mTextBox.setFont( Font( "Arial", (float)xml.getAttributeValue( "size", 12 ) ) );
	else
		mTextBox.setFont( Font( app::loadAsset( font ), (float)xml.getAttributeValue( "size", 12 ) ) );
	setText( xml.getAttributeValue<std::string>( "text", "" ) );
	setTextAlignment( xml.getAttributeValue<std::string>( "alignment", "left" ) );

	update();
}

void XText::setProperty( const XNodeStateProperty& prop )
{
	if (prop.mType == "text")
		setText( prop.mValue.c_str() );
	else if (prop.mType == "textcolor")
		mTextBox.setColor( hexToColor(prop.mValue.c_str()) );
	else if (prop.mType == "alignment")
		setTextAlignment( prop.mValue.c_str() );
	else
		XRect::setProperty( prop );

	update();
}

void XText::setTextAlignment(std::string alignmentName)
{
	TextBox::Alignment alignment = TextBox::Alignment::LEFT;

	if (boost::iequals(alignmentName, "left"))
		alignment = TextBox::Alignment::LEFT;
	if (boost::iequals(alignmentName, "center"))
		alignment = TextBox::Alignment::CENTER;
	if (boost::iequals(alignmentName, "right"))
		alignment = TextBox::Alignment::RIGHT;

	mTextBox.setAlignment(alignment);
	update();
}

void XText::update()
{
	// render our text surface
	if (mWidth && mHeight) {
		// if a width and height were manually set, then set the textbox to whatever size we set
		mTextBox.setSize(vec2(mWidth, mHeight));
	}
	else {
		// otherwise, measure the text box and give us a new default size
		mWidth = mTextBox.measure().x + 1;
		mHeight = mTextBox.measure().y + 1;
	}
	mTextTexture = gl::Texture::create( mTextBox.render() );
}