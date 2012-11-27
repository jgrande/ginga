#pragma once

#include "../../rect.h"
#include "../../videooverlay.h"

typedef struct _GtkWidget GtkWidget;
typedef union  _GdkEvent GdkEvent;

namespace canvas {
namespace gtk {

class Window;

class VideoOverlay : public canvas::VideoOverlay {
public:
	VideoOverlay( Window *win );
	virtual ~VideoOverlay( void );

	//	Initialization
	virtual bool initialize( const Rect &rect );
	virtual void finalize();

	virtual bool move( const Point &point );
	virtual bool resize( const Size &size );
	virtual void size( Size &size );	
	virtual bool getDescription( VideoDescription &desc );

	//	Aux
	void onMainChanged( GdkEvent *event );

protected:
	void config();

private:
	Rect       _rect;
	Window    *_main;
	GtkWidget *_window;
	bool       _needMove;
};

}
}

