#include <gtest/gtest.h>
#include "../../../src/color.h"

TEST( color, default_constructor ) {
    canvas::Color color;
    ASSERT_TRUE( color.r == 0 );
    ASSERT_TRUE( color.g == 0 );
    ASSERT_TRUE( color.b == 0 );
    ASSERT_TRUE( color.alpha == 0 );
}

TEST( color, constructor_with_alpha ) {
    canvas::Color color(25, 54, 46, 128);
    ASSERT_TRUE( color.r == 25 );
    ASSERT_TRUE( color.g == 54 );
    ASSERT_TRUE( color.b == 46 );
    ASSERT_TRUE( color.alpha == 128 );
}

TEST( color, constructor_without_alpha ) {
    canvas::Color color(32, 43, 78);
    ASSERT_TRUE( color.r == 32 );
    ASSERT_TRUE( color.g == 43 );
    ASSERT_TRUE( color.b == 78 );
    ASSERT_TRUE( color.alpha == 255 );
}

TEST( color, equals_no_threshold ) {
    canvas::Color color1(0, 0, 0);
    canvas::Color color2(0, 0, 0);
    ASSERT_TRUE( color1.equals( color2, 0 ) );
    ASSERT_TRUE( color2.equals( color1, 0 ) );
}

TEST( color, not_equals_no_threshold ) {
    canvas::Color color1(0, 0, 0);
    canvas::Color color2(1, 0, 0);
    ASSERT_FALSE( color1.equals( color2, 0 ) );
    ASSERT_FALSE( color2.equals( color1, 0 ) );
}

TEST( color, equals_with_threshold_1 ) {
    canvas::Color color1(0, 0, 0);
    canvas::Color color2(1, 0, 0);
    ASSERT_TRUE( color1.equals( color2, 1 ) );
    ASSERT_TRUE( color2.equals( color1, 1 ) );
}

TEST( color, not_equals_with_threshold_1 ) {
    canvas::Color color1(0, 0, 0);
    canvas::Color color2(1, 1, 0);
    ASSERT_FALSE( color1.equals( color2, 1 ) );
    ASSERT_FALSE( color2.equals( color1, 1 ) );
}

TEST( color, equals_with_threshold_2 ) {
    canvas::Color color1(0, 0, 0);
    canvas::Color color2(2, 0, 0);
    ASSERT_TRUE( color1.equals( color2, 2 ) );
    ASSERT_TRUE( color2.equals( color1, 2 ) );
}

TEST( color, not_equals_with_threshold_2 ) {
    canvas::Color color1(0, 0, 0);
    canvas::Color color2(2, 1, 0);
    ASSERT_FALSE( color1.equals( color2, 2 ) );
    ASSERT_FALSE( color2.equals( color1, 2 ) );
}

TEST( color, equals_with_threshold_3 ) {
    canvas::Color color1(0, 0, 0);
    canvas::Color color2(2, 1, 0);
    ASSERT_TRUE( color1.equals( color2, 3 ) );
    ASSERT_TRUE( color2.equals( color1, 3 ) );
}

TEST( color, not_equals_with_threshold_3 ) {
    canvas::Color color1(0, 0, 0);
    canvas::Color color2(2, 1, 1);
    ASSERT_FALSE( color1.equals( color2, 3 ) );
    ASSERT_FALSE( color2.equals( color1, 3 ) );
}





