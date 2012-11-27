#include "point.h"
#include "rect.h"

namespace canvas  {

Point::Point( void )
{
	x = 0;
	y = 0;
}

Point::Point( int paramX, int paramY )
{
	x = paramX;
	y = paramY;
}

Point::Point( const Rect &rect )
{
	x = rect.x;
	y = rect.y;
}

Point::~Point( void )
{
}

bool Point::operator==(const Point& point) const {
	return x==point.x && y==point.y;
}

bool Point::operator!=(const Point& point) const {
	return !((*this)==point);
}

}
