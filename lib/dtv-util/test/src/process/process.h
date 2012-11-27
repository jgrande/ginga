#include <gtest/gtest.h>

class Process : public testing::Test {
public:
	Process() {}
	virtual ~Process() {}

protected:
	virtual void SetUp( void );
	virtual void TearDown( void );
};
