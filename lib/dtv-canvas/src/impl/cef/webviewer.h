#pragma once

#include "../../size.h"
#include "../../webviewer.h"
#pragma warning( push )
#pragma warning( disable: 4100 )
#include <cef/cef.h>
#pragma warning( pop )
#include <boost/thread/mutex.hpp>

namespace canvas {

class Surface;
class System;

namespace cef {

class WebHandler;

class WebViewer : public canvas::WebViewer {
public:
	WebViewer( System *sys, Surface *surface );
	virtual ~WebViewer( void );

	static bool init();
	static void fin();

	virtual bool load( const std::string &file );
	virtual void stop();
	virtual void draw();

	//	Aux
	void paint( const char *buffer );
	void setupBrowser( const CefRefPtr<CefBrowser> &browser );

protected:
	virtual void onResized();
	void resize();
	int bitmapSize() const;

private:
	System *_sys;
	CefRefPtr<CefBrowser> _browser;
	boost::mutex _mutex;
	char *_buf;
	int _bufSize;
	Size _size;
	bool _valid;
};

}
}

