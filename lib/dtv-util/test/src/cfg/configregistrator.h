#pragma once

#include <list>
#include <gtest/gtest.h>

namespace util{
namespace reg{
	class Registrator;
}
}

class ConfigRegistrator : public testing::Test {
public:
	ConfigRegistrator();
	virtual ~ConfigRegistrator();

protected:
	virtual void SetUp( void );
	virtual void TearDown( void );

	std::list<util::reg::Registrator *> _list;
};

