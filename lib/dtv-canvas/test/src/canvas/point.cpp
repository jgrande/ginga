#include <gtest/gtest.h>
#include "../../../src/point.h"

TEST( point, default_constructor ) {
	canvas::Point point;
	ASSERT_TRUE( point.x == 0 );
	ASSERT_TRUE( point.y == 0 );	
}

TEST( point, constructor_coord ) {
    canvas::Point point(5, 6);
    ASSERT_TRUE( point.x == 5 );
    ASSERT_TRUE( point.y == 6 );
}

// Two points not initialized have to be equals
TEST( point, default_equals ) {
	canvas::Point p1, p2;

	ASSERT_TRUE( p1 == p2 );
	ASSERT_FALSE( p1 != p2 );
}

// Two points initialized with same values have to be equals
TEST( point, initialized_equals ) {
	canvas::Point p1(2,3), p2(2,3);

	ASSERT_TRUE( p1 == p2 );
	ASSERT_FALSE( p1 != p2 );
}

// Two points initialized with differents values have not to be equals
TEST( point, not_equals ) {
	canvas::Point p1(2,0), p2(1,0);

	ASSERT_TRUE( p1 != p2 );
	ASSERT_FALSE( p1 == p2 );
}
