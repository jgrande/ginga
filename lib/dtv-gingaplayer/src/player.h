#pragma once

#include "types.h"
#include "property/types.h"
#include "property/property.h"
#include "player/lua/event/types.h"
#include <util/log.h>
#include <boost/function.hpp>
#include <string>
#include <map>

namespace canvas {
	class System;
}

namespace player {

class TimeLineTimer;
class Device;

class Player {
public:
	explicit Player( Device *dev );
	virtual ~Player();

	//	Initialization
	bool initialized() const;
	bool initialize();
	void finalize();

	//	Media
	bool isPlaying() const;
	bool isPaused() const;
	bool play();
	void stop();
	void abort();
	void pause(bool pause);

	//	Properties
	template<typename T>
	bool setProperty( const std::string &name, const T &value );
	void addProperty( property::type::Type type, Property *prop );
	std::string rootPath() const;
	util::DWORD uptime() const;
	virtual bool isApplication() const;
	virtual bool isVisible() const;

	//	Callback initialization
	virtual void setEventCallback( const event::Callback &callback );
	virtual void setInputEventCallback( const event::InputCallback &callback );

	//	Timers
	typedef boost::function<void (void)> TimerCallback;
	void createTimer( util::DWORD ms, const TimerCallback &fnc );

	//	Signals
	typedef boost::function<void (void)> OnStatusChanged;
	typedef boost::function<void (bool)> OnPauseStatusChanged;

	void onStarted(const OnStatusChanged &fnc);
	void onStopped(const OnStatusChanged &fnc);
	void onPaused(const OnPauseStatusChanged &fnc);

	//	Getters
	Device *device() const;

protected:
	//	Types
	typedef std::map<property::type::Type,Property *> Properties;
	
	virtual bool init();
	virtual void fin();
	
	virtual bool startPlay()=0;
	virtual void stopPlay()=0;
	virtual void abortPlay();
	virtual void pausePlay( bool pause );
	virtual bool canPlay() const;
	virtual void beginRefresh();
	virtual void refresh();
	virtual void endRefresh();
	virtual void onPropertyChanged();
	void markModified();
	void applyChanges();
	void apply( bool needRefresh );

	//	Properties
	virtual void registerProperties();
	Property *getProperty( property::type::Type type ) const;	
	Property *getProperty( const std::string &name ) const;

	//	Source
	const std::string &url() const;
	schema::type schema() const;
	const std::string &body() const;
	const std::string &type() const;
	virtual bool supportSchemma( schema::type sch ) const;
	virtual bool supportRemote() const;
	bool checkUrl( const std::string &url );	

	//	Aux explicit duration
	void applyDuration();
	void onDurationExpired( int dur );

private:
	Device *_dev;	
	std::string _url;
	std::string _type;
	std::string _body;
	schema::type _schema;
	int _duration;
	bool _pause;
	bool _playing;
	bool _initialized;
	Properties _properties;
	TimeLineTimer *_timer;
	OnStatusChanged _onStarted, _onStopped;
	OnPauseStatusChanged _onPaused;

	Player() {}
};

template<typename T>
inline bool Player::setProperty( const std::string &name, const T &value ) {
	bool result=false;

	LOG_DEBUG("gingaplayer", "Player", "Set property begin: name=%s", name.c_str());
	
	//	Get property
	Property *prop = getProperty( name );
	if (!prop) {
		LOG_WARN("gingaplayer", "Player", "property not supported: %s", name.c_str());
		return result;
	}
	
	if (!isPlaying() && prop->isOnlyDynamic()) {
		LOG_WARN("gingaplayer", "Player", "property only supported when player has started: %s", name.c_str());
		return result;
	}

	try {
		//	Assign value, property changed?
		if (prop->assign( value ) && isPlaying()) {
			//	Dynamic property
			apply( prop->apply() );
		}

		//	Assign was ok!
		result=true;
	} catch ( std::exception &e ) {
		LOG_WARN("gingaplayer", "Player", "cannot set property: name=%s, error=%s", name.c_str(), e.what());
	}

	LOG_DEBUG("gingaplayer", "Player", "Set property end: name=%s, result=%d", name.c_str(), result);
	return result;
}

}

