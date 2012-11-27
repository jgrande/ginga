#pragma once

#include "types.h"
#include "rect.h"
#include <vector>
#include <string>

namespace canvas {

class VideoOverlay;

class Window {
public:
	Window();
	virtual ~Window();
	
	//	Initialization
	virtual bool initialize();
	virtual void finalize();

	//	Getters
	const std::string &title() const;
	const Size &size() const;

	//	Video overlays
	VideoOverlay *createVideoOverlay();
	void destoyVideoOverlay( VideoOverlayPtr &ptr );

	//	Layer methods
	virtual Surface *lockLayer( Canvas *canvas )=0;
	virtual void renderLayer( Surface *surface, const std::vector<Rect> &dirtyRegions )=0;
	virtual void unlockLayer( Surface *surface );

	//	Video methods
	virtual int getFormat( char *chroma, unsigned *width, unsigned *height, unsigned *pitches, unsigned *lines );
	virtual void cleanup();
	virtual void *allocFrame( void **pixels );
	virtual void freeFrame( void *frame );
	virtual void renderFrame( void *frame );

	//	Window methods
	void redraw( Canvas *canvas );
	void redraw( Canvas *canvas, const Rect &r );

	//	Instance creation
	static Window *create();

protected:
	//	Mode methods
	void setMode();
	virtual void setFullscreenMode();
	virtual void setNormalMode();
	void setSize( int width, int height );

	//	Overlays
	const std::vector<VideoOverlayPtr> &overlays() const;
	virtual VideoOverlay *createOverlayInstance() const;

private:
	std::string _title;
	Size _size;
	bool _isFullScreen;
	std::vector<VideoOverlayPtr> _overlays;
};
	
}

