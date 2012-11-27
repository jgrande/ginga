#pragma once

#include <string>
#include <boost/function.hpp>
namespace canvas {

class Point;
class Size;
class System;
class Surface;

class WebViewer {
public:
	explicit WebViewer( Surface *surface );
	virtual ~WebViewer( void );

	virtual bool load( const std::string &uri )=0;
	virtual void stop()=0;
	virtual void draw()=0;

	//	Widget
	virtual void resize( const Size &size );
	virtual void move( const Point &point );

	//	Events
	typedef boost::function<void (void)> Callback;
	void setCallbackLoadFinished( const Callback &callback );

	//	Instance creation
	static WebViewer *create( System *sys, Surface *s );

protected:
	virtual void onResized();
	Surface *surface();
	void runCallbackLoadFinished();

private:
	Surface *_surface;
	Callback _callbackFinished;
	WebViewer() {}
};

}

