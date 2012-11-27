#include <gtest/gtest.h>

class LoggerTest : public testing::Test {
public:
	LoggerTest();
	virtual ~LoggerTest() {}

protected:
	virtual void SetUp( void );
	virtual void TearDown( void ){}

	std::string _file;
};
