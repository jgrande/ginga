#pragma once

#include "types.h"
#include "rect.h"
#include "size.h"
#include <string>
#include <vector>
#include <list>

namespace canvas {

class Window;

class Canvas {
public:
	Canvas();
	virtual ~Canvas();

	//	Initialization
	bool initialize( Window *win );
	void finalize();

	//	Surface creation
	Surface *createSurface( const Size &size );
	Surface *createSurface( const Rect &rect );
	Surface *createSurfaceFromPath( const std::string &file );
	Surface *createSurface( ImageData *img );
	void destroy( SurfacePtr &surface );

	//	Getters
	const Size &size() const;
	virtual std::string name()=0;

	//	Flush
	void flush();
	void beginDraw();
	void endDraw();
	void invalidateRegion( const Rect &rect );
	const std::vector<Rect> &dirtyRegions() const;

	//	Store
	bool saveAsImage( const std::string &file );
	bool equalsImage( const std::string &file );

	void reset();
	static Canvas *create();

protected:
	virtual Surface *createSurfaceImpl( ImageData *img )=0;
	virtual Surface *createSurfaceImpl( const Rect &rect )=0;
	virtual Surface *createSurfaceImpl( const std::string &file )=0;

	void flushImpl( Surface *layer );
	Surface *addSurface( Surface *surface );
	void addDirtyRegion( const Rect &rect );

	//	Getters
	Window *win() const;

private:
	Size _size;
	Window *_win;
	int _inTransaction;
	std::vector<Rect> _dirtyRegions;
	std::vector<Surface *> _surfaces;
	double _joinPercentage;

	bool _showBlittedRegions;
	int _nTrackedFlush;
	Surface *_blittedRegionsSurface;
	std::vector<Color> _blittedRegionsColors;
	std::list< std::vector<Rect> > _previousDirtyRegions;
};

}

