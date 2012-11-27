#include "size.h"
#include "rect.h"

namespace canvas {

Size::Size( void )
{
	w = 0;
	h = 0;
}

Size::Size( int paramW, int paramH )
{
	w = paramW;
	h = paramH;
}
	
Size::Size( const Rect &rect )
{
	w = rect.w;
	h = rect.h;
}

Size::~Size( void )
{
}

bool Size::operator==(const Size &size) const {
	return w == size.w && h == size.h;
}

bool Size::operator!=(const Size& size) const {
	return !((*this) == size);
}

}

