#include "color.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

namespace canvas {
	
namespace color {

typedef struct {
	const char *name;
	util::BYTE r;
	util::BYTE g;
	util::BYTE b;
	util::BYTE a;	
} ColorType;

#define DO_ENUM_COLOR( name, r, g, b, a ) { #name, r, g, b, a },
static const ColorType colors[] = {
	COLOR_LIST(DO_ENUM_COLOR)
	{ NULL, 0, 0, 0, 0 }
};
#undef DO_ENUM_COLOR

bool get( const char *textColor, Color &color ) {
	int i=0;
	while (colors[i].name && strcmp(colors[i].name,textColor) != 0) {
		i++;
	}
	if (i < LAST_COLOR) {
		color = Color( colors[i].r, colors[i].g, colors[i].b, colors[i].a );
		return true;
	}
	return false;
}

}

Color::Color( void )
{
	r = 0;
	g = 0;
	b = 0;
	alpha = 0;
}

Color::Color( util::BYTE paramR, util::BYTE paramG, util::BYTE paramB, util::BYTE paramAlpha )
{
	r = paramR;
	g = paramG;
	b = paramB;
	alpha = paramAlpha;
}

Color::Color( util::BYTE paramR, util::BYTE paramG, util::BYTE paramB )
{
	r = paramR;
	g = paramG;
	b = paramB;
	alpha = 255;
}

Color::~Color( void )
{
}

bool Color::operator==( const Color &color ) const {
	return r == color.r && g == color.g && b == color.b;
}

bool Color::operator!=( const Color &color ) const {
	return !((*this) == color);
}

bool Color::equals( const Color &color, int threshold ) const {
	int error = abs(color.r - r) + abs( color.g - g ) + abs( color.b - b ) + abs( color.alpha - alpha );
	return error <= threshold;
}

}
