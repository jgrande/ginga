#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"

class SurfaceResize : public Surface {
protected:
	std::string getSubDirectory() const { return "Resize"; }
};

// Create surface from an image and then resize
TEST_F( SurfaceResize, basic_smaller_not_scaled ) {
	canvas::Surface* s = getCanvas()->createSurfaceFromPath(util::getImageName( "image.png"));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);
	canvas::Size newSize(100,100);
	ASSERT_TRUE( s->resize( newSize ) );
	ASSERT_TRUE( s->getSize() == newSize );
	ASSERT_TRUE( util::compareImages( getCanvas(), "nothing" ) );

	getCanvas()->destroy( s );
}

// Create surface from an image and then resize scaleing surface content
TEST_F( SurfaceResize, basic_smaller_scaled ) {
	canvas::Surface* s = getCanvas()->createSurfaceFromPath(util::getImageName( "image.png"));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);
	canvas::Size newSize(100,100);
	ASSERT_TRUE( s->resize( newSize, true ) );
	ASSERT_TRUE( s->getSize() == newSize );
	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "basic_smaller_scaled" ) ) );

	getCanvas()->destroy( s );
}

// Create surface from an image and then resize
TEST_F( SurfaceResize, basic_bigger_not_scaled ) {
	canvas::Surface* s = getCanvas()->createSurfaceFromPath(util::getImageName( "image.png"));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);
	canvas::Size newSize(600,500);
	ASSERT_TRUE( s->resize( newSize ) );
	ASSERT_TRUE( s->getSize() == newSize );
	ASSERT_TRUE( util::compareImages( getCanvas(), "nothing") );

	getCanvas()->destroy( s );
}

// Create surface from an image and then resize scaleing surface content
TEST_F( SurfaceResize, basic_bigger_scaled ) {
	canvas::Surface* s = getCanvas()->createSurfaceFromPath(util::getImageName( "image.png"));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);
	canvas::Size newSize(600,500);
	ASSERT_TRUE( s->resize( newSize, true ) );
	ASSERT_TRUE( s->getSize() == newSize );
	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "basic_bigger_scaled" ) ) );

	getCanvas()->destroy( s );
}

// Create surface from an image and then resize to 0
TEST_F( SurfaceResize, basic_0_0 ) {
	canvas::Surface* s = getCanvas()->createSurfaceFromPath(util::getImageName( "image.png"));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);
	canvas::Size oldSize = s->getSize();
	canvas::Size newSize(0,0);
	ASSERT_FALSE( s->resize( newSize ) );
	ASSERT_TRUE( s->getSize() == oldSize );

	getCanvas()->destroy( s );
}

// Create surface from an image and then resize to 0
TEST_F( SurfaceResize, basic_0_10 ) {
	canvas::Surface* s = getCanvas()->createSurfaceFromPath(util::getImageName( "image.png"));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);
	canvas::Size oldSize = s->getSize();
	canvas::Size newSize(0,10);
	ASSERT_FALSE( s->resize( newSize ) );
	ASSERT_TRUE( s->getSize() == oldSize );

	getCanvas()->destroy( s );
}

// Create surface from an image and then resize to 0
TEST_F( SurfaceResize, basic_10_0 ) {
	canvas::Surface* s = getCanvas()->createSurfaceFromPath(util::getImageName( "image.png"));

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);
	canvas::Size oldSize = s->getSize();
	canvas::Size newSize(10,0);
	ASSERT_FALSE( s->resize( newSize ) );
	ASSERT_TRUE( s->getSize() == oldSize );

	getCanvas()->destroy( s );
}