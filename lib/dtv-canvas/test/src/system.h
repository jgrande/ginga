#pragma once

#include <string>
#include <gtest/gtest.h>

namespace canvas {
	class System;
}

namespace impl {
	void init( const std::string &name );
	void fin();
}

class System : public testing::Test {
public:
	static canvas::System *getSystem();
	static void setSystem( canvas::System *sys );

private:
	static canvas::System *_system;
};
