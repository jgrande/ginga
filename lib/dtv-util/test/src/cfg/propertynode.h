#pragma once

#include <gtest/gtest.h>

class PropertyNode : public testing::Test {
public:
	PropertyNode();
	virtual ~PropertyNode();
	util::cfg::PropertyNode _root;

protected:
	virtual void SetUp( void );
	virtual void TearDown( void );

};
