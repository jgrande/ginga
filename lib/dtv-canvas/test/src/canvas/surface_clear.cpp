#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"

class SurfaceClear : public Surface {
protected:
    std::string getSubDirectory() const { return "Clear"; }
};

// Create surface from an image and then clear all the surface
TEST_F( SurfaceClear, basic ) {
    canvas::Surface* s = getCanvas()->createSurfaceFromPath(util::getImageName( "image.png"));

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "basic_before_clear" ) ) );
    ASSERT_TRUE( s->clear() );
    ASSERT_TRUE( util::compareImages( getCanvas(), "nothing" ) );

    getCanvas()->destroy( s );
}

// Create surface from an image and then clear part of the surface
TEST_F( SurfaceClear, basic_rect ) {
    canvas::Surface* s = getCanvas()->createSurfaceFromPath(util::getImageName( "image.png"));

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("basic_before_clear") ) );
    ASSERT_TRUE( s->clear(canvas::Rect(0,0,100,100)) );
    ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("basic_after_clear_rect") ) );

    getCanvas()->destroy( s );
}

// Create surface from rect, fill a rect with color and then clear all the surface
TEST_F( SurfaceClear, basic_color ) {
    canvas::Rect rect(0,0,200,200);
    canvas::Surface* s = getCanvas()->createSurface(rect);

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor( canvas::Color(255,0,0) );
    ASSERT_TRUE( s->fillRect(rect) );
    ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("basic_color_before_clear") ) );
    ASSERT_TRUE( s->clear() );
    ASSERT_TRUE( util::compareImages( getCanvas(), "nothing" ) );

    getCanvas()->destroy( s );
}

// Create surface from rect, fill a rect with color and then clear part of the surface
TEST_F( SurfaceClear, basic_color_rect ) {
    canvas::Rect rect(0,0,200,200);
    canvas::Surface* s = getCanvas()->createSurface(rect);

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor( canvas::Color(255,0,0) );
    ASSERT_TRUE( s->fillRect(rect) );
    ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("basic_color_before_clear") ) );
    ASSERT_TRUE( s->clear(canvas::Rect(0,0,100,100)) );
    ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("basic_color_after_clear_rect") ) );

    getCanvas()->destroy( s );
}

// Surface rendered from an image and then a rectangle inside is cleared.
TEST_F( SurfaceClear, clear_rect_with_surface_created_from_path ) {
	canvas::Surface* s = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);
	ASSERT_TRUE( s->clear(canvas::Rect(50, 50, 50, 100)) );
	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "clear_rect_with_surface_created_from_path" ) ) );

	getCanvas()->destroy( s );
}

// Clear a region with width lower than 0
TEST_F( SurfaceClear, rect_width_lt_0 ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(320,238,-1,100) ) );

	getCanvas()->destroy( s );
}

// Clear a region with height lower than 0
TEST_F( SurfaceClear, rect_height_lt_0 ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(320,238,100,-1) ) );

	getCanvas()->destroy( s );
}

// Clear a region with height and width lower than 0
TEST_F( SurfaceClear, rect_height_and_width_lt_0 ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(320,238,-1,-1) ) );

	getCanvas()->destroy( s );
}

// Clear a region completely outside the surface (top)
TEST_F( SurfaceClear, completely_out_top ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(310,-100,100,100) ) );

	getCanvas()->destroy( s );
}

// Clear a region completely outside the surface (bottom)
TEST_F( SurfaceClear, completely_out_bottom ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(310,576,100,100) ) );

	getCanvas()->destroy( s );
}

// Clear a region completely outside the surface (left)
TEST_F( SurfaceClear, completely_out_left ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(-100,238,100,100) ) );

	getCanvas()->destroy( s );
}

// Clear a region completely outside the surface (right)
TEST_F( SurfaceClear, completely_out_right ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(720,238,100,100) ) );

	getCanvas()->destroy( s );
}

// Clear a region three vertices outside the surface (top-left)
TEST_F( SurfaceClear, three_vertices_out_top_left ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(-1,-1,100,100) ) );

	getCanvas()->destroy( s );
}

// Clear a region three vertices outside the surface (top-right)
TEST_F( SurfaceClear, three_vertices_out_top_right ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(621,-1,100,100) ) );

	getCanvas()->destroy( s );
}

// Clear a region three vertices outside the surface (bottom-right)
TEST_F( SurfaceClear, three_vertices_out_bottom_right ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(621,477,100,100) ) );

	getCanvas()->destroy( s );
}

// Clear a region three vertices outside the surface (bottom-left)
TEST_F( SurfaceClear, three_vertices_out_bottom_left ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(-1,477,100,100) ) );

	getCanvas()->destroy( s );
}

// Clear a region two vertices outside the surface (top)
TEST_F( SurfaceClear, two_vertices_out_top ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(310,-1,100,100) ) );

	getCanvas()->destroy( s );
}

// Clear a region two vertices outside the surface (bottom)
TEST_F( SurfaceClear, two_vertices_out_bottom ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(310,477,100,100) ) );

	getCanvas()->destroy( s );
}

// Clear a region two vertices outside the surface (left)
TEST_F( SurfaceClear, two_vertices_out_left) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(-1,238,100,100) ) );

	getCanvas()->destroy( s );
}

// Clear a region two vertices outside the surface (right)
TEST_F( SurfaceClear, two_vertices_out_right) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(621,238,100,100) ) );

	getCanvas()->destroy( s );
}

// Clear a region four vertices outside the surface including the surface
TEST_F( SurfaceClear, four_vertices_out_include ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(-1,-1,722,578) ) );

	getCanvas()->destroy( s );
}

// Clear a region four vertices outside the surface crossing the surface horizontally
TEST_F( SurfaceClear, four_vertices_out_crossing_horizontally ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(-1,238,722,100) ) );

	getCanvas()->destroy( s );
}

// Clear a region four vertices outside the surface crossing the surface vertically
TEST_F( SurfaceClear, four_vertices_out_crossing_vertically ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	ASSERT_FALSE( s->clear(canvas::Rect(310,-1,100,578) ) );

	getCanvas()->destroy( s );
}

// Test markDirty after clearing all the surface
TEST_F( SurfaceClear, markDirty_clear ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);
	s->setColor(canvas::Color(255,0,0));
	getCanvas()->flush();

	ASSERT_TRUE( s->clear() );

	std::vector<canvas::Rect> dirtyRegions = getCanvas()->dirtyRegions();

	ASSERT_FALSE( dirtyRegions.empty() );
	ASSERT_TRUE( dirtyRegions.size() == 1 );

	ASSERT_TRUE( dirtyRegions.at(0) == rect );

	getCanvas()->destroy( s );
}

// Test markDirty after clearing some rects
TEST_F( SurfaceClear, markDirty_clear_rect ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);
	s->setColor(canvas::Color(255,0,0));
	getCanvas()->flush();

	canvas::Rect r1(0,0,10,10),
				 r2(20,20,100,100),
				 r3(200,200,1,1);

	ASSERT_TRUE( s->clear(r1) );
	ASSERT_TRUE( s->clear(r2) );
	ASSERT_TRUE( s->clear(r3) );

	std::vector<canvas::Rect> dirtyRegions = getCanvas()->dirtyRegions();

	ASSERT_FALSE( dirtyRegions.empty() );
	ASSERT_TRUE( dirtyRegions.size() == 3 );

	ASSERT_TRUE( dirtyRegions.at(0) == r1 );
	ASSERT_TRUE( dirtyRegions.at(1) == r2 );
	ASSERT_TRUE( dirtyRegions.at(2) == r3 );

	getCanvas()->destroy( s );
}

// Comparar una imagen con fondo negro con una imagen transparente (para probar el compare image)
TEST_F( SurfaceClear, compare_black_background_with_transparent_background ) {
    canvas::Rect rect(0,0,720,576);
    canvas::Surface* s = getCanvas()->createSurface( rect );

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);

    s->setColor(canvas::Color(0,0,0,255));
    ASSERT_TRUE( s->fillRect(rect) );
    ASSERT_TRUE( util::compareImages(getCanvas(), "nothing_black_background") );
    ASSERT_FALSE( util::compareImages(getCanvas(), "nothing") );

    getCanvas()->destroy( s );
}
