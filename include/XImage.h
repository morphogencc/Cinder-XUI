#pragma once
#include "XRect.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/gl/Texture.h"

namespace xui {

typedef std::shared_ptr<class XImage> XImageRef;

class XImage : public XRect
{
public:
    static XImageRef create();
    static XImageRef create( ci::XmlTree &xml );

	virtual XNode::NodeType getType() { return XNode::NodeTypeImage; }
    
    void update();
    void draw(float opacity = 1.0f);

	void loadXml( ci::XmlTree &xml );
	void setTexture(const std::string &path);
	std::string getTexture() const { return mTexturePath; }
	void setAlignment(const std::string &alignment);
	std::string getAlignment() const;
protected:
	XImage() : mTexturePath(""), mTexturePosition(ci::vec2(0, 0)), mTextureDimensions(ci::vec2(0,0)), mAlignment(Left) {}
    
	std::string mTexturePath;
    ci::gl::TextureRef mTexture;
	ci::vec2 mTexturePosition;
	ci::vec2 mTextureDimensions;
	AlignmentType mAlignment;
};

}