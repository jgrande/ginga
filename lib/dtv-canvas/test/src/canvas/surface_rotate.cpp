#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"

class SurfaceRotate : public Surface {
protected:
    std::string getSubDirectory() const { return "Rotate"; }
};

// Surface rotated 0 degrees
TEST_F( SurfaceRotate, rotated_0_degrees ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	ASSERT_TRUE( s1 != NULL );
	s1->setLocation(canvas::Point(100,100));

	canvas::Surface* s2 = s1->rotate(0);
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "rotated_360_degrees" ) ) );

	canvas::Size size = s2->getSize();
	ASSERT_TRUE( size == canvas::Size(500,375) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface rotated 90 degrees
TEST_F( SurfaceRotate, rotated_90_degrees ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	ASSERT_TRUE( s1 != NULL );
	s1->setLocation(canvas::Point(100,100));

	canvas::Surface* s2 = s1->rotate(90);
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "rotated_90_degrees" ) ) );

	canvas::Size size = s2->getSize();
	ASSERT_TRUE( size == canvas::Size(375,500) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface rotated 180 degrees
TEST_F( SurfaceRotate, rotated_180_degrees ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	ASSERT_TRUE( s1 != NULL );
	s1->setLocation(canvas::Point(100,100));

	canvas::Surface* s2 = s1->rotate(180);
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "rotated_180_degrees" ) ) );

	canvas::Size size = s2->getSize();
	ASSERT_TRUE( size == canvas::Size(500,375) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface rotated 270 degrees
TEST_F( SurfaceRotate, rotated_270_degrees ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	ASSERT_TRUE( s1 != NULL );
	s1->setLocation(canvas::Point(100,100));

	canvas::Surface* s2 = s1->rotate(270);
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "rotated_270_degrees" ) ) );

	canvas::Size size = s2->getSize();
	ASSERT_TRUE( size == canvas::Size(375,500) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface rotated 360 degrees
TEST_F( SurfaceRotate, rotated_360_degrees ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	ASSERT_TRUE( s1 != NULL );
	s1->setLocation(canvas::Point(100,100));

	canvas::Surface* s2 = s1->rotate(360);
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "rotated_360_degrees" ) ) );

	canvas::Size size = s2->getSize();
	ASSERT_TRUE( size == canvas::Size(500,375) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface rotated 90 degrees negative
TEST_F( SurfaceRotate, rotated_90_degrees_negative ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	ASSERT_TRUE( s1 != NULL );
	s1->setLocation(canvas::Point(100,100));

	canvas::Surface* s2 = s1->rotate(-90);
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "rotated_270_degrees" ) ) );

	canvas::Size size = s2->getSize();
	ASSERT_TRUE( size == canvas::Size(375,500) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface rotated 180 degrees negative
TEST_F( SurfaceRotate, rotated_180_degrees_negative ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	ASSERT_TRUE( s1 != NULL );
	s1->setLocation(canvas::Point(100,100));

	canvas::Surface* s2 = s1->rotate(-180);
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "rotated_180_degrees" ) ) );

	canvas::Size size = s2->getSize();
	ASSERT_TRUE( size == canvas::Size(500,375) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface rotated 270 degrees negative
TEST_F( SurfaceRotate, rotated_270_degrees_negative ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	ASSERT_TRUE( s1 != NULL );
	s1->setLocation(canvas::Point(100,100));

	canvas::Surface* s2 = s1->rotate(-270);
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "rotated_90_degrees" ) ) );

	canvas::Size size = s2->getSize();
	ASSERT_TRUE( size == canvas::Size(375,500) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface rotated 360 degrees negative
TEST_F( SurfaceRotate, rotated_360_degrees_negative ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	ASSERT_TRUE( s1 != NULL );
	s1->setLocation(canvas::Point(100,100));

	canvas::Surface* s2 = s1->rotate(-360);
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "rotated_360_degrees" ) ) );

	canvas::Size size = s2->getSize();
	ASSERT_TRUE( size == canvas::Size(500,375) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface rotated not multiple of 90
TEST_F( SurfaceRotate, rotated_not_multiple_of_90 ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	ASSERT_TRUE( s1 != NULL );
	s1->setLocation(canvas::Point(100,100));

	canvas::Surface* s2 = s1->rotate(45);
	ASSERT_TRUE( s2 == NULL );

	getCanvas()->destroy( s1 );
}

// Surface rotated not multiple of 90 negative
TEST_F( SurfaceRotate, rotated_not_multiple_of_90_negative ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	ASSERT_TRUE( s1 != NULL );
	s1->setLocation(canvas::Point(100,100));

	canvas::Surface* s2 = s1->rotate(-45);
	ASSERT_TRUE( s2 == NULL );

	getCanvas()->destroy( s1 );
}
