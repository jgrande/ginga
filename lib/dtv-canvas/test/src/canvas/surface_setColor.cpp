#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"

class SurfaceSetColor : public Surface {
protected:
    std::string getSubDirectory() const { return "SetColor"; }
};

// Set color to red
TEST_F( SurfaceSetColor, red_opaque ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0, 0, 200, 200));
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(100, 100, 200, 200));

	ASSERT_TRUE( s1 != NULL );
	s1->autoFlush(true);
	s1->setColor(canvas::Color(255, 0, 0));
	s1->setZIndex(2);
	ASSERT_TRUE( s1->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( s2 != NULL );
	s2->autoFlush(true);
	s2->setColor(canvas::Color(255, 255, 0, 255));
	s2->setZIndex(1);
	ASSERT_TRUE( s2->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("red_opaque") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Set color to red with alpha = 0
TEST_F( SurfaceSetColor, red_alpha_0 ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0, 0, 200, 200));
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(100, 100, 200, 200));

	ASSERT_TRUE( s1 != NULL );
	s1->autoFlush(true);
	s1->setColor(canvas::Color(255, 0, 0, 0));
	s2->setZIndex(2);
	ASSERT_TRUE( s1->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( s2 != NULL );
	s2->autoFlush(true);
	s2->setColor(canvas::Color(255, 255, 0, 255));
	s2->setZIndex(1);
	ASSERT_TRUE( s2->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("red_with_alpha_0") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Set color to red with alpha = 127
TEST_F( SurfaceSetColor, red_alpha_127 ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0, 0, 200, 200));
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(100, 100, 200, 200));

	ASSERT_TRUE( s1 != NULL );
	s1->autoFlush(true);
	s1->setColor(canvas::Color(255, 0, 0, 127));
	s1->setZIndex(2);
	ASSERT_TRUE( s1->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( s2 != NULL );
	s2->autoFlush(true);
	s2->setColor(canvas::Color(255, 255, 0, 255));
	s2->setZIndex(1);
	ASSERT_TRUE( s2->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("red_with_alpha_127") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Set color to green
TEST_F( SurfaceSetColor, green_opaque ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0, 0, 200, 200));
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(100, 100, 200, 200));

	ASSERT_TRUE( s1 != NULL );
	s1->autoFlush(true);
	s1->setColor(canvas::Color(0, 255, 0));
	s1->setZIndex(2);
	ASSERT_TRUE( s1->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( s2 != NULL );
	s2->autoFlush(true);
	s2->setColor(canvas::Color(255, 255, 0, 255));
	s2->setZIndex(1);
	ASSERT_TRUE( s2->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("green_opaque") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Set color to green with alpha = 0
TEST_F( SurfaceSetColor, green_alpha_0 ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0, 0, 200, 200));
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(100, 100, 200, 200));

	ASSERT_TRUE( s1 != NULL );
	s1->autoFlush(true);
	s1->setColor(canvas::Color(0, 255, 0, 0));
	s2->setZIndex(2);
	ASSERT_TRUE( s1->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( s2 != NULL );
	s2->autoFlush(true);
	s2->setColor(canvas::Color(255, 255, 0, 255));
	s2->setZIndex(1);
	ASSERT_TRUE( s2->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("green_with_alpha_0") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Set color to green with alpha = 127
TEST_F( SurfaceSetColor, green_alpha_127 ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0, 0, 200, 200));
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(100, 100, 200, 200));

	ASSERT_TRUE( s1 != NULL );
	s1->autoFlush(true);
	s1->setColor(canvas::Color(0, 255, 0, 127));
	s1->setZIndex(2);
	ASSERT_TRUE( s1->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( s2 != NULL );
	s2->autoFlush(true);
	s2->setColor(canvas::Color(255, 255, 0, 255));
	s2->setZIndex(1);
	ASSERT_TRUE( s2->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("green_with_alpha_127") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Set color to blue
TEST_F( SurfaceSetColor, blue_opaque ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0, 0, 200, 200));
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(100, 100, 200, 200));

	ASSERT_TRUE( s1 != NULL );
	s1->autoFlush(true);
	s1->setColor(canvas::Color(0, 0, 255));
	s1->setZIndex(2);
	ASSERT_TRUE( s1->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( s2 != NULL );
	s2->autoFlush(true);
	s2->setColor(canvas::Color(255, 255, 0, 255));
	s2->setZIndex(1);
	ASSERT_TRUE( s2->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("blue_opaque") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Set color to blue with alpha = 0
TEST_F( SurfaceSetColor, blue_alpha_0 ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0, 0, 200, 200));
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(100, 100, 200, 200));

	ASSERT_TRUE( s1 != NULL );
	s1->autoFlush(true);
	s1->setColor(canvas::Color(0, 0, 255, 0));
	s2->setZIndex(2);
	ASSERT_TRUE( s1->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( s2 != NULL );
	s2->autoFlush(true);
	s2->setColor(canvas::Color(255, 255, 0, 255));
	s2->setZIndex(1);
	ASSERT_TRUE( s2->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("blue_with_alpha_0") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Set color to blue with alpha = 127
TEST_F( SurfaceSetColor, blue_alpha_127 ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0, 0, 200, 200));
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(100, 100, 200, 200));

	ASSERT_TRUE( s1 != NULL );
	s1->autoFlush(true);
	s1->setColor(canvas::Color(0, 0, 255, 127));
	s1->setZIndex(2);
	ASSERT_TRUE( s1->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( s2 != NULL );
	s2->autoFlush(true);
	s2->setColor(canvas::Color(255, 255, 0, 255));
	s2->setZIndex(1);
	ASSERT_TRUE( s2->fillRect(canvas::Rect(0,0,200,200)) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath("blue_with_alpha_127") ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}
