#pragma once

#include "types.h"
#include <canvas/types.h>
#include <vector>
#include <map>
#include <string>

namespace connector {
	class EditingCommandData;
}

namespace player {

class System;
class Player;

class Device {
public:
	Device( System *sys );
	virtual ~Device();

	//	Player methods
	Player *create( const std::string &url, const std::string &mime );
	virtual Player *create( type::type typeOfPlayer );
	void destroy( Player *player );

	//	Initialize
	virtual bool initialize();
	virtual void finalize();

	//	Start/stop
	virtual void start();
	virtual void stop();
	void exit();

	//	Input manager
	virtual void onReserveKeys( const ::util::key::Keys &keys );
	void dispatchKey( ::util::key::type keystroke, bool isUp );
	void dispatchEditingCommand( connector::EditingCommandData *event );

	//	External resources
	bool download( const std::string &url, std::string &newFile );

	//	Factory methods
	virtual canvas::MediaPlayer *createMediaPlayer();
	virtual canvas::WebViewer *createWebViewer( canvas::Surface * );

	//	Getters
	canvas::Size size() const;
	System *systemPlayer() const;
	canvas::System *system() const;
	virtual bool haveVideo() const;
	virtual bool haveAudio() const;

protected:
	typedef std::map<std::string,std::string> DownloadCache;
	
	Player *addPlayer( Player *player );
	void enqueue( const boost::function<void (void)> &func );
	bool tryDownload( const std::string &url, std::string &file );
	
private:
	System *_sys;
	canvas::System *_canvas;
	std::vector<Player *> _players;
	DownloadCache _downloadCache;
};

}

