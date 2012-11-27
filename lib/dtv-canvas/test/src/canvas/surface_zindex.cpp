#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"

class SurfaceZIndex: public Surface {
protected:
    std::string getSubDirectory() const { return "ZIndex"; }
};

// Test default zindex.
TEST_F( SurfaceZIndex, default ) {
	canvas::Surface* s = getCanvas()->createSurface( canvas::Rect(0,0,10,10) );

	ASSERT_TRUE( s != NULL );
	ASSERT_TRUE( s->getZIndex() == 1 );

	getCanvas()->destroy( s );
}

// Two surfaces intersected with different zIndex (s2 over s1).
TEST_F( SurfaceZIndex, red_over_blue ) {
	canvas::Surface* s1 = getCanvas()->createSurface( canvas::Rect(100, 100, 100, 100) );
	canvas::Surface* s2 = getCanvas()->createSurface( canvas::Rect(50, 50, 100, 100) );

	ASSERT_TRUE(s1 && s2);
	s1->autoFlush(true);
	s2->autoFlush(true);
	s1->setColor(canvas::Color(0, 0, 255));
	s2->setColor(canvas::Color(255, 0, 0));
	s1->fillRect(canvas::Rect(0,0,100,100));
	s2->fillRect(canvas::Rect(0,0,100,100));
	s2->setZIndex(2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("two_surfaces_intersected_red_over_blue") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Two surfaces intersected with different zIndex (s1 over s2).
TEST_F( SurfaceZIndex, blue_over_red ) {
	canvas::Surface* s1 = getCanvas()->createSurface( canvas::Rect(100, 100, 100, 100) );
	canvas::Surface* s2 = getCanvas()->createSurface( canvas::Rect(50, 50, 100, 100) );

	ASSERT_TRUE(s1 && s2);
	s1->autoFlush(true);
	s2->autoFlush(true);
	s1->setColor(canvas::Color(0, 0, 255));
	s2->setColor(canvas::Color(255, 0, 0));
	s1->fillRect(canvas::Rect(0,0,100,100));
	s2->fillRect(canvas::Rect(0,0,100,100));
	s1->setZIndex(2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("two_surfaces_intersected_blue_over_red") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Two surfaces intersected with different zIndex swapped (s1 over s2 -> s2 over s1).
TEST_F( SurfaceZIndex, swap ) {
	canvas::Surface* s1 = getCanvas()->createSurface( canvas::Rect(100, 100, 100, 100) );
	canvas::Surface* s2 = getCanvas()->createSurface( canvas::Rect(50, 50, 100, 100) );

	ASSERT_TRUE(s1 && s2);
	s1->autoFlush(true);
	s2->autoFlush(true);
	s1->setColor(canvas::Color(0, 0, 255));
	s2->setColor(canvas::Color(255, 0, 0));
	s1->fillRect(canvas::Rect(0,0,100,100));
	s2->fillRect(canvas::Rect(0,0,100,100));
	s1->setZIndex(2);

	s2->setZIndex(3);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("two_surfaces_intersected_red_over_blue") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Three surfaces intersected with different zindex (s2 over s1, s3 over s1 and s3 over s2).
TEST_F( SurfaceZIndex, three_surfaces_intersected ) {
	canvas::Surface* s1 = getCanvas()->createSurface( canvas::Rect(50, 50, 100, 100) );
	canvas::Surface* s2 = getCanvas()->createSurface( canvas::Rect(125, 75, 100, 100) );
	canvas::Surface* s3 = getCanvas()->createSurface( canvas::Rect(75, 125, 100, 100) );

	ASSERT_TRUE(s1 && s2 && s3);
	s1->autoFlush(true);
	s2->autoFlush(true);
	s3->autoFlush(true);
	s1->setColor(canvas::Color(0, 0, 255));
	s2->setColor(canvas::Color(255, 0, 0));
	s3->setColor(canvas::Color(0, 255, 0));
	s1->fillRect(canvas::Rect(0,0,100,100));
	s2->fillRect(canvas::Rect(0,0,100,100));
	s3->fillRect(canvas::Rect(0,0,100,100));
	s2->setZIndex(2);
	s3->setZIndex(3);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("three_surfaces_intersected") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
	getCanvas()->destroy( s3 );
}

// Three surfaces intersected with different zindex (s2 over s1, s3 over s1 and s3 over s2) swapped.
TEST_F( SurfaceZIndex, three_surfaces_intersected_swap ) {
	canvas::Surface* s1 = getCanvas()->createSurface( canvas::Rect(50, 50, 100, 100) );
	canvas::Surface* s2 = getCanvas()->createSurface( canvas::Rect(125, 75, 100, 100) );
	canvas::Surface* s3 = getCanvas()->createSurface( canvas::Rect(75, 125, 100, 100) );

	ASSERT_TRUE(s1 && s2 && s3);
	s1->autoFlush(true);
	s2->autoFlush(true);
	s3->autoFlush(true);
	s1->setColor(canvas::Color(0, 0, 255));
	s2->setColor(canvas::Color(255, 0, 0));
	s3->setColor(canvas::Color(0, 255, 0));
	s1->fillRect(canvas::Rect(0,0,100,100));
	s2->fillRect(canvas::Rect(0,0,100,100));
	s3->fillRect(canvas::Rect(0,0,100,100));
	s2->setZIndex(2);
	s3->setZIndex(3);

	s1->setZIndex(4);
	s2->setZIndex(5);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("three_surfaces_intersected_swapped") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
	getCanvas()->destroy( s3 );
}

// Two surfaces intersected with equal zIndex.
TEST_F( SurfaceZIndex, two_surfaces_equal_zindex ) {
	canvas::Surface* s1 = getCanvas()->createSurface( canvas::Rect(100, 100, 100, 100) );
	canvas::Surface* s2 = getCanvas()->createSurface( canvas::Rect(50, 50, 100, 100) );

	ASSERT_TRUE(s1 && s2);
	s1->autoFlush(true);
	s2->autoFlush(true);
	s1->setColor(canvas::Color(0, 0, 255));
	s2->setColor(canvas::Color(255, 0, 0));
	s1->fillRect(canvas::Rect(0,0,100,100));
	s2->fillRect(canvas::Rect(0,0,100,100));

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("two_surfaces_intersected_red_over_blue") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Three surfaces intersected with equal zindex
TEST_F( SurfaceZIndex, three_surfaces_intersected_with_same_zindex) {
	canvas::Surface* s1 = getCanvas()->createSurface( canvas::Rect(50, 50, 100, 100) );
	canvas::Surface* s2 = getCanvas()->createSurface( canvas::Rect(125, 75, 100, 100) );
	canvas::Surface* s3 = getCanvas()->createSurface( canvas::Rect(75, 125, 100, 100) );

	ASSERT_TRUE(s1 && s2 && s3);
	s1->autoFlush(true);
	s2->autoFlush(true);
	s3->autoFlush(true);
	s1->setColor(canvas::Color(0, 0, 255));
	s2->setColor(canvas::Color(255, 0, 0));
	s3->setColor(canvas::Color(0, 255, 0));
	s1->fillRect(canvas::Rect(0,0,100,100));
	s2->fillRect(canvas::Rect(0,0,100,100));
	s3->fillRect(canvas::Rect(0,0,100,100));

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("three_surfaces_intersected") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
	getCanvas()->destroy( s3 );
}

// Two surfaces intersected with different zIndex, both lower than 0.
TEST_F( SurfaceZIndex, two_surfaces_both_lt_0 ) {
	canvas::Surface* s1 = getCanvas()->createSurface( canvas::Rect(100, 100, 100, 100) );
	canvas::Surface* s2 = getCanvas()->createSurface( canvas::Rect(50, 50, 100, 100) );

	ASSERT_TRUE(s1 && s2);
	s1->autoFlush(true);
	s2->autoFlush(true);
	s1->setColor(canvas::Color(0, 0, 255));
	s2->setColor(canvas::Color(255, 0, 0));
	s1->fillRect(canvas::Rect(0,0,100,100));
	s2->fillRect(canvas::Rect(0,0,100,100));
	s1->setZIndex(-1);
	s2->setZIndex(-2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("two_surfaces_intersected_blue_over_red") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Two surfaces intersected with different zIndex. One lower than 0 and the other greater than 0.
TEST_F( SurfaceZIndex, two_surfaces_one_lt_0 ) {
	canvas::Surface* s1 = getCanvas()->createSurface( canvas::Rect(100, 100, 100, 100) );
	canvas::Surface* s2 = getCanvas()->createSurface( canvas::Rect(50, 50, 100, 100) );

	ASSERT_TRUE(s1 && s2);
	s1->autoFlush(true);
	s2->autoFlush(true);
	s1->setColor(canvas::Color(0, 0, 255));
	s2->setColor(canvas::Color(255, 0, 0));
	s1->fillRect(canvas::Rect(0,0,100,100));
	s2->fillRect(canvas::Rect(0,0,100,100));
	s1->setZIndex(-1);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("two_surfaces_intersected_red_over_blue") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Test markDirty after changing zindex
TEST_F( SurfaceZIndex, markDirty_zindex ) {
	canvas::Rect rect(0,0,200,200);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);
	getCanvas()->flush();

	s->setZIndex(2);

	std::vector<canvas::Rect> dirtyRegions = getCanvas()->dirtyRegions();

	ASSERT_FALSE( dirtyRegions.empty() );
	ASSERT_TRUE( dirtyRegions.size() == 1 );

	ASSERT_TRUE( dirtyRegions.at(0) == rect );

	getCanvas()->destroy( s );
}
