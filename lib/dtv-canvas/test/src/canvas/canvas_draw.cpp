#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"

// Test flush when no surface was created
TEST_F( Surface, canvas_draw_basic_empty ) {
	getCanvas()->beginDraw();
	getCanvas()->endDraw();	
	ASSERT_TRUE( util::compareImages(getCanvas(), "nothing" ) );
}

// Test flush with one surface visible
TEST_F( Surface, canvas_draw_basic_ok ) {
	canvas::Surface* s = getCanvas()->createSurfaceFromPath( util::getImageName("red.jpg") );

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	getCanvas()->beginDraw();
	ASSERT_FALSE( util::compareImages( getCanvas(), "canvas_flush/flush_with_surface_visible" ) );
	getCanvas()->endDraw();
	ASSERT_TRUE( util::compareImages( getCanvas(), "canvas_flush/flush_with_surface_visible" ) );	

	getCanvas()->destroy( s );
}

TEST_F( Surface, canvas_draw_recursive_ok ) {
	canvas::Surface* s = getCanvas()->createSurfaceFromPath( util::getImageName("red.jpg") );

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);

	getCanvas()->beginDraw();
	getCanvas()->beginDraw();
	getCanvas()->beginDraw();
	ASSERT_FALSE( util::compareImages( getCanvas(), "canvas_flush/flush_with_surface_visible" ) );
	getCanvas()->endDraw();
	ASSERT_FALSE( util::compareImages( getCanvas(), "canvas_flush/flush_with_surface_visible" ) );
	getCanvas()->endDraw();
	ASSERT_FALSE( util::compareImages( getCanvas(), "canvas_flush/flush_with_surface_visible" ) );
	getCanvas()->endDraw();	
	ASSERT_TRUE( util::compareImages( getCanvas(), "canvas_flush/flush_with_surface_visible" ) );	

	getCanvas()->destroy( s );
}

