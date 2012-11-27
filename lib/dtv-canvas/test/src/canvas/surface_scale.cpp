#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"

class SurfaceScale : public Surface {
protected:
    std::string getSubDirectory() const { return "Scale"; }
};

// Surface scaled double
TEST_F( SurfaceScale, factor_double ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,720,576);
	canvas::Rect r2(0,0,360,288);
	ASSERT_TRUE( s2->scale(r1, s1, r2) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_double" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled half
TEST_F( SurfaceScale, factor_half ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r(0,0,250,188);
	ASSERT_TRUE( s2->scale(r, s1) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_half" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled half
TEST_F( SurfaceScale, factor_half_2 ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,100,100);
	canvas::Rect r2(100,100,200,200);
	ASSERT_TRUE( s2->scale(r1, s1, r2) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_half_2" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled equal
TEST_F( SurfaceScale, factor_equal ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r(0,0,500,375);
	ASSERT_TRUE( s2->scale(r, s1) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_equal" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled height half
TEST_F( SurfaceScale, factor_height_half ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r(0,0,500,188);
	ASSERT_TRUE( s2->scale(r, s1) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_height_half" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled width half
TEST_F( SurfaceScale, factor_width_half ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	ASSERT_TRUE( s2->scale( canvas::Rect(0,0,250,375), s1 ) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_width_half" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled height double
TEST_F( SurfaceScale, factor_height_double ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	ASSERT_TRUE( s2->scale( canvas::Rect(0,0,500,576), s1, canvas::Rect(0,0,500,288) ) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_height_double" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled width double
TEST_F( SurfaceScale, factor_width_double ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	ASSERT_TRUE( s2->scale( canvas::Rect(0,0,720,375), s1, canvas::Rect(0,0,360,375) ) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_width_double" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled double negative
TEST_F( SurfaceScale, factor_double_negative ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,720,576);
	canvas::Rect r2(0,0,360,288);
	ASSERT_TRUE( s2->scale(r1, s1, r2, true, true) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_double_negative" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled height negative
TEST_F( SurfaceScale, factor_half_negative ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,250,188);
	canvas::Rect r2(0,0,500,375);
	ASSERT_TRUE( s2->scale(r1, s1, r2, true, true) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_half_negative" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled equal negative
TEST_F( SurfaceScale, factor_equal_negative ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,500,375);
	canvas::Rect r2(0,0,500,375);
	ASSERT_TRUE( s2->scale(r1, s1, r2, true, true) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_equal_negative" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}


// Surface scaled height half negative
TEST_F( SurfaceScale, factor_negative_height_half ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,500,188);
	canvas::Rect r2(0,0,500,375);
	ASSERT_TRUE( s2->scale(r1, s1, r2, true, true) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_negative_height_half" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled width half negative
TEST_F( SurfaceScale, factor_negative_width_half ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,250,375);
	canvas::Rect r2(0,0,500,375);
	ASSERT_TRUE( s2->scale(r1, s1, r2, true, true) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_negative_width_half" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}


// Surface scaled height double negative
TEST_F( SurfaceScale, factor_negative_height_double ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,500,576);
	canvas::Rect r2(0,0,500,288);
	ASSERT_TRUE( s2->scale(r1, s1, r2, true, true) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_negative_height_double" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}


// Surface scaled width double negative
TEST_F( SurfaceScale, factor_negative_width_double ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,720,375);
	canvas::Rect r2(0,0,360,375);
	ASSERT_TRUE( s2->scale(r1, s1, r2, true, true) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_negative_width_double" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled double height negative
TEST_F( SurfaceScale, factor_double_height_negative ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,720,576);
	canvas::Rect r2(0,0,360,288);
	ASSERT_TRUE( s2->scale(r1, s1, r2, false, true) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_double_height_negative" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}


// Surface scaled double width negative
TEST_F( SurfaceScale, factor_double_width_negative ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,720,576);
	canvas::Rect r2(0,0,360,288);
	ASSERT_TRUE( s2->scale(r1, s1, r2, true, false) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_double_width_negative" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled half height negative
TEST_F( SurfaceScale, factor_half_hegiht_negative ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,250,188);
	canvas::Rect r2(0,0,500,375);
	ASSERT_TRUE( s2->scale(r1, s1, r2, false, true) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_half_hegiht_negative" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled half width negative
TEST_F( SurfaceScale, factor_half_width_negative ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,250,188);
	canvas::Rect r2(0,0,500,375);
	ASSERT_TRUE( s2->scale(r1, s1, r2, true, false) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_half_width_negative" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}


// Surface height mirrored
TEST_F( SurfaceScale, factor_equal_hegiht_negative ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,500,375);
	canvas::Rect r2(0,0,500,375);
	ASSERT_TRUE( s2->scale(r1, s1, r2, false, true) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_equal_hegiht_negative" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface width mirrored
TEST_F( SurfaceScale, factor_equal_width_negative ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,500,375);
	canvas::Rect r2(0,0,500,375);
	ASSERT_TRUE( s2->scale(r1, s1, r2, true, false) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "factor_equal_width_negative" ) ) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled width 0 and height 0 
TEST_F( SurfaceScale, factor_zero ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,0,0);
	canvas::Rect r2(0,0,500,375);
	ASSERT_FALSE( s2->scale(r1, s1, r2) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled width 0
TEST_F( SurfaceScale, factor_width_zero ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,0,375);
	canvas::Rect r2(0,0,500,375);
	ASSERT_FALSE( s2->scale(r1, s1, r2) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

// Surface scaled height 0
TEST_F( SurfaceScale, factor_height_zero ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );

	s2->autoFlush(true);
	canvas::Rect r1(0,0,500,0);
	canvas::Rect r2(0,0,500,375);
	ASSERT_FALSE( s2->scale(r1, s1, r2) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}
