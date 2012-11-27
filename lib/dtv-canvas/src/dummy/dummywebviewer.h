#pragma once

#include "../webviewer.h"

namespace canvas {
namespace dummy {

class WebViewer : public canvas::WebViewer {
public:
	WebViewer( Surface *surface );
	virtual ~WebViewer( void );

	virtual bool load( const std::string &file );
	virtual void stop();
	virtual void draw();
};

}
}

