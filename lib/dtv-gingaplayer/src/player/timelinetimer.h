#pragma once

#include <canvas/types.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <vector>

namespace player {

namespace impl {
	//	Types
	typedef boost::function<void (void)> TimerCallback;
	class Timer;
	struct CompareTimers : public std::binary_function<const Timer *, const Timer *, bool> {
        bool operator()( Timer *x, Timer *y );
	};

	namespace pt = boost::posix_time;

	namespace state {
		enum type { stopped, paused, running };
	}
}

class System;

class TimeLineTimer {
public:
	TimeLineTimer( System *sys );
	virtual ~TimeLineTimer();

	//	Methods
	void addTimer( util::DWORD ms, const impl::TimerCallback &fnc );
	void start();
	void stop();
	void pause();
	void unpause();

	//	Getters
	util::DWORD uptime() const;

protected:
	bool isRunning() const;
	void startTimer();
	void cancelTimer();
	void onExpired( util::id::Ident &id );
	void removeTimer( impl::Timer *timer, bool dispatch );
	void cleanTimers();
	
private:
	System *_sys;
	util::DWORD _elapsed;
	impl::state::type _state;
	impl::pt::ptime _startTimer;
	util::id::Ident _timerID;
	std::vector<impl::Timer *> _timers;
	impl::CompareTimers _cmp;
};

}
