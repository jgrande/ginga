#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"

class SurfaceCompositionMode : public Surface {
protected:
    std::string getSubDirectory() const { return "CompositionMode"; }
};

TEST_F( SurfaceCompositionMode, source_over_basic ) {
	canvas::Rect rect(0,0,300,300);
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName("image.png") );
	canvas::Surface* s2 = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );
	s1->autoFlush(true);

	s2->setColor(canvas::Color(255,0,0,128));
	ASSERT_TRUE( s2->fillRect(canvas::Rect(0,0,300,300)) );

	ASSERT_TRUE( s1->blit( canvas::Point(0,0), s2 ) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "source_over_basic" )) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

TEST_F( SurfaceCompositionMode, source_basic ) {
	canvas::Rect rect(0,0,300,300);
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName("image.png") );
	canvas::Surface* s2 = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );
	s1->autoFlush(true);

	s2->setColor(canvas::Color(255,0,0,128));
	ASSERT_TRUE( s2->fillRect(canvas::Rect(0,0,300,300)) );

	s1->setCompositionMode(canvas::composition::source);
	ASSERT_TRUE( s1->blit( canvas::Point(0,0), s2 ) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "source_basic" )) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

TEST_F( SurfaceCompositionMode, source_full_transparent ) {
	canvas::Rect rect(0,0,300,300);
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName("image.png") );
	canvas::Surface* s2 = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );
	s1->autoFlush(true);

	s2->setColor(canvas::Color(0,0,0,0));
	ASSERT_TRUE( s2->fillRect(canvas::Rect(0,0,300,300)) );

	s1->setCompositionMode(canvas::composition::source);
	ASSERT_TRUE( s1->blit( canvas::Point(0,0), s2 ) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "source_300x300_fullTransparent" )) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

TEST_F( SurfaceCompositionMode, mixed ) {
	canvas::Surface* s1 = getCanvas()->createSurfaceFromPath( util::getImageName("image.png") );
	canvas::Surface* s2 = getCanvas()->createSurface( canvas::Rect(0,0,200,200) );
	canvas::Surface* s3 = getCanvas()->createSurface( canvas::Rect(0,0,100,100) );
	
	ASSERT_TRUE( s1 != NULL );
	ASSERT_TRUE( s2 != NULL );
	ASSERT_TRUE( s3 != NULL );
	s1->autoFlush(true);

	s2->setColor(canvas::Color(255,0,0,128));
	ASSERT_TRUE( s2->fillRect(canvas::Rect(0,0,200,200)) );

	s3->setColor(canvas::Color(0,255,0,128));
	ASSERT_TRUE( s3->fillRect(canvas::Rect(0,0,100,100)) );

	s1->setCompositionMode(canvas::composition::source_over);
	ASSERT_TRUE( s1->blit( canvas::Point(0,0), s2 ) );

	s1->setCompositionMode(canvas::composition::source);
	ASSERT_TRUE( s1->blit( canvas::Point(0,0), s3 ) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "mixed" )) );

	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
	getCanvas()->destroy( s3 );
}

