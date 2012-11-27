#include "device.h"
#include "system.h"
#include "input/manager.h"
#include "generated/config.h"
#include "player.h"
#include "player/luaplayer.h"
#include "player/imageplayer.h"
#include "player/animeplayer.h"
#include "player/textplayer.h"
#include "player/soundplayer.h"
#include "player/videoplayer.h"
#include "player/htmlplayer.h"
#include <canvas/player.h>
#include <canvas/canvas.h>
#include <canvas/system.h>
#include <util/log.h>
#include <util/cfg/cfg.h>
#include <util/mcr.h>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <curl/curl.h>

#define EXTERNAL_RESOURCE_TIMEOUT 5

namespace player {

namespace fs = boost::filesystem;

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

Device::Device( System *sys )
	: _sys(sys)
{
	_canvas = canvas::System::create();	
}

Device::~Device()
{
	if (_players.size()) {
		LWARN("Device", "not all players destroyed: size=%d", _players.size());
	}

	delete _canvas;

	BOOST_FOREACH( const DownloadCache::value_type &val, _downloadCache ) {
		try {
			fs::remove( val.second );
		} catch (...) {
		}
	}
}

System *Device::systemPlayer() const {
	return _sys;
}

//	Getters
canvas::System *Device::system() const {
	return _canvas;
}

bool Device::haveVideo() const {
	return true;
}

bool Device::haveAudio() const {
	return true;	
}

canvas::Size Device::size() const {
	util::cfg::PropertyNode &root = util::cfg::get("gui.window.size");
	canvas::Size size;
	size.w = root.get<int>( "width");
	size.h = root.get<int>( "height");
	return size;
}

//	Player
Player *Device::addPlayer( Player *player ) {
	//	Initialize player
	if (player->initialize()) {
		_players.push_back( player );
		return player;
	}
	else {
		LWARN("Device", "cannot initialize player");
		delete player;
		return NULL;
	}
}

Player *Device::create( enum type::type typeOfPlayer ) {
	Player *player;

	switch (typeOfPlayer) {
		case type::audio:
			player = new SoundPlayer( this );
			break;
		case type::image:
			player = new ImagePlayer( this );
			break;
		// case type::anime:
		// 	player = new AnimePlayer( this );
		// 	break;
		case type::lua:
			player = new LuaPlayer( this );
			break;
		case type::text:
			player = new TextPlayer( this );
			break;
		case type::video:
			player = new VideoPlayer( this );
			break;
		case type::html:
			player = new HtmlPlayer( this );
			break;
		default: {
			LWARN("Device", "cannot create player: type=%s", type::getName(typeOfPlayer) );
			return NULL;
		}
	};

	//	Add player to device
	return addPlayer( player );
}

Player *Device::create( const std::string &url, const std::string &mime ) {
	schema::type schema;
	std::string body;
	type::type typeOfPlayer;
	
	url::parse( url, schema, body );

	//	Check schema
	if (schema == schema::file || schema == schema::http || schema == schema::https) {
		typeOfPlayer=type::get( schema, body, mime );
	}
	else if (schema == schema::sbtvd
		|| schema == schema::rtsp
		|| schema == schema::rtp)
	{
		typeOfPlayer=type::video;
	}
	else {
		LWARN("Device", "schema not supported: schema=%s", schema::getName(schema) );
		return NULL;
	}

	LINFO("Device", "Create player: type=%s, schema=%s, body=%s, mime=%s",
		type::getName(typeOfPlayer), schema::getName(schema), body.c_str(), mime.c_str() );

	//	Setup src and type
	Player *player=create( typeOfPlayer );
	if (player) {
		player->setProperty( "src", url );
		player->setProperty( "type", mime );
	}
	return player;
}

void Device::destroy( Player *player ) {
	LDEBUG("Device", "Destroy player: player=%p", player);
	assert(player);
	
	std::vector<Player *>::iterator it=std::find(
		_players.begin(), _players.end(), player );
	if (it != _players.end()) {
		player->finalize();
		delete player;
		_players.erase( it );
	}
	else {
		LWARN("Device", "player is not member of this device");
	}
}

//	Start/stop
void Device::start() {
}

void Device::stop() {
}

//	Initialize
bool Device::initialize() {
	system()->setInputCallback( boost::bind(&Device::dispatchKey,this,_1,_2) );
	return system()->initialize();
}

void Device::finalize() {
	system()->finalize();
}

void Device::exit() {
	_sys->dispatchKey( ::util::key::exit, true );
}

//	Keys
void Device::onReserveKeys( const ::util::key::Keys &/*keys*/ ) {
	//	Do nothing
}

void Device::dispatchKey( util::key::type keyValue, bool isUp ) {
	_sys->dispatchKey( keyValue, isUp );
}

void Device::dispatchEditingCommand( connector::EditingCommandData *event ) {
	_sys->dispatchEditingCommand( event );
}

//	External resources
bool Device::download( const std::string &url, std::string &newFile ) {
	bool result;
	
	DownloadCache::const_iterator it=_downloadCache.find( url );
	if (it != _downloadCache.end()) {
		newFile=(*it).second;
		result=true;
	}
	else {
		result = tryDownload( url, newFile );
		if (result) {
			_downloadCache[url] = newFile;
		}
	}
	return result;
}

bool Device::tryDownload( const std::string &url, std::string &file ) {
	CURL *curl;
	bool result=false;

	curl = curl_easy_init();
	if (curl) {
		//	Set basic options
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, EXTERNAL_RESOURCE_TIMEOUT);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
 
		//	HTTPS options
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

		//	Setup file name (temporary, with unknown extension)
		fs::path fsTemp = fs::temp_directory_path();
		fsTemp /= "ginga_player_file%%%%%%%%";

		//	Add temporary extension
		std::string fileToDownload = fs::unique_path(fsTemp).string();
		fileToDownload += ".unknown";
		
		//	Open file
		FILE *pagefile = fopen(fileToDownload.c_str(), "wb");
		if (pagefile) {
			//	Setup file
			curl_easy_setopt(curl, CURLOPT_FILE, pagefile);
			
			//	Perform operation
			result = curl_easy_perform(curl) == CURLE_OK;

			//	Close file
			fclose(pagefile);

			//	Check result
			if (result) {
				//	Check content type
				char *ct; 
				result = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct) == CURLE_OK && ct;
				if (result) {
					const char *ext=type::getExtensionFromMime( ct );
					if (ext) {
						//	Fix file extension
						file = fs::unique_path(fsTemp).string();
						file += ".";
						file += ext;

						//	Rename file
						fs::rename( fileToDownload, file );
						LDEBUG( "Device", "File download: name=%s, mime=%s\n",
							file.c_str(),  ct );
						
						result=true;
					}
					else {
						result=false;
					}
				}
			}
		}
		
		//	Cleanup
		curl_easy_cleanup(curl);
	}

	if (!result) {
		LERROR("Device", "cannot load external resource: url=%s", url.c_str());
	}
	
	return result;
}

//	Factory methods
canvas::MediaPlayer *Device::createMediaPlayer() {
	return system()->player()->create( system() );
}

canvas::WebViewer *Device::createWebViewer( canvas::Surface *surface ) {
	return system()->createWebViewer( surface );
}

//	Aux
void Device::enqueue( const boost::function<void (void)> &func ) {
	_sys->enqueue( func );
}

}
