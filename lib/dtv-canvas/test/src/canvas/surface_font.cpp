#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"
#include <algorithm>

// Tests getFont with default font
TEST_F( Surface, font_default ){
	canvas::Rect rect(0, 0, 720, 576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );

	std::vector<std::string> familiesGet = s->getFont().families();
	ASSERT_TRUE( std::find(familiesGet.begin(), familiesGet.end(), "Tiresias") != familiesGet.end() );
	getCanvas()->destroy( s );
}

// Tests getFont after changing the setted font
TEST_F( Surface, font_getFont_after_changing_font ){
	canvas::Rect rect(0, 0, 720, 576);
	canvas::Surface* s = getCanvas()->createSurface( rect );
	canvas::Font f;

	ASSERT_TRUE( s != NULL );

	std::vector<std::string> families;
	families.push_back("DejaVuSans");
	f.families(families);

	std::vector<std::string> familiesGet1 = s->getFont().families();
	ASSERT_TRUE( std::find(familiesGet1.begin(), familiesGet1.end(), "Tiresias") != familiesGet1.end() );

	s->setFont(f);

	std::vector<std::string> familiesGet2 = s->getFont().families();
	ASSERT_TRUE( std::find(familiesGet2.begin(), familiesGet2.end(), "DejaVuSans") != familiesGet2.end() );

	getCanvas()->destroy( s );
}
