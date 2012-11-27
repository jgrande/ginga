#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"

// Test para el constructor de image
TEST_F( Surface, image_constructor ) {
	canvas::Surface* i  = getCanvas()->createSurfaceFromPath(util::getImageName("image.png") );
	canvas::Size s1,s2(500,375);

	ASSERT_TRUE( i != NULL );
	s1 = i->getSize();

	ASSERT_TRUE( s1 == s2 );

	getCanvas()->destroy( i );
}

// Test para el constructor de image desde una imagen inexistente
TEST_F( Surface, image_constructor_from_inexistent_image ) {
	canvas::Surface* i  = getCanvas()->createSurfaceFromPath(util::getImageName("nn.png") );

	ASSERT_FALSE( i );
}

TEST_F( Surface, image_getSize) {
	canvas::Surface* i1 = getCanvas()->createSurfaceFromPath(util::getImageName("image.png"));
	canvas::Surface* i2 = getCanvas()->createSurfaceFromPath(util::getImageName("red.jpg"));

	ASSERT_TRUE( i1 && i2 );

	int w = i1->getSize().w;
	int h = i1->getSize().h;

	ASSERT_TRUE( w == 500 );
	ASSERT_TRUE( h == 375 );

	w = i2->getSize().w;
	h = i2->getSize().h;

	ASSERT_TRUE( w == 100 );
	ASSERT_TRUE( h == 100 );

	getCanvas()->destroy(i1);
	getCanvas()->destroy(i2);
}

TEST_F( Surface, image_getPixelColor ) {
	canvas::Surface* i1 = getCanvas()->createSurfaceFromPath(util::getImageName("image.png"));
	canvas::Surface* i2 = getCanvas()->createSurfaceFromPath(util::getImageName("red.jpg"));

	ASSERT_TRUE( i1 && i2 );

	canvas::Point p1(10,10),
			      p2(373,364),
				  p3(0,0);

	canvas::Color color(0,0,0),
				  c1(138,135,188),
				  c2(98,92,44),
				  c3(254,0,0);

	ASSERT_TRUE( i1->getPixelColor(p1, color) );
	ASSERT_TRUE( color.equals(c1, 0) );

	ASSERT_TRUE( i1->getPixelColor(p2, color) );
	ASSERT_TRUE( color.equals(c2, 0) );

	ASSERT_TRUE( i2->getPixelColor(p3, color) );
	ASSERT_TRUE( color.equals(c3, 0) );

	getCanvas()->destroy(i1);
	getCanvas()->destroy(i2);
}
