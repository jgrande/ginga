#pragma once
#include <map>
#include <string>

typedef struct lua_State lua_State;

namespace player {

class LuaPlayer;

namespace settings {

class Module
{
public:
	Module( LuaPlayer *player, lua_State *lua );
	virtual ~Module();

	static Module *get( lua_State *st );
	bool isReadOnly( void );
	void update( void );

protected:
	void exportTable( void );
	void readOnly( bool value );

private:
	LuaPlayer *_player;
	lua_State *_lua;
	bool _readOnly;
};

}
}
