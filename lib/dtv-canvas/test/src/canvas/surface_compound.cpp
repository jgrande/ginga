#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"

class SurfaceCompound : public Surface {
protected:
    std::string getSubDirectory() const { return "Compound"; }
};

TEST_F( SurfaceCompound, figures ) {

	canvas::Surface* s = getCanvas()->createSurface( canvas::Rect( 0, 0, 720, 576 ) );

	ASSERT_TRUE( s != NULL );

	s->autoFlush( true );

	s->setColor( canvas::Color( 0, 255, 0, 224 ) );
	ASSERT_TRUE( s->fillRect(canvas::Rect(200, 200, 100, 100)) );

	s->setColor( canvas::Color( 255, 0, 0, 224 ) );
	ASSERT_TRUE( s->drawRect(canvas::Rect(210, 210, 100, 100)) );

	s->setColor( canvas::Color( 0, 0, 255, 224 ) );
	ASSERT_TRUE( s->fillRect( canvas::Rect(220, 220, 100, 100) ) );

	s->setColor( canvas::Color( 0, 255, 0, 224 ) );
	ASSERT_TRUE( s->fillRoundRect(canvas::Rect(230, 230, 100, 100), 10, 10) );

	s->setColor( canvas::Color( 255, 0, 0, 224 ) );
	ASSERT_TRUE( s->drawRoundRect(canvas::Rect(240, 240, 100, 100), 10, 10) );

	s->setColor( canvas::Color( 0, 0, 255, 224 ) );
	ASSERT_TRUE( s->fillRoundRect(canvas::Rect(250, 250, 100, 100), 10, 10) );

	s->setColor( canvas::Color( 0, 255, 0, 224 ) );
	ASSERT_TRUE( s->fillEllipse( canvas::Point(320, 320), 50, 50, 0, 0 ) );

	s->setColor( canvas::Color( 255, 0, 0, 224 ) );
	ASSERT_TRUE( s->drawEllipse( canvas::Point(330, 330), 50, 50, 0, 0 ) );

	s->setColor( canvas::Color( 0, 0, 255, 224 ) );
	ASSERT_TRUE( s->fillEllipse( canvas::Point(340, 340), 50, 50, 0, 0 ) );

	s->setColor( canvas::Color( 255, 255, 255, 224 ) );
	ASSERT_TRUE( s->drawLine( 200, 200, 340, 340 ) );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "figures" ) ) );

	getCanvas()->destroy( s );
}

TEST_F( SurfaceCompound, figures_in_surfaces ) {
	canvas::Rect r = canvas::Rect( 0, 0, 720, 576 );
	canvas::Point p = canvas::Point( 0, 0 );
	canvas::Surface* s = getCanvas()->createSurface( r );

	ASSERT_TRUE( s != NULL );

	s->autoFlush( true );

	canvas::Surface* s1 = getCanvas()->createSurface( r );
	s1->setColor( canvas::Color( 0, 255, 0, 224 ) );
	ASSERT_TRUE( s1->fillRect(canvas::Rect(200, 200, 100, 100)) );
	s->blit( p, s1, r );
	getCanvas()->destroy( s1 );

	canvas::Surface* s2 = getCanvas()->createSurface( r );
	s2->setColor( canvas::Color( 255, 0, 0, 224 ) );
	ASSERT_TRUE( s2->drawRect(canvas::Rect(210, 210, 100, 100)) );
	s->blit( p, s2, r );
	getCanvas()->destroy( s2 );

	canvas::Surface* s3 = getCanvas()->createSurface( r );
	s3->setColor( canvas::Color( 0, 0, 255, 224 ) );
	ASSERT_TRUE( s3->fillRect(canvas::Rect(220, 220, 100, 100)) );
	s->blit( p, s3, r );
	getCanvas()->destroy( s3 );

	canvas::Surface* s4 = getCanvas()->createSurface( r );
	s4->setColor( canvas::Color( 0, 255, 0, 224 ) );
	ASSERT_TRUE( s4->fillRoundRect(canvas::Rect(230, 230, 100, 100), 10, 10) );
	s->blit( p, s4, r );
	getCanvas()->destroy( s4 );

	canvas::Surface* s5 = getCanvas()->createSurface( r );
	s5->setColor( canvas::Color( 255, 0, 0, 224 ) );
	ASSERT_TRUE( s5->drawRoundRect(canvas::Rect(240, 240, 100, 100), 10, 10) );
	s->blit( p, s5, r );
	getCanvas()->destroy( s5 );

	canvas::Surface* s6 = getCanvas()->createSurface( r );
	s6->setColor( canvas::Color( 0, 0, 255, 224 ) );
	ASSERT_TRUE( s6->fillRoundRect(canvas::Rect(250, 250, 100, 100), 10, 10) );
	s->blit( p, s6, r );
	getCanvas()->destroy( s6 );

	canvas::Surface* s7 = getCanvas()->createSurface( r );
	s7->setColor( canvas::Color( 0, 255, 0, 224 ) );
	ASSERT_TRUE( s7->fillEllipse( canvas::Point(320, 320), 50, 50, 0, 0 ) );
	s->blit( p, s7, r );
	getCanvas()->destroy( s7 );

	canvas::Surface* s8 = getCanvas()->createSurface( r );
	s8->setColor( canvas::Color( 255, 0, 0, 224 ) );
	ASSERT_TRUE( s8->drawEllipse( canvas::Point(330, 330), 50, 50, 0, 0 ) );
	s->blit( p, s8, r );
	getCanvas()->destroy( s8 );

	canvas::Surface* s9 = getCanvas()->createSurface( r );
	s9->setColor( canvas::Color( 0, 0, 255, 224 ) );
	ASSERT_TRUE( s9->fillEllipse( canvas::Point(340, 340), 50, 50, 0, 0 ) );
	s->blit( p, s9, r );
	getCanvas()->destroy( s9 );

	canvas::Surface* s10 = getCanvas()->createSurface( r );
	s10->setColor( canvas::Color( 255, 255, 255, 224 ) );
	ASSERT_TRUE( s10->drawLine( 200, 200, 340, 340 ) );
	s->blit( p, s10, r );
	getCanvas()->destroy( s10 );
	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "figures_in_surfaces") ) );

	getCanvas()->destroy( s );
}

TEST_F( SurfaceCompound, image_text ) {
	canvas::Rect r = canvas::Rect( 0, 0, 720, 576 );

	canvas::Surface* s = getCanvas()->createSurface( r );
	ASSERT_TRUE( s != NULL );

	canvas::Surface* image = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	ASSERT_TRUE( image != NULL );

	s->autoFlush( true );
	ASSERT_TRUE( s->blit(canvas::Point(0, 0), image, canvas::Rect(0,0,500,375) ) );

	canvas::Surface* s1 = getCanvas()->createSurface( r );
	canvas::Font f;
	f.size( 100 );
	s1->setFont( f );
	s1->setColor( canvas::Color( 0, 255, 0, 224 ) );
	ASSERT_TRUE( s1->drawText(canvas::Point(300,300),"Text") );
	s->blit( canvas::Point(0,0), s1, r );
	getCanvas()->destroy( s1 );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "image_text" ) ) );

	getCanvas()->destroy( image );
	getCanvas()->destroy( s );
}

TEST_F( SurfaceCompound, figure_text ) {
	canvas::Rect r = canvas::Rect( 0, 0, 720, 576 );

	canvas::Surface* s = getCanvas()->createSurface( r );
	ASSERT_TRUE( s != NULL );

	canvas::Surface* image = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	ASSERT_TRUE( image != NULL );

	s->autoFlush( true );

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
		s->setColor( canvas::Color( (util::BYTE)(j*20), (util::BYTE)(0), (util::BYTE)(i*20), (util::BYTE)(220+(j*i)) ) );
		ASSERT_TRUE( s->fillRect(canvas::Rect(i*90, j*96, 90, 96)) );
		}
	}

	canvas::Surface* s1 = getCanvas()->createSurface( r );
	canvas::Font f;
	f.size( 100 );
	s1->setFont( f );
	s1->setColor( canvas::Color( 0, 255, 0, 224 ) );
	ASSERT_TRUE( s1->drawText(canvas::Point(300,300),"Text") );
	s->blit( canvas::Point(0,0), s1, r );
	getCanvas()->destroy( s1 );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "figure_text" ) ) );

	getCanvas()->destroy( image );
	getCanvas()->destroy( s );
}

TEST_F( SurfaceCompound, text_text ) {
	canvas::Rect r = canvas::Rect( 0, 0, 720, 576 );

	canvas::Font f;
	f.size( 100 );

	canvas::Surface* s = getCanvas()->createSurface( r );
	ASSERT_TRUE( s != NULL );
	s->autoFlush( true );
	s->setFont( f );
	s->setColor( canvas::Color( 255, 0, 0, 224 ) );
	ASSERT_TRUE( s->drawText(canvas::Point(250,250),"Text") );

	canvas::Surface* s1 = getCanvas()->createSurface( r );
	s1->setFont( f );
	s1->setColor( canvas::Color( 0, 255, 0, 224 ) );
	ASSERT_TRUE( s1->drawText(canvas::Point(300,300),"Text") );
	s->blit( canvas::Point(0,0), s1, r );
	getCanvas()->destroy( s1 );

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "text_text" ) ) );

	getCanvas()->destroy( s );
}
