#include "../../src/buffer.h"
#include "../../src/types.h"
#include <gtest/gtest.h>

TEST( Buffer, default_constructor ) {
	util::Buffer buf;
	ASSERT_TRUE( buf.buffer() == NULL );
	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 0 );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.asHexa().empty() );
	const char *operChar = buf;
	ASSERT_TRUE( operChar == NULL );
}

TEST( Buffer, block_constructor ) {
	util::Buffer buf( 1024 );
	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 1024 );
	ASSERT_TRUE( buf.blockSize() == 1024 );
	ASSERT_TRUE( buf.asHexa().empty() );
	const char *operChar = buf;
	ASSERT_TRUE( operChar != NULL );
}

TEST( Buffer, copy_constructor ) {
	util::Buffer bufOriginal( 1024 );
	util::Buffer buf( bufOriginal );

	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 1024 );
	ASSERT_TRUE( buf.blockSize() == 1024 );
	ASSERT_TRUE( buf.asHexa().empty() );
	const char *operChar = buf;
	ASSERT_TRUE( operChar != NULL );
}

TEST( Buffer, buffer_owner_constructor ) {
	const char name[] = "rako";
	int s = (int)strlen(name);
	util::Buffer buf( (char *)name, s );

	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( buf.buffer() != name );
	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.asHexa().empty() == false );
	const char *operChar = buf;
	ASSERT_TRUE( operChar != NULL );
}

TEST( Buffer, buffer_no_owner_constructor ) {
	const char name[] = "rako";
	int s = (int)strlen(name);
	util::Buffer buf( (char *)name, s, false );

	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( buf.buffer() == name );
	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.asHexa().empty() == false );
	const char *operChar = buf;
	ASSERT_TRUE( operChar != NULL );
}

TEST( Buffer, buffer_no_owner2_constructor ) {
	char tmp[200];
	int s=200;
	util::Buffer buf( tmp, s, false );

	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( buf.buffer() == tmp );
	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.asHexa().empty() == false );
	const char *operChar = buf;
	ASSERT_TRUE( operChar != NULL );
}

TEST( Buffer, default_resize_mayor ) {
	util::Buffer buf;

	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 0 );
	ASSERT_TRUE( buf.blockSize() == 0 );
	buf.resize( 10 );
	ASSERT_TRUE( buf.length() == 10 );
	ASSERT_TRUE( buf.capacity() == 10 );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
}

TEST( Buffer, default_resize_equal ) {
	util::Buffer buf;

	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 0 );
	ASSERT_TRUE( buf.blockSize() == 0 );
	buf.resize( 0 );
	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 0 );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() == NULL );
}

TEST( Buffer, default_resize_zero ) {
	util::Buffer buf;
	const char name[] = "rako";
	int s = (int)strlen(name);

	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 0 );
	ASSERT_TRUE( buf.blockSize() == 0 );

	buf.copy( (char *)name, s );
	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );

	buf.resize( 0 );
	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
}

TEST( Buffer, default_resize_minor ) {
	util::Buffer buf;
	const char name[] = "rako";
	int s = (int)strlen(name);

	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 0 );
	ASSERT_TRUE( buf.blockSize() == 0 );

	buf.copy( (char *)name, s );
	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );

	buf.resize( 2 );
	ASSERT_TRUE( buf.length() == 2 );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
}

TEST( Buffer, default_resize_negative ) {
	util::Buffer buf;

	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 0 );
	ASSERT_TRUE( buf.blockSize() == 0 );
	buf.resize( -2 );
	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 0 );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() == NULL );
}

TEST( Buffer, block_resize_mayor1 ) {
	util::Buffer buf(100);

	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );
	buf.resize( 10 );
	ASSERT_TRUE( buf.length() == 10 );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );
	ASSERT_TRUE( buf.buffer() != NULL );
}

TEST( Buffer, block_resize_mayor2 ) {
	util::Buffer buf(100);

	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );
	buf.resize( 101 );
	ASSERT_TRUE( buf.length() == 101 );
	ASSERT_TRUE( buf.capacity() == 200 );
	ASSERT_TRUE( buf.blockSize() == 100 );
	ASSERT_TRUE( buf.buffer() != NULL );
}

TEST( Buffer, block_resize_equal ) {
	util::Buffer buf(100);

	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );
	buf.resize( 0 );
	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );
	ASSERT_TRUE( buf.buffer() != NULL );
}

TEST( Buffer, block_resize_negative ) {
	util::Buffer buf(100);

	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );
	buf.resize( -2 );
	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );
	ASSERT_TRUE( buf.buffer() != NULL );
}

TEST( Buffer, block_resize_minor ) {
	util::Buffer buf(100);
	const char name[] = "rako";
	int s = (int)strlen(name);

	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );

	buf.copy( (char *)name, s );
	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );
	ASSERT_TRUE( buf.buffer() != NULL );

	buf.resize( 2 );
	ASSERT_TRUE( buf.length() == 2 );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );
	ASSERT_TRUE( buf.buffer() != NULL );
}

TEST( Buffer, no_owner_resize_mayor1 ) {
	char tmp[100];
	int s = 100;
	util::Buffer buf( tmp, s, false );

	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	buf.resize( 10 );
	ASSERT_TRUE( buf.length() == 10 );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
}

TEST( Buffer, no_owner_resize_mayor2 ) {
	char tmp[100];
	int s = 100;
	util::Buffer buf( tmp, s, false );

	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	buf.resize( 101 );
	ASSERT_TRUE( buf.length() == 101 );
	ASSERT_TRUE( buf.capacity() == 101 );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
}

TEST( Buffer, no_owner_resize_mayor3 ) {
	char *tmp = NULL;
	int s = 0;
	util::Buffer buf( tmp, s, false );

	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	buf.resize( 101 );
	ASSERT_TRUE( buf.length() == 101 );
	ASSERT_TRUE( buf.capacity() == 101 );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
}

TEST( Buffer, no_owner_resize_equal ) {
	char tmp[100];
	int s = 100;
	util::Buffer buf( tmp, s, false );

	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	buf.resize( s );
	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
}

TEST( Buffer, no_owner_resize_minor ) {
	char tmp[100];
	int s = 100;
	util::Buffer buf( tmp, s, false );

	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );

	buf.resize( 2 );
	ASSERT_TRUE( buf.length() == 2 );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
}

TEST( Buffer, no_owner_resize_negative ) {
	char tmp[100];
	int s = 100;
	util::Buffer buf( tmp, s, false );

	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	buf.resize( -2 );
	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
}

//	void copy( char *buf, int len );
//		a) owner=true,  bufLen=len,   blockSize=0
//		b) owner=true,  bufLen>len,   blockSize=0
//		c) owner=true,  bufLen<len,   blockSize=0
//		d) owner=true,  bufLen<len,   blockSize=100
//		e) owner=false, bufLen=100, blockSize=0
TEST( Buffer, copy_a ) {
	char name1[] = "rako";
	char name2[] = "1234";
	int s = (int)strlen(name1);
	util::Buffer buf( (char *)name1, s );
	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );

	buf.copy( name2, s );
	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( strncmp(buf.buffer(),name2,s) == 0 );
}

TEST( Buffer, copy_b ) {
	char name1[] = "rako22";
	int s1 = (int)strlen(name1);

	char name2[] = "1234";
	int s2 = (int)strlen(name1);

	util::Buffer buf( (char *)name1, s1 );
	ASSERT_TRUE( buf.length() == s1 );
	ASSERT_TRUE( buf.capacity() == s1 );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );

	buf.copy( name2, s2 );
	ASSERT_TRUE( buf.length() == s2 );
	ASSERT_TRUE( buf.capacity() == s2 );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( strncmp(buf.buffer(),name2,s2) == 0 );
}

TEST( Buffer, copy_c ) {
	char name1[] = "ra";
	int s1 = (int)strlen(name1);

	char name2[] = "1234";
	int s2 = (int)strlen(name1);

	util::Buffer buf( (char *)name1, s1 );
	ASSERT_TRUE( buf.length() == s1 );
	ASSERT_TRUE( buf.capacity() == s1 );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );

	buf.copy( name2, s2 );
	ASSERT_TRUE( buf.length() == s2 );
	ASSERT_TRUE( buf.capacity() == s2 );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( strncmp(buf.buffer(),name2,s2) == 0 );
}

TEST( Buffer, copy_d ) {
	char name1[] = "ra";
	int s1 = (int)strlen(name1);
	util::Buffer buf( 100 );
	buf.copy( name1, s1 );
	ASSERT_TRUE( buf.length() == s1 );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );
	ASSERT_TRUE( buf.buffer() != NULL );

	char name2[] = "1234";
	int s2 = (int)strlen(name1);
	buf.copy( name2, s2 );
	ASSERT_TRUE( buf.length() == s2 );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );
	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( strncmp(buf.buffer(),name2,s2) == 0 );
}

//	void copy( int pos, char *buf, int len );
//		a) owner=true,  pos=len,   blockSize=0
//		b) owner=true,  pos>len,   blockSize=0
//		c) owner=true,  pos<len,   blockSize=0
//		d) owner=true,  pos<len,   blockSize=100
//		e) owner=false, pos=100,   blockSize=0
//		f) pos<0
TEST( Buffer, copy_with_pos_a ) {
	std::string name1 = "rako";
	util::Buffer buf( (char *)name1.c_str(), name1.length() );
	ASSERT_TRUE( buf.length() == (int)name1.length() );
	ASSERT_TRUE( buf.capacity() == (int)name1.length() );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );

	std::string name2 = "1234";
	std::string res = name1 + name2;
	buf.append( (char *)name2.c_str(), name2.length() );
	ASSERT_TRUE( buf.length() == (int)res.length() );
	ASSERT_TRUE( buf.capacity() == (int)res.length() );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( strncmp(buf.buffer(),res.c_str(),res.length()) == 0 );
}

TEST( Buffer, copy_with_pos_b ) {
	std::string name1("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	std::string name2( "rako" );
	std::string name3( "otrodddd" );

	util::Buffer buf( name1.c_str(), (int)name1.length() );
	ASSERT_TRUE( buf.length() == (int)name1.length() );
	ASSERT_TRUE( buf.capacity() == (int)name1.length() );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );

	buf.copy( name2.c_str(), (int)name2.length() );
	ASSERT_TRUE( buf.length() == (int)name2.length() );
	ASSERT_TRUE( buf.capacity() == (int)name1.length() );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( strncmp(buf.buffer(),name2.c_str(),(int)name2.length()) == 0 );

	buf.copy( buf.length()+5, name3.c_str(), (int)name3.length() );
	int s = (int)(name2.length()+name3.length()+5);
	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == (int)name1.length() );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( strncmp(buf.buffer(),"rakoaaaaaotrodddd",buf.length()) == 0 );
}

TEST( Buffer, copy_with_pos_c ) {
	std::string name1( "123456789" );
	std::string name2( "1234" );
	std::string res( "121234789" );

	util::Buffer buf( name1.c_str(), name1.length() );
	ASSERT_TRUE( buf.length() == (int)name1.length() );
	ASSERT_TRUE( buf.capacity() == (int)name1.length() );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( strncmp(buf.buffer(),name1.c_str(),(int)name1.length()) == 0 );

	buf.copy( 2, name2.c_str(), name2.length() );
	ASSERT_TRUE( buf.length() == (int)res.length() );
	ASSERT_TRUE( buf.capacity() == (int)res.length() );
	ASSERT_TRUE( buf.blockSize() == 0 );
	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( strncmp(buf.buffer(),res.c_str(),buf.length()) == 0 );
}

TEST( Buffer, copy_with_pos_d ) {
	std::string name1( "123456789" );
	std::string name2( "1234" );
	std::string res( "121234789" );
	util::Buffer buf( 100 );

	buf.copy( name1.c_str(), name1.length() );
	ASSERT_TRUE( buf.length() == (int)name1.length() );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );
	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( strncmp(buf.buffer(),name1.c_str(),(int)name1.length()) == 0 );

	buf.copy( 2, name2.c_str(), name2.length() );
	ASSERT_TRUE( buf.length() == (int)res.length() );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );
	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( strncmp(buf.buffer(),res.c_str(),buf.length()) == 0 );
}

TEST( Buffer, copy_with_pos_f ) {
	util::Buffer buf;

	ASSERT_TRUE( buf.buffer() == NULL );
	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 0 );
	ASSERT_TRUE( buf.blockSize() == 0 );

	const char name[] = "rako";
	int s = (int)strlen(name);
	buf.copy( -10, name, s );

	ASSERT_TRUE( buf.buffer() == NULL );
	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 0 );
	ASSERT_TRUE( buf.blockSize() == 0 );
}

//	void assign( char *buf, int len );
TEST( Buffer, assign_owner ) {
	const char name[] = "rako";
	int s = (int)strlen(name);
	util::Buffer buf( (char *)name, s, false );

	ASSERT_TRUE( buf.buffer() == name );
	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );

	char name2[] = "rako23";
	int s2 = (int)strlen(name2);
	buf.assign( name2, s2 );
	ASSERT_TRUE( buf.buffer() == name2 );
	ASSERT_TRUE( buf.length() == s2 );
	ASSERT_TRUE( buf.capacity() == s2 );
	ASSERT_TRUE( buf.blockSize() == 0 );

	char name3[] = "sdf";
	int s3 = (int)strlen(name3);
	buf.assign( name3, s3 );
	ASSERT_TRUE( buf.buffer() == name3 );
	ASSERT_TRUE( buf.length() == s3 );
	ASSERT_TRUE( buf.capacity() == s3 );
	ASSERT_TRUE( buf.blockSize() == 0 );
}

TEST( Buffer, assign_no_owner_buf_null ) {
	// owner=false && buf==NULL
	util::Buffer buf;
	ASSERT_TRUE( buf.buffer() == NULL );
	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 0 );
	ASSERT_TRUE( buf.blockSize() == 0 );

	char name[] = "rako";
	int s = (int)strlen(name);
	buf.assign( name, s );
	ASSERT_TRUE( buf.buffer() == name );
	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );
}

TEST( Buffer, assign_no_owner_buf_no_null ) {
	// owner=false && buf!=NULL
	char name[] = "rako";
	int s = (int)strlen(name);
	util::Buffer buf( name, s );
	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );

	char name2[] = "rako355";
	int s2 = (int)strlen(name2);
	buf.assign( name2, s2 );
	ASSERT_TRUE( buf.buffer() == name2 );
	ASSERT_TRUE( buf.length() == s2 );
	ASSERT_TRUE( buf.capacity() == s2 );
	ASSERT_TRUE( buf.blockSize() == 0 );
}

//	void swap( Buffer &other );
TEST( Buffer, swap ) {
	const char name[] = "rako";
	int s = (int)strlen(name);
	util::Buffer buf( (char *)name, s, false );

	ASSERT_TRUE( buf.buffer() == name );
	ASSERT_TRUE( buf.length() == s );
	ASSERT_TRUE( buf.capacity() == s );
	ASSERT_TRUE( buf.blockSize() == 0 );

	util::Buffer other( 100 );
	ASSERT_TRUE( other.buffer() != NULL );
	ASSERT_TRUE( other.length() == 0 );
	ASSERT_TRUE( other.capacity() == 100 );
	ASSERT_TRUE( other.blockSize() == 100 );

	buf.swap( other );

	ASSERT_TRUE( buf.buffer() != NULL );
	ASSERT_TRUE( buf.length() == 0 );
	ASSERT_TRUE( buf.capacity() == 100 );
	ASSERT_TRUE( buf.blockSize() == 100 );

	ASSERT_TRUE( other.buffer() == name );
	ASSERT_TRUE( other.length() == s );
	ASSERT_TRUE( other.capacity() == s );
	ASSERT_TRUE( other.blockSize() == 0 );
}
