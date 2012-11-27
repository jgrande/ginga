#pragma once

#include <gtest/gtest.h>

class Option : public testing::Test {
public:
	Option();
	virtual ~Option();

protected:
	virtual void SetUp( void );
	virtual void TearDown( void );

};
