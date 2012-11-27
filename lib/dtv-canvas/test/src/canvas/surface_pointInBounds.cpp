#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"

// Tests pointInBounds with a point inside the surface
TEST_F( Surface, pointInBounds_point_inside_the_surface ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(10,10);
	ASSERT_TRUE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point in the top-left corner of the surface
TEST_F( Surface, pointInBounds_point_top_left ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(0,0);
	ASSERT_TRUE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point in the top of the surface
TEST_F( Surface, pointInBounds_point_top ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(360,0);
	ASSERT_TRUE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point in the top-right corner of the surface
TEST_F( Surface, pointInBounds_point_top_right ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(719,0);
	ASSERT_TRUE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point in the right of the surface
TEST_F( Surface, pointInBounds_point_right ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(719,288);
	ASSERT_TRUE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point in the bottom-right corner of the surface
TEST_F( Surface, pointInBounds_point_bottom_right ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(719,575);
	ASSERT_TRUE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point in the bottom of the surface
TEST_F( Surface, pointInBounds_point_bottom ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(360,575);
	ASSERT_TRUE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point in the bottom-left corner of the surface
TEST_F( Surface, pointInBounds_point_bottom_left ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(0,575);
	ASSERT_TRUE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point in the left of the surface
TEST_F( Surface, pointInBounds_point_left ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(0,288);
	ASSERT_TRUE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point outside the surface (top-left)
TEST_F( Surface, pointInBounds_point_outside_top_left ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(-1,-1);
	ASSERT_FALSE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point outside the surface (top)
TEST_F( Surface, pointInBounds_point_outside_top ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(360,-1);
	ASSERT_FALSE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point outside the surface (top-right)
TEST_F( Surface, pointInBounds_point_outside_top_right ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(720,-1);
	ASSERT_FALSE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point outside the surface (right)
TEST_F( Surface, pointInBounds_point_outside_right ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(720,288);
	ASSERT_FALSE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point outside the surface (bottom-right)
TEST_F( Surface, pointInBounds_point_outside_bottom_right ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(720,576);
	ASSERT_FALSE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point outside the surface (bottom)
TEST_F( Surface, pointInBounds_point_outside_bottom ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(360,576);
	ASSERT_FALSE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point outside the surface (bottom-left)
TEST_F( Surface, pointInBounds_point_outside_bottom_left ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(-1,576);
	ASSERT_FALSE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

// Tests pointInBounds with a point outside the surface (left)
TEST_F( Surface, pointInBounds_point_outside_left ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	canvas::Point p(-1,288);
	ASSERT_FALSE( s->pointInBounds(p) );

	getCanvas()->destroy( s );
}

