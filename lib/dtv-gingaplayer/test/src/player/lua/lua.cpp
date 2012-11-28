#include "../../util.h"
#include "luaplayer.h"
#include "../../../../src/player/lua/event/event.h"
#include "../../../../src/player/luaplayer.h"
#include "../../../../src/device.h"
#include "../../../../src/system.h"
#include "../../../../src/player/settings.h"
#include "generated/config.h"
#include <canvas/system.h>
#include <canvas/canvas.h>
#include <util/mcr.h>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

namespace fs = boost::filesystem;

namespace lua {

void scanFiles( const std::string &path, std::vector<std::string> &files, int maxDepth ) {
	if (fs::exists( path )) {
		fs::directory_iterator end_itr;
		for (fs::directory_iterator itr( path ); itr != end_itr; ++itr ) {
			if (fs::is_directory( itr->status() ) && 0 < maxDepth) {
				scanFiles( itr->path().string(), files, maxDepth - 1 );
			}
			else if (fs::is_regular_file( itr->status() )) {
				fs::path file = itr->path();
				if (file.extension() == ".lua") {
					files.push_back( file.string() );
				}
			}
		}
	}
}

std::vector<std::string> scanFiles( const std::string &dir ) {
	std::vector<std::string> files;
	fs::path rootPath( util::getTestRoot() );
	rootPath /= "lua";
	rootPath /= dir;
	scanFiles( rootPath.string().c_str(), files, 0 );
	std::sort( files.begin(), files.end() );
	return files;
}

class LuaTest : public LuaPlayer {
public:
	LuaTest() {}
	virtual ~LuaTest() {}

protected:
	virtual void SetUp( void ) {
		LuaPlayer::SetUp();
		//	Get File
		_file = GetParam();
		ASSERT_FALSE( _file.empty() );
	}

	std::string getImageName( const std::string &file, canvas::Canvas *c ) {
		//	Remove extension to file
		fs::path image(file);
		std::string basicFileName = file.substr( 0, file.find( image.extension().string() ) );
		std::string returnStr = basicFileName + "_" + c->name() + ".png";
  		if (!fs::exists( returnStr )){
  			returnStr = basicFileName + ".png";
  		}
		return returnStr;
	}

	std::string _file;
};

class LuaCanvasTest : public LuaTest {};

namespace lua_canvas {

static boost::condition_variable _cWakeup;
static boost::mutex _mutex;
static bool _fin;

static void wait( void ) {
	boost::unique_lock<boost::mutex> lock( _mutex );
	if (!_fin) {
		_cWakeup.wait( lock );
	}
}

static void onReady( void ) {
	_mutex.lock();
	_fin=true;
	_mutex.unlock();
	_cWakeup.notify_all();
}

static void doPlay( player::System *sys, player::Player *player ) {
	ASSERT_TRUE( player->play() );
	sys->enqueue( boost::bind(&onReady) );
}

}

TEST_P( LuaCanvasTest, execute_canvas_script ) {
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,720,576) ) );
	ASSERT_TRUE ( _player->setProperty( "src", _file ) );

	lua_canvas::_fin=false;
	system()->enqueue( boost::bind(&lua_canvas::doPlay,system(),_player) );
	lua_canvas::wait();
	ASSERT_TRUE( util::compareImagesFromPath( canvas(), getImageName(_file, canvas()) ) );
}

INSTANTIATE_TEST_CASE_P(
    LuaCanvasTest,
    LuaCanvasTest,
    testing::ValuesIn( scanFiles("canvas") ));

class LuaCanvasFailTest : public LuaTest {};

TEST_P( LuaCanvasFailTest, execute_canvas_with_assert_script ) {
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,720,576) ) );	
	ASSERT_TRUE ( _player->setProperty( "src", _file ) );
	if (_player->play()) {
		ASSERT_TRUE( util::compareImagesFromPath( canvas(), getImageName(_file, canvas()) ) );
	}
}

INSTANTIATE_TEST_CASE_P(
    LuaCanvasFailTest,
    LuaCanvasFailTest,
    testing::ValuesIn( scanFiles("canvas.fail") ));


class LuaEventTest : public LuaTest {};

namespace event {

static bool _ready = true;
static bool _playResult = false;
static bool _playEnd = false;
static boost::condition_variable _cWakeup;
static boost::mutex _mutex;

static void init( void ) {
	_mutex.lock();
	_playEnd = false;
	_ready = true;
	_playResult = false;
	_mutex.unlock(); 	
}

static void wait( void ) {
	boost::unique_lock<boost::mutex> lock( _mutex );
	while (!_ready || !_playEnd) {
		_cWakeup.wait( lock );
	}
}

static void onReady( void ) {
	_cWakeup.notify_all();
}

static void ready( player::System *sys ) {
	_mutex.lock();
	_ready=true;
	_mutex.unlock();
	sys->enqueue( boost::bind(&onReady) );	
}

static void notReady( void ) {
	_mutex.lock();
	_ready=false;
	_mutex.unlock();
}

static void callback( player::System *sys, player::event::EventImpl *event ) {
	if ((*event)["class"] == "user") {
		if ((*event)["action"] == "wait") {
			notReady();
		}
		else if ((*event)["action"] == "signal") {
			ready( sys );
		}
	}
}

static void doPlay( player::System *sys, player::Player *player ) {
	bool result = player->play();

	_mutex.lock();
	_playResult = result;
	_playEnd = true;
	_mutex.unlock();
	
	sys->enqueue( boost::bind(&onReady) );
}

}

TEST_P( LuaEventTest, execute_event_script ) {
	event::init();
	_player->setInputEventCallback( boost::bind(&event::callback, system(),_1) );

	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,720,576) ) );
	_player->setProperty( "src", _file );
	
	system()->enqueue( boost::bind(&event::doPlay,system(),_player) );
	
	event::wait();
	ASSERT_TRUE( event::_playResult );
	ASSERT_TRUE( util::compareImages( canvas(), "green" ) );
}

INSTANTIATE_TEST_CASE_P(
    LuaEventTest,
    LuaEventTest,
    testing::ValuesIn( scanFiles("event") ));

#ifdef TEST_GINGAPLAYER_TCP
INSTANTIATE_TEST_CASE_P(
    LuaTCPEventTest,
    LuaEventTest,
    testing::ValuesIn( scanFiles("event/tcp") ));
#endif

class LuaSettingsReadOnlyTest: public LuaTest {};

TEST_P( LuaSettingsReadOnlyTest, execute_setting_script ) {
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,720,576) ) );
	ASSERT_TRUE ( _player->setProperty( "src", _file ) );
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), "green" ) );
}

INSTANTIATE_TEST_CASE_P(
	LuaSettingsTest,
	LuaSettingsReadOnlyTest,
	testing::ValuesIn( scanFiles("settings") ));

INSTANTIATE_TEST_CASE_P(
	LuaSettingsUserTest,
	LuaSettingsReadOnlyTest,
	testing::ValuesIn( scanFiles("settings/user") ));

INSTANTIATE_TEST_CASE_P(
	LuaSettingsDefaultTest,
	LuaSettingsReadOnlyTest,
	testing::ValuesIn( scanFiles("settings/default") ));

INSTANTIATE_TEST_CASE_P(
	LuaSettingsSiTest,
	LuaSettingsReadOnlyTest,
	testing::ValuesIn( scanFiles("settings/si") ));

INSTANTIATE_TEST_CASE_P(
	LuaSettingsChannelTest,
	LuaSettingsReadOnlyTest,
	testing::ValuesIn( scanFiles("settings/channel") ));

INSTANTIATE_TEST_CASE_P(
	LuaSettingsSystemTest,
	LuaSettingsReadOnlyTest,
	testing::ValuesIn( scanFiles("settings/system") ));

INSTANTIATE_TEST_CASE_P(
	LuaSettingsServiceTest,
	LuaSettingsReadOnlyTest,
	testing::ValuesIn( scanFiles("settings/service") ));

}


