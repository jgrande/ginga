#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class SurfaceCompositionModeOpacity : public Surface {
protected:
    std::string getSubDirectory() const { return "CompositionMode"; }
    std::string getInternalDirectory() const { return "Opacity"; }

    std::string getExpectedPath( const std::string &fileName ) const {
        fs::path root( Surface::getExpectedPath( getInternalDirectory() ) );
        root /= fileName;
        return root.string();
    }
};

void draw_compositionMode1_opacity(canvas::Surface* s1,canvas::Canvas* c, canvas::Surface* s2) {
	canvas::Surface* i = c->createSurfaceFromPath(util::getImageName("image.png"));
	s1->autoFlush(true);
	s2->autoFlush(true);
	s2->blit(canvas::Point(0,0),i,canvas::Rect(0,0,500,375));
	s2->setOpacity(100);

	s1->setColor(canvas::Color(255,0,0));
	s1->fillRect(canvas::Rect(200,137,150,150));

	canvas::Point target(300,220);
	canvas::Rect source(0,0,250,185);
	s1->blit( target, s2, source );

	c->destroy(i);
}
 
//*Create a surface  with default compositionMode and then call compositionMode1_opacity function*/
TEST_F( SurfaceCompositionModeOpacity, default ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurface(canvas::Rect(0,0,500,375));
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "source_over" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with source_over mode and then call compositionMode1_opacity function*/
TEST_F( SurfaceCompositionModeOpacity, source_over ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::source_over);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "source_over" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with destination_over mode and then call compositionMode1_opacity function*/
TEST_F( SurfaceCompositionModeOpacity, DISABLED_destination_over ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::destination_over);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "destination_over" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with clear mode and then call compositionMode1_opacity function*/
TEST_F( SurfaceCompositionModeOpacity, DISABLED_clear ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::clear);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "clear" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with source mode and then call compositionMode1_opacity function*/
TEST_F( SurfaceCompositionModeOpacity, DISABLED_source ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::source);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "source" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with source in mode and then call compositionMode1_opacity function*/
TEST_F( SurfaceCompositionModeOpacity, DISABLED_source_in ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::source_in);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "source_in" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with destination mode and then call compositionMode1_opacity function*/
TEST_F( SurfaceCompositionModeOpacity, DISABLED_destination ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::destination);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "destination" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with destination_in mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_destination_in ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::destination_in);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "destination_in" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with source_out mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_source_out ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::source_out);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "source_out" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with destination_out mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_destination_out ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::destination_out);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "destination_out" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with source_atop mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_source_atop ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::source_atop);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "source_atop" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with destination_atop mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_destination_atop ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::destination_atop);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "destination_atop" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}


/*Create a surface  with x_or mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_x_or ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::x_or);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "x_or" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}


/*Create a surface  with plus mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_plus ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::plus);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "plus" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with multiply mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_multiply ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::multiply);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "multiply" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with screen mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_screen ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::screen);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "screen" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with overlay mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_overlay ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::overlay);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "overlay" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with darken mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_darken ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::darken);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "darken" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with lighten mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_lighten ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::lighten);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "lighten" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with color_dodge mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_color_dodge ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::color_dodge);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "color_dodge" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with color_burn mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_color_burn ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::color_burn);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "color_burn" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with hard_light mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_hard_light ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::hard_light);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "hard_light" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with soft_light mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_soft_light ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::soft_light);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "soft_light" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with difference mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_difference ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::difference);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "difference" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}

/*Create a surface  with exclusion mode and then call compositionMode1_opacity function*/ 
TEST_F( SurfaceCompositionModeOpacity, DISABLED_exclusion ) {
	canvas::Surface* s1 = getCanvas()->createSurface(canvas::Rect(0,0,720,576));
	canvas::Surface* s2 = getCanvas()->createSurfaceFromPath( util::getImageName( "image.png" ) );
	s1->setCompositionMode(canvas::composition::exclusion);
	draw_compositionMode1_opacity(s1,getCanvas(),s2);

	ASSERT_TRUE( util::compareImages( getCanvas(), getExpectedPath( "exclusion" ) ) );
	getCanvas()->destroy( s1 );
	getCanvas()->destroy( s2 );
}
