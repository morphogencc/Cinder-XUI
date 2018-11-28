#pragma once
#include "XRect.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
//#include "cinder/gl/Texture.h"
#include "ciWMFVideoPlayer.h"

namespace xui {

typedef std::shared_ptr<class XMovie> XMovieRef;

class XMovie : public XRect
{
public:
    static XMovieRef create();
    static XMovieRef create( ci::XmlTree &xml );

	virtual XNode::NodeType getType() { return XNode::NodeTypeMovie; }
    
    void update( double elapsedSeconds );
    void draw(float opacity = 1.0f);

	void loadXml( ci::XmlTree &xml );
    
	virtual bool getLoop() const { return mIsLooping; }
	virtual void setLoop(bool loop) { mIsLooping = loop; mMovie->setLoop(mIsLooping); }
	virtual bool getFullscreen() const { return mIsFullscreen; }
	virtual void setFullscreen(bool fullscreen);
	virtual void stop() { mMovie->stop(); }
	virtual void play() { mMovie->play(); }
	virtual void pause() { mMovie->pause(); }
protected:
	XMovie() : mIsLooping(false), mIsFullscreen(false) {}
    
	bool mIsLooping;
	bool mIsFullscreen;
	ciWMFVideoPlayerRef mMovie;
};

}