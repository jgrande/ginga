#pragma once

#include "../system.h"
#include <gtest/gtest.h>

namespace canvas {
	class Canvas;
}

class Surface : public System {
protected:
	virtual void SetUp( void );
	virtual void TearDown( void );


	canvas::Canvas* getCanvas();
	virtual std::string getSubDirectory() const;
	virtual std::string getExpectedPath( const std::string &fileName ) const;

};
