#pragma once

#include "util.h"
#include "../../src/types.h"
#include <canvas/types.h>
#include <util/types.h>
#include <boost/thread.hpp>

namespace canvas {
	class System;
	class Canvas;
}

namespace player {
	class Player;
	class System;
	class Device;
	class TimeLineTimer;
}

void init();
void fin();
void run();
void stop();

class Player : public testing::TestWithParam<std::string> {
public:
	Player();
	virtual ~Player();

protected:
	virtual void SetUp( void );
	virtual void TearDown( void );

	bool play( player::Player *player );
	void doPlay( player::Player *player );
	void wait();
	void onReady();

	virtual std::string getExpectedPath( const std::string &fileName ) const;
	virtual std::string playerType() const = 0;
	virtual std::string property() const = 0;
	virtual player::type::type type() const = 0;

	canvas::Canvas *canvas();
	player::System *system();
	player::Device *device();

	player::Player *createPlayer( const player::type::type &type ) const;
	player::TimeLineTimer *createTimeLineTimer() const;
	void destroyPlayer( player::Player *player );
	util::id::Ident registerTimer( ::util::DWORD ms, const canvas::EventCallback &callback );

	player::Player *_player;

private:
	bool _result;
	boost::condition_variable _cWakeup;
	boost::mutex _mutex;
};
