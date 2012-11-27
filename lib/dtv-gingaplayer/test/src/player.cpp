#include "player.h"
#include "util.h"
#include "../../src/player/imageplayer.h"
#include "../../src/player/timelinetimer.h"
#include "../../src/device.h"
#include "../../src/system.h"
#include <canvas/system.h>
#include <util/mcr.h>
#include <boost/filesystem.hpp>
#include <cstring>

namespace fs = boost::filesystem;

namespace impl {
static player::System *sys;
static player::Device *dev;
}

void init() {
	//	Init sys
	impl::sys = new player::System();
	impl::dev = new player::Device( impl::sys );
	impl::dev->initialize();
	impl::sys->addDevice( impl::dev );
}

void fin() {
	DEL( impl::sys );
}

void run() {
	impl::sys->run();
}

void stop() {
	impl::sys->exit();
}

Player::Player() {
	_player = NULL;
}

Player::~Player() {
}

player::Player *Player::createPlayer( const player::type::type &type ) const {
	return impl::dev->create( type );
}

player::TimeLineTimer *Player::createTimeLineTimer() const {
	return new player::TimeLineTimer( impl::sys );
}

void Player::destroyPlayer( player::Player *player ) {
	impl::dev->destroy( player );
}

//	Timers
util::id::Ident Player::registerTimer( ::util::DWORD ms, const canvas::EventCallback &callback ) {
	return impl::sys->registerTimer( ms, callback );
}


void Player::SetUp( void ){
	_player = impl::dev->create( type() );
	ASSERT_TRUE( _player != NULL );
	_result = false;
}

void Player::TearDown( void ){
	if (_player) {
		impl::dev->destroy( _player );
	}
}

void Player::doPlay( player::Player *player ) {
	_result = player->play();
	impl::sys->enqueue( boost::bind(&Player::onReady, this) );
}

void Player::wait() {
	boost::unique_lock<boost::mutex> lock( _mutex );
	_cWakeup.wait( lock );
}

void Player::onReady() {
	_cWakeup.notify_one();
}

bool Player::play( player::Player *player ){
	impl::sys->enqueue( boost::bind(&Player::doPlay, this, player) );
	wait();
	return _result;
}

canvas::Canvas *Player::canvas() {
	return impl::dev->system()->canvas();
}

player::System *Player::system() {
	return impl::sys;
}

player::Device *Player::device() {
	return impl::dev;
}

std::string Player::getExpectedPath( const std::string &fileName ) const {
	fs::path root;
	root /= playerType();
	root /= property();
	root /= fileName;
	return root.string();
}

TEST( Player, fromMime ) {
	ASSERT_TRUE( player::type::fromMime( "IMAGE/BMP" ) == player::type::image );
	ASSERT_TRUE( player::type::fromMime( "ImAGe/BmP" ) == player::type::image );
	ASSERT_TRUE( player::type::fromMime( "IMAGE/PNG" ) == player::type::image );
	ASSERT_TRUE( player::type::fromMime( "IMAGE/JPEG" ) == player::type::image );
	ASSERT_TRUE( player::type::fromMime( "APPLICATION/X-GINGA-NCLUA" ) == player::type::lua );
	ASSERT_TRUE( player::type::fromMime( "TEXT/PLAIN" ) == player::type::text );
	ASSERT_TRUE( player::type::fromMime( "" ) == player::type::unknown );
}

TEST( Player, getExtensionfromMime ) {
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "IMAGE/BMP" ), "bmp") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "ImAGe/BmP" ), "bmp") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "IMAGE/PNG" ), "png") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "IMAGE/JPEG" ), "jpg") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "IMAGE/GIF" ), "gif") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "AUDIO/BASIC" ), "wav") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "AUDIO/AC3" ), "ac3") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "AUDIO/MPA" ), "mpa") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "AUDIO/MP3" ), "mp3") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "AUDIO/MP2" ), "mp2") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "VIDEO/MPEG4" ), "mp4") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "VIDEO/MPEG" ), "mpg") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "VIDEO/MPV" ), "mpv") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "VIDEO/QUICKTIM" ), "mov") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "VIDEO/X-MSVIDEO" ), "avi") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "APPLICATION/X-GINGA-NCLUA" ), "lua") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "APPLICATION/X-NCL-NCLUA" ), "lua") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "APPLICATION/X-GINGA-NCL" ), "ncl") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "APPLICATION/X-NCL-NCL" ), "ncl") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "TEXT/PLAIN" ), "txt") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "TEXT/HTML" ), "htm") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "TEXT/CSS"), "css") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "TEXT/XML"), "xml") == 0 );
	ASSERT_TRUE( strcmp(player::type::getExtensionFromMime( "TEXT/SRT"), "srt") == 0 );
	ASSERT_TRUE( player::type::getExtensionFromMime( "" ) == NULL );
}

TEST( Player, fromExtension ) {
	ASSERT_TRUE( player::type::fromBody( "" ) == player::type::unknown );
	ASSERT_TRUE( player::type::fromBody( "." ) == player::type::unknown );
	ASSERT_TRUE( player::type::fromBody( "algo.bmp" ) == player::type::image );
	ASSERT_TRUE( player::type::fromBody( "algo.BMP" ) == player::type::image );
	ASSERT_TRUE( player::type::fromBody( "/home/alguien/foto.pNg" ) == player::type::image );
	ASSERT_TRUE( player::type::fromBody( "/home/run.lua" ) == player::type::lua );
	ASSERT_TRUE( player::type::fromBody( "/home/run" ) == player::type::unknown );
}

TEST( Player, parse_invalid_url ) {
	player::schema::type sch;
	std::string body;

	player::url::parse("http:/path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::file );
	ASSERT_TRUE( body == "http:/path/image.png");

	player::url::parse("http//path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::file );
	ASSERT_TRUE( body == "http//path/image.png");

	player::url::parse("://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::unknown );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("://", sch, body);
	ASSERT_TRUE( sch == player::schema::unknown );
	ASSERT_TRUE( body == "");

	player::url::parse("aaa://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::unknown );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("http://path://image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::http);
	ASSERT_TRUE( body == "path://image.png");
}

TEST( Player, parse_default ) {
	player::schema::type sch;
	std::string body;

	player::url::parse("path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::file );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("//path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::file );
	ASSERT_TRUE( body == "//path/image.png");

	player::url::parse("://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::unknown );
	ASSERT_TRUE( body == "path/image.png");
}

TEST( Player, parse_file ) {
	player::schema::type sch;
	std::string body;

	player::url::parse("file://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::file );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("FILE://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::file );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("FilE://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::file );
	ASSERT_TRUE( body == "path/image.png");
}

TEST( Player, parse_http ) {
	player::schema::type sch;
	std::string body;
	player::type::type type;

	player::url::parse("http://path/image.png", sch, body);
	type = player::type::get( sch, body, "" );
	ASSERT_TRUE( type == player::type::image );
	ASSERT_TRUE( sch == player::schema::http );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("HTTP://path/image.png", sch, body);
	type = player::type::get( sch, body, "" );
	ASSERT_TRUE( type == player::type::image );
	ASSERT_TRUE( sch == player::schema::http );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("hTTp://path/image.png", sch, body);
	type = player::type::get( sch, body, "" );
	ASSERT_TRUE( type == player::type::image );
	ASSERT_TRUE( sch == player::schema::http );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("http://prueba/prueba.php?id=1", sch, body);
	type = player::type::get( sch, body, "" );
	ASSERT_TRUE( type == player::type::html );
	ASSERT_TRUE( sch == player::schema::http );
	ASSERT_TRUE( body == "prueba/prueba.php?id=1");    
}

TEST( Player, parse_https ) {
	player::schema::type sch;
	std::string body;

	player::url::parse("https://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::https );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("HTTPS://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::https );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("hTTpS://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::https );
	ASSERT_TRUE( body == "path/image.png");
}

TEST( Player, parse_mirror ) {
	player::schema::type sch;
	std::string body;

	player::url::parse("ncl-mirror://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::mirror );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("NCL-MIRROR://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::mirror );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("Ncl-MirROr://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::mirror );
	ASSERT_TRUE( body == "path/image.png");
}

TEST( Player, parse_rtp ) {
	player::schema::type sch;
	std::string body;

	player::url::parse("rtp://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::rtp );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("RTP://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::rtp );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("rTp://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::rtp );
	ASSERT_TRUE( body == "path/image.png");
}

TEST( Player, parse_rtsp ) {
	player::schema::type sch;
	std::string body;

	player::url::parse("rtsp://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::rtsp );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("RTSP://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::rtsp );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("rTSp://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::rtsp );
	ASSERT_TRUE( body == "path/image.png");
}

TEST( Player, parse_sbdtv ) {
	player::schema::type sch;
	std::string body;

	player::url::parse("sbtvd-ts://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::sbtvd );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("SBTVD-TS://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::sbtvd );
	ASSERT_TRUE( body == "path/image.png");

	player::url::parse("sBTvD-tS://path/image.png", sch, body);
	ASSERT_TRUE( sch == player::schema::sbtvd );
	ASSERT_TRUE( body == "path/image.png");
}
