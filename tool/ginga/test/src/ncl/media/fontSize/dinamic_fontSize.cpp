#include "../../../ginga.h"

namespace ginga {

TEST_F( Ginga, media_dinamic_fontSize1 ) {
	ASSERT_TRUE( play("media/fontSize/dinamic_fontSize1.ncl") );
	ASSERT_TRUE( compareTo("standardText_size12") );
	ASSERT_TRUE( pressKey( ::util::key::red ));
	ASSERT_TRUE( compareTo("standardText_size12") );
}
TEST_F( Ginga, media_dinamic_fontSize2 ) {
	ASSERT_TRUE( play("media/fontSize/dinamic_fontSize2.ncl") );
	ASSERT_TRUE( compareTo("standardText_size12") );
	ASSERT_TRUE( pressKey( ::util::key::red ));
	ASSERT_TRUE( compareTo("standardText_size72") );
}
TEST_F( Ginga, media_dinamic_fontSize3 ) {
	ASSERT_TRUE( play("media/fontSize/dinamic_fontSize3.ncl") );
	ASSERT_TRUE( compareTo("standardText_size12") );
	ASSERT_TRUE( pressKey( ::util::key::red ));
	ASSERT_TRUE( compareTo("standardText_size460") );
}
TEST_F( Ginga, media_dinamic_fontSize4 ) {
	ASSERT_TRUE( play("media/fontSize/dinamic_fontSize4.ncl") );
	ASSERT_TRUE( compareTo("standardText_size460") );
	ASSERT_TRUE( pressKey( ::util::key::red ));
	ASSERT_TRUE( compareTo("standardText_size12") );
}
TEST_F( Ginga, media_dinamic_fontSize5 ) {
	ASSERT_TRUE( play("media/fontSize/dinamic_fontSize5.ncl") );
	ASSERT_TRUE( compareTo("standardText_size460") );
	ASSERT_TRUE( pressKey( ::util::key::red ));
	ASSERT_TRUE( compareTo("standardText_size72") );
}
TEST_F( Ginga, media_dinamic_fontSize6 ) {
	ASSERT_TRUE( play("media/fontSize/dinamic_fontSize6.ncl") );
	ASSERT_TRUE( compareTo("standardText_size460") );
	ASSERT_TRUE( pressKey( ::util::key::red ));
	ASSERT_TRUE( compareTo("standardText_size460") );
}
}
