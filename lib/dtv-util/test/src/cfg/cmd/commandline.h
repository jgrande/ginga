#pragma once

#include <gtest/gtest.h>

class CommandLine : public testing::Test {
public:
	CommandLine();
	virtual ~CommandLine();

protected:
	virtual void SetUp( void );
	virtual void TearDown( void );
	
	char **_params;
};
