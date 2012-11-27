#include <list>
#include <gtest/gtest.h>
#include "../../src/registrator.h"
#include "registrator.h"

static int a = 0,b = 0;
REGISTER_INIT( one ) {
	a += 1;
}

REGISTER_FIN( one ) {
	b += 100;
}

Registrator::Registrator()
{
}

Registrator::~Registrator() {
}

void Registrator::SetUp( void ) {

}

void Registrator::TearDown( void ) {

}


TEST_F( Registrator, init ) {
	util::reg::init();
	ASSERT_TRUE(a == 1);
}
TEST_F( Registrator, fin){
	util::reg::fin();
	ASSERT_TRUE(b == 100);
}
