#pragma once

#include "../../window.h"

typedef struct _GtkWidget GtkWidget;
typedef union  _GdkEvent GdkEvent;

namespace canvas {

namespace cairo {
	class Surface;
}

namespace gtk {

class Window : public canvas::Window {
public:
	Window();
	virtual ~Window();

	//	Initialization
	virtual bool initialize();
	virtual void finalize();

	//	Layer methods
	virtual Surface *lockLayer( Canvas *canvas );
	virtual void renderLayer( Surface *surface, const std::vector<Rect> &dirtyRegions );
	virtual void unlockLayer( Surface *surface );

	//	Aux	
	void draw( GtkWidget *da, const Rect &rect );
	void updateWindow( GdkEvent *event );
	GtkWidget *widget() const;

protected:
	//	Overlays
	virtual canvas::VideoOverlay *createOverlayInstance() const;

	//	Mode methods
	void setFullscreenMode();
	void setNormalMode();

private:
	GtkWidget *_window;
	cairo::Surface *_surface;
};
	
}
}

