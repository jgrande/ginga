#include "luaplayer.h"
#include "settings.h"
#include "lua/lua.h"
#include "lua/event/event.h"
#include "lua/canvas/canvas.h"
#include "lua/settings/settings.h"
#include "../property/forwardproperty.h"
#include "../device.h"
#include "../system.h"
#include <canvas/system.h>
#include <util/log.h>
#include <util/mcr.h>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>

namespace player {

namespace fs = boost::filesystem;

LuaPlayer::LuaPlayer( Device *dev )
  : GraphicPlayer( dev )
{
	_lua = NULL;
	_event = NULL;
	_canvas = NULL;
	_settings = NULL;
}

LuaPlayer::~LuaPlayer()
{
	assert(!_event);
	assert(!_canvas);
	assert(!_settings);
}

bool LuaPlayer::isApplication() const {
	return true;
}

bool LuaPlayer::init() {
	assert( !_lua );
	
	//	Initialize graphic player
	if (!GraphicPlayer::init()) {
		return false;
	}
	
	//	Create lua state
	_lua = luaL_newstate();
	if (!_lua) {
		LWARN("LuaPlayer", "Cannot initialize lua engine");
		return false;
	}

	if (!loadModules()) {
		LWARN("LuaPlayer", "Cannot load lua modules");
		return false;
	}

	return true;
}

void LuaPlayer::fin() {
	unloadModules();
	closeLua();
	GraphicPlayer::fin();
}

bool LuaPlayer::loadModules() {
	//	Open libs
	luaL_openlibs(_lua);

	//	Initialize event/canvas modules
	_event = new event::Module( device()->systemPlayer(), this, _lua );
	_canvas = new mcanvas::Module( this, _lua );
	_settings = new settings::Module( this, _lua );

	return true;
}

void LuaPlayer::unloadModules() {
	//	Unload event module
	DEL(_event);
	DEL(_canvas);
	DEL(_settings);
}

void LuaPlayer::closeLua() {
	if (_lua) {
		lua_close( _lua );
		_lua = NULL;
	}
}

void LuaPlayer::addPath( const std::string &modulePath ) {
	lua_getglobal( _lua, "package" );
	lua_getfield( _lua, -1, "path" ); // get field "path" from table at top of stack (-1)
	if (_packagePath.empty()) {
		_packagePath = lua_tostring( _lua, -1 ); // grab path string from top of stack
	}

	std::string cur_path=_packagePath;
	
	{	// Add search: modulePath/?
		cur_path.append( ";" );
		fs::path path = modulePath;
		path /= "?";
		cur_path.append( path.string().c_str() );
	}

	{	// Add search: modulePath/?.lua
		cur_path.append( ";" ); // do your path magic here
		fs::path path = modulePath;
		path /= "?.lua";
		cur_path.append( path.string().c_str() );
	}

	lua_pop( _lua, 1 ); // get rid of the string on the stack we just pushed on line 5
	lua_pushstring( _lua, cur_path.c_str() ); // push the new one
	lua_setfield( _lua, -2, "path" ); // set the field "path" in table at -2 with value at top of stack
	lua_pop( _lua, 1 ); // get rid of package table from top of stack
}

bool LuaPlayer::startPlay( void ) {
	if (GraphicPlayer::startPlay()) {
		assert(_lua);

		//	Calculate the path from lua file
		LINFO("LuaPlayer", "Start play, source=%s", body().c_str());

		//	Add path to load library
		addPath( rootPath() );
		
		//	Start canvas
		_canvas->start( surface() );
		return true;
	}
	return false;
}

void LuaPlayer::stopPlayer( event::evtAction::type evtAction ) {
	assert(_lua);	
	LINFO("LuaPlayer", "Stop play");

	onPresentationEvent( evtAction );
	
	//	Stop canvas
	_canvas->stop();

	GraphicPlayer::stopPlay();
}

void LuaPlayer::stopPlay( void ) {
	stopPlayer( event::evtAction::stop );
}

void LuaPlayer::pausePlay( bool pause ) {
	if (pause) {
		onPresentationEvent( event::evtAction::pause );
	} else {
		onPresentationEvent( event::evtAction::resume );
	}
}

void LuaPlayer::abortPlay( void ) {
	stopPlayer( event::evtAction::abort );
}

void LuaPlayer::refresh() {
	//	Load file
	if (luaL_dofile(_lua, body().c_str() )) {
		int i=lua_gettop(_lua);
		std::string desc(lua_tostring(_lua, i));
		std::string path = desc.substr(0,desc.find(":"));
		desc.erase(0,desc.find(":")+1);
		std::string line = desc.substr(0,desc.find(":"));
		desc.erase(0,desc.find(":")+1);
		LERROR("LuaPlayer", "in lua script '%s' at line = %s, %s", path.c_str(), line.c_str(),desc.c_str());
	}
	onPresentationEvent( event::evtAction::start );
}

void LuaPlayer::registerProperties() {
	//	Setup graphic player
	GraphicPlayer::registerProperties();

	{	//	Property attributionEvent
		ForwardProperty<AttributionEventData> *prop = new ForwardProperty<AttributionEventData>(
			boost::bind(&LuaPlayer::sendAttributionEvent,this,_1), true );
		addProperty( property::type::attributionEvent, prop );
	}

	{	//	Property presentationEvent
		ForwardProperty<std::string> *prop = new ForwardProperty<std::string>(
			boost::bind(&LuaPlayer::onPresentationEvent,this,event::evtAction::start,_1), true );
		addProperty( property::type::presentationEvent, prop );
	}

	{	//	Property selectionEvent
		ForwardProperty<SelectionEventData> *prop = new ForwardProperty<SelectionEventData>(
			boost::bind(&LuaPlayer::sendKeyEvent,this,_1) );
		addProperty( property::type::selectionEvent, prop );
	}		
}

void LuaPlayer::setEventCallback( const event::Callback &callback ) {
	_event->setCallback( callback );
}

void LuaPlayer::setInputEventCallback( const event::InputCallback &callback ) {
	_event->setInputEventCallback( callback );
}

void LuaPlayer::onPresentationEvent( player::event::evtAction::type action, const std::string &label/*=""*/ ) {
	_event->dispatchPresentation( action, label );
}

void LuaPlayer::sendAttributionEvent( const AttributionEventData &data ) {
	onAttributionEvent( data.first, data.second );
}

void LuaPlayer::onAttributionEvent( const std::string &name/*=""*/, const std::string &value/*=""*/ ) {
	_event->dispatchAttribution( name, event::evtAction::start, value );
}

void LuaPlayer::sendKeyEvent( const SelectionEventData &data ) {
	onKeyEvent( data.first, data.second );
}

void LuaPlayer::onKeyEvent( util::key::type key, bool isUp ) {
	_event->dispatchKey( key, isUp );
}

}
