#include "canvas.h"
#include "surface.h"
#include "window.h"
#include "dummy/canvas.h"
#include "generated/config.h"
#if SYS_CANVAS_USE_CAIRO
#	include "impl/cairo/canvas.h"
#endif
#include <util/cfg/configregistrator.h>
#include <util/mcr.h>
#include <util/log.h>
#include <boost/foreach.hpp>
#include <boost/math/special_functions/round.hpp>
#include <limits.h>

#define LAYER(code)  {	  \
	Window *w = win(); \
	Surface *layer = w->lockLayer(this); \
	if (layer) { \
		if (!_inTransaction) { flushImpl( layer ); } \
		code \
		w->unlockLayer( layer ); \
	} \
	else { LWARN("Canvas", "invalid layer" ); } }


namespace canvas {

REGISTER_INIT_CONFIG( gui_canvas ) {
	root().addNode( "canvas" )
#if SYS_CANVAS_USE_CAIRO
	.addValue( "use", "Canvas to instance", std::string("cairo") )
#else
	.addValue( "use", "Canvas to instance", std::string("dummy") )
#endif

	.addValue( "joinPercentage", "Extra area that can be used when joining dirty regions", 0.2 )

	.addNode( "showBlits" )
		.addValue( "enabled", "Delimit blitted regions", false )
		.addValue( "track", "Number of flush to trak (max=5)", 5 );

	root()("canvas").addNode( "size" )
		.addValue( "width", "Canvas width", 720 )
		.addValue( "height", "Canvas height", 576 );
}

Canvas *Canvas::create() {
	std::string use = util::cfg::getValue<std::string>("gui.canvas.use");

	LINFO("Canvas", "Using canvas: %s", use.c_str());

#if SYS_CANVAS_USE_CAIRO
	if (use == "cairo") {
		return new cairo::Canvas();
	}
#endif
	return new dummy::Canvas();
}

Canvas::Canvas()
{
	_win = NULL;
	_inTransaction = 0;
	_showBlittedRegions = false;
	_blittedRegionsSurface = NULL;
	_joinPercentage  = util::cfg::getValue<double>("gui.canvas.joinPercentage");
}

Canvas::~Canvas()
{
	if (_surfaces.size()) {
		LWARN("Canvas", "not all surfaces destroyed: size=%d", _surfaces.size() );
	}
	assert(!_win);
}

//	Initialization
bool Canvas::initialize( Window *win ) {
	assert(win);

	//	Get canvas size from config
	util::cfg::PropertyNode &sizeNode = util::cfg::get("gui.canvas.size");
	_size.w = sizeNode.get<int>( "width" );
	_size.h = sizeNode.get<int>( "height" );
	_dirtyRegions.push_back(Rect(Point(0,0),_size));

	//	Setup window
	_win = win;

	_showBlittedRegions = util::cfg::getValue<bool>("gui.canvas.showBlits.enabled");
	_nTrackedFlush = util::cfg::getValue<int>("gui.canvas.showBlits.track");
	if (_nTrackedFlush<1 || _nTrackedFlush>5) {
		throw std::runtime_error( "Invalid showBlits.track value. Must be between 1 and 5" );
	}
	if (_showBlittedRegions) {
		_blittedRegionsSurface = createSurface(size());
		_blittedRegionsSurface->setZIndex(INT_MAX);
		_blittedRegionsColors.push_back(Color(255,0,0));
		_blittedRegionsColors.push_back(Color(255,255,0));
		_blittedRegionsColors.push_back(Color(0,255,0));
		_blittedRegionsColors.push_back(Color(0,255,255));
		_blittedRegionsColors.push_back(Color(0,0,255));
	}

	return true;
}

void Canvas::finalize() {
	_win = NULL;
	if (_showBlittedRegions) {
		destroy(_blittedRegionsSurface);
	}
}

Surface *Canvas::createSurface( const Size &size ) {
	Rect rect(0,0,size.w,size.h);
	return createSurface( rect );
}

Surface *Canvas::createSurface( const Rect &rect ) {
	try {
		return addSurface( createSurfaceImpl( rect ) );
	} catch (...) {}
	return NULL;
}

Surface *Canvas::createSurfaceFromPath( const std::string &file ) {
	try {
		return addSurface( createSurfaceImpl( file ) );
	} catch (...) {}
	return NULL;
}

Surface *Canvas::createSurface( ImageData *img ) {
	try {
		return createSurfaceImpl( img );
	} catch (...) {}
	return NULL;
}

const Size &Canvas::size() const {
	return _size;
}

Surface *Canvas::addSurface( Surface *surface ) {
	LDEBUG("Canvas", "Add surface: surface=%p", surface );
	assert(surface);
	_surfaces.push_back( surface );
	return surface;
}

void Canvas::destroy( SurfacePtr &surface ) {
	LDEBUG("Canvas", "Destroy surface: surface=%p", surface );
	assert(surface);
	std::vector<Surface *>::iterator it=std::find(
		_surfaces.begin(), _surfaces.end(), surface );
	if (it != _surfaces.end()) {
		delete (*it);
		_surfaces.erase( it );
	}
	surface = NULL;
}

struct SortSurfaces {
	bool operator()( Surface *s1, Surface *s2 ) const {
		return s1->getZIndex() < s2->getZIndex();
	}
};

const std::vector<Rect> &Canvas::dirtyRegions() const {
	return _dirtyRegions;
}

void Canvas::addDirtyRegion( const Rect &rect ) {
	LTRACE("Canvas", "addDirtyRegion: rect(%d,%d,%d,%d)", rect.x, rect.y, rect.w, rect.h);
	_dirtyRegions.push_back( rect );

	//	Invalidate surfaces
	BOOST_FOREACH( Surface *surface, _surfaces ) {
		surface->invalidateRegion( rect );
	}
}

void Canvas::invalidateRegion( const Rect &rect ) {
	if (!rect.isEmpty()) {
		std::vector<Rect> toErase;
		std::vector<Rect> toAdd;

		BOOST_FOREACH( const Rect &dirtyRegion, _dirtyRegions ) {
			if (dirtyRegion.includes( rect )) {
				// If rect is already included in any dirty region return
				return;
			} else if ( rect.includes( dirtyRegion ) ) {
				// If rect includes a region, mark to remove it
				toErase.push_back( dirtyRegion );
			} else {
				Rect composedRect = rect.encompass(dirtyRegion);
				Rect intersection;
				rect.intersection(dirtyRegion, intersection);
				int extraJoinedArea = composedRect.area()-rect.area()-dirtyRegion.area()+intersection.area();
				int maxExtraJoinedArea = boost::math::iround(composedRect.area() * _joinPercentage);

				if (extraJoinedArea<=maxExtraJoinedArea) {
					// If the resulting join area of rect and dirtyRegion
					// is smaller enough, add the new composed rect
					toErase.push_back(dirtyRegion);
					toAdd.push_back(composedRect);
				} else if (intersection.area()>0) {
					// Substract dirtyRegion from rect and add resulting
					// rectangles that don't intersect with dirtyRegion
					if (rect.goesInto(dirtyRegion)) {
						toAdd.push_back(rect.cut(intersection));
					} else if (dirtyRegion.goesInto(rect)) {
						toErase.push_back(dirtyRegion);
						toAdd.push_back(dirtyRegion.cut(intersection));
						toAdd.push_back(rect);
					}
				}
			}
		}

		// Remove old regions
		BOOST_FOREACH( const Rect region, toErase ) {
			std::vector<Rect>::iterator it=std::find( _dirtyRegions.begin(), _dirtyRegions.end(), region );
			if (it != _dirtyRegions.end()) {
				_dirtyRegions.erase( it );
			}
		}

		if (toAdd.size()>0) {
			// If the original region has changed invalidate new regions
			BOOST_FOREACH( const Rect& r, toAdd ) {
				invalidateRegion(r);
			}
		} else {
			// else add the original region
			addDirtyRegion( rect );
		}
	}
}

void Canvas::flush() {
	if (!_inTransaction) {
		Window *w = win();
		Surface *layer = w->lockLayer( this );
		if (layer) {
			flushImpl( layer );
			w->unlockLayer( layer );
		}
		else {
			LWARN("Canvas", "invalid layer" );
		}
	}
}

void Canvas::beginDraw() {
	_inTransaction++;
}

void Canvas::endDraw() {
	if (_inTransaction > 0) {
		_inTransaction--;
		flush();
	}
}

void Canvas::flushImpl( Surface *layer ) {
	assert(layer->getCompositionMode() == composition::source_over);
	std::vector<Surface *> toBlit;

	if (_showBlittedRegions && !_dirtyRegions.empty()) {
		_previousDirtyRegions.push_back(std::vector<Rect>(_dirtyRegions.begin(), _dirtyRegions.end()));
		_blittedRegionsSurface->autoFlush(false);
		if (_previousDirtyRegions.size()>(unsigned)_nTrackedFlush) {
			_previousDirtyRegions.pop_front();
		}
		_blittedRegionsSurface->clear();
		int i = _previousDirtyRegions.size();
		BOOST_FOREACH( std::vector<Rect> tmp,  _previousDirtyRegions ) {
			_blittedRegionsSurface->setColor(_blittedRegionsColors[--i]);
			BOOST_FOREACH( const Rect &dirtyRegion, tmp ) {
				_blittedRegionsSurface->drawRect( dirtyRegion );
			}
		}
		_blittedRegionsSurface->autoFlush(true);
	}

	//	Check if any surface is dirty
	bool isDirty=false;
	BOOST_FOREACH( Surface *surface, _surfaces ) {
		//	Check if surface is dirty
		isDirty |= surface->isDirty();
		if (surface->isDirty()) {
			if (surface->autoFlush() && surface->isVisible()) {
				toBlit.push_back( surface );
			}
			surface->clearDirty();
		}
	}

	//	Need blit any surface?
	if (isDirty || !_dirtyRegions.empty()) {
		Rect blitRect;

		//	Sort surfaces by zIndex
		std::stable_sort( toBlit.begin(), toBlit.end(), SortSurfaces() );

		LDEBUG("Canvas", "Flush: toBlit=%d, regions=%d", toBlit.size(), _dirtyRegions.size() );

		//	For each dirty region
		BOOST_FOREACH( const Rect &dirtyRegion, _dirtyRegions ) {
			LTRACE("Canvas", "Dirty region: (%d, %d, %d, %d)", dirtyRegion.x, dirtyRegion.y, dirtyRegion.w, dirtyRegion.h );
			
			//	Clear region
			Rect intersection;
			if (layer->getBounds().intersection( dirtyRegion, intersection )) {
				layer->clear( intersection );
			}

			//	Blit each surface
			BOOST_FOREACH( Surface *surface, toBlit ) {
				//	Need blit?
				if (surface->getDirtyRegion( dirtyRegion, blitRect )) {
					LDEBUG("Canvas", "Surface to blit: %p, zIndex=%d", surface, surface->getZIndex() );

					//	Set composition mode from surface
					layer->setCompositionMode( surface->flushCompositionMode() );					
					
					//	Blit dirty region
					Point point( blitRect.x, blitRect.y );
					Point surfacePos = surface->getLocation();
					blitRect.x -= surfacePos.x;
					blitRect.y -= surfacePos.y;
					layer->blit( point, surface, blitRect );
				}
			}
			layer->setCompositionMode( composition::source_over );
		}

		//	Render layer
		win()->renderLayer( layer, _dirtyRegions );

		//	Clean dirty regions
		_dirtyRegions.clear();
	}
}
	
bool Canvas::saveAsImage( const std::string &file ) {
	bool result=false;
	LAYER( result=layer->saveAsImage( file ); );
	return result;
}

bool Canvas::equalsImage( const std::string &file ) {
	bool result=false;
	LAYER( result=layer->equalsImage( file ); );
	return result;
}

Window *Canvas::win() const {
	return _win;
}

void Canvas::reset() {
	Surface *layer = _win->lockLayer(this);
	std::vector<Surface *> toErase;
	BOOST_FOREACH( Surface* s, _surfaces ) {
		if (s!=layer) {
			toErase.push_back(s);
		}
	}
	BOOST_FOREACH( Surface* s, toErase ) {
		std::vector<Surface *>::iterator it = find(_surfaces.begin(), _surfaces.end(), s);
		if (it!=_surfaces.end()) {
			_surfaces.erase(it);
		}
	}
	flush();
}

}
