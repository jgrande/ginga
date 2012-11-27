#pragma once

#include <gtest/gtest.h>

class Cfg : public testing::Test {
public:
	Cfg();
	virtual ~Cfg();

protected:
	virtual void SetUp( void );
	virtual void TearDown( void );

};
