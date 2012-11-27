#pragma once

#include <string>
#include <vector>

typedef struct lua_State lua_State;

namespace canvas {
	class Surface;
}

namespace player {

class LuaPlayer;

namespace mcanvas {

class SurfaceWrapper;

class Module {
public:
	Module( LuaPlayer *player, lua_State *lua );
	virtual ~Module();

	void start( canvas::Surface *surface );
	void stop();

	int createSurface( canvas::Surface *surface, bool isPrimary=false );
	std::string getImagePath( const std::string &image );
	static Module *get( lua_State *st );

private:
	LuaPlayer *_player;
	lua_State *_lua;
	std::vector<SurfaceWrapper *> _surfaces;
};

}
}
