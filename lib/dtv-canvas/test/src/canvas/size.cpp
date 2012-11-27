#include <gtest/gtest.h>
#include "../../../src/size.h"

TEST( size, default_constructor ) {
    canvas::Size size;
    ASSERT_TRUE( size.w == 0 );
    ASSERT_TRUE( size.h == 0 );
}

TEST( size, constructor_dimension ) {
    canvas::Size size(7, 9);
    ASSERT_TRUE( size.w == 7 );
    ASSERT_TRUE( size.h == 9 );
}


// Two points not initialized have to be equals
TEST( size, equal_compare_default) {
    canvas::Size size, size2;
    ASSERT_TRUE(size == size2);
    ASSERT_FALSE(size != size2);
}

// Two points initialized with same values have to be equals
TEST( size, equal_compare_with_value) {
    canvas::Size size(5,6), size2(5,6);
    ASSERT_TRUE(size == size2);
    ASSERT_FALSE(size != size2);
}

//Two points initialized with differents value have not to be equals
TEST( size, not_equal_compare){
    canvas::Size size(100,200), size2(120,200);
    ASSERT_TRUE(size != size2);
    ASSERT_FALSE(size == size2);
}
