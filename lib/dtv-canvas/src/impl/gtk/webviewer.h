#pragma once

#include "../../webviewer.h"

typedef struct _GtkWidget GtkWidget;

namespace canvas {

class System;

namespace gtk {

class WebViewer : public canvas::WebViewer {
public:
	WebViewer( canvas::System *sys, Surface *surface );
	virtual ~WebViewer( void );

	virtual bool load( const std::string &file );
	virtual void stop();
	virtual void draw();
	
	//	Aux
	void onFinished();

protected:
	virtual void onResized();

	//	Aux
	void stopPage();

private:
	System *_sys;	
	GtkWidget *_window;
	GtkWidget *_view;
};

}
}

