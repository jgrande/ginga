#include "../../../src/id/pool.h"
#include <gtest/gtest.h>

TEST( Ident, constructor ) {
	util::id::Pool _pool("test");
}

TEST( Ident, alloc_one ) {
	util::id::Pool _pool("test");

	{
		util::id::Ident id = _pool.alloc();
	}
}

TEST( Ident, alloc_two ) {
	util::id::Pool _pool("test");

	{
		util::id::Ident id1 = _pool.alloc();
		util::id::Ident id2 = _pool.alloc();
		ASSERT_TRUE( id1 != id2 );
	}
}

TEST( Ident, alloc_max_reached_without_free ) {
	util::id::Pool _pool( "test", 0, 2 );

	{
		util::id::Ident id1 = _pool.alloc();
		util::id::Ident id2 = _pool.alloc();
		util::id::Ident id3 = _pool.alloc();

		try {
			util::id::Ident id4 = _pool.alloc();
			ASSERT_TRUE( false );
		} catch ( std::exception &/*e*/ ) {
		}
	}	
}

TEST( Ident, alloc_max_reached_with_free ) {
	util::id::Pool _pool( "test", 0, 2 );

	{
		util::id::Ident id1 = _pool.alloc();
		{
			util::id::Ident id2 = _pool.alloc();
		}
		util::id::Ident id3 = _pool.alloc();
		util::id::Ident id4 = _pool.alloc();
	}	
}

TEST( Ident, copy_contsruct ) {
	util::id::Pool _pool("test");

	{
		util::id::Ident id1 = _pool.alloc();
		util::id::Ident id2(id1);
		ASSERT_TRUE( id1 == id2 );
	}
}

TEST( Ident, opeator_copy ) {
	util::id::Pool _pool("test");

	{
		util::id::Ident id1 = _pool.alloc();
		util::id::Ident id2 = _pool.alloc();		
		ASSERT_TRUE( id1 != id2 );
		id1 = id2;
		ASSERT_TRUE( id1 == id2 );
	}
}

TEST( Ident, copy_empty_id ) {
	util::id::Pool _pool("test");

	{
		util::id::Ident id1 = _pool.alloc();
		util::id::Ident id2;
		ASSERT_TRUE( id1 != id2 );
		id1 = id2;
		ASSERT_TRUE( id1 == id2 );
	}
}

TEST( Ident, copy_from_empty_id ) {
	util::id::Pool _pool("test");

	{
		util::id::Ident id1;
		util::id::Ident id2 = _pool.alloc();
		ASSERT_TRUE( id1 != id2 );
		id1 = id2;
		ASSERT_TRUE( id1 == id2 );
	}
}

