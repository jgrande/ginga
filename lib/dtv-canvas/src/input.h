#pragma once

#include <util/keydefs.h>
#include <boost/function.hpp>

namespace canvas {

class System;

class Input {
public:
	explicit Input( System *sys );
	virtual ~Input();

	static void create( System *sys );

	//	Initialization
	virtual bool initialize();
	virtual void finalize();

	//	Getter
	virtual std::string name() const=0;

protected:
	System *sys() const;

private:
	System *_sys;
};

}

