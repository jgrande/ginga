#include "formatter.h"
#include "statics.h"
#include <cstdio>
#include <iostream>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

namespace util {
namespace log {

Target::Target() {
	_formatter = Statics::getFormatter();
	_fin = false;
	_waitingFlush = false;
	_thread = new boost::thread(boost::bind( &Target::loggerThread, this ));
}

Target::~Target() {
}

void Target::receive( const Message &message ) {
	_linesMutex.lock();
	_lines.push(_formatter->format(message));
	_linesMutex.unlock();
}

void Target::flush() {
	boost::unique_lock<boost::mutex> lock(_flushMutex);
	_waitingFlush = true;
	_linesCond.notify_one();
	_flushCond.wait(lock);
	flushImpl();
	_waitingFlush = false;
}

void Target::flushImpl() {
}

void Target::loggerThread() {
	_finMutex.lock();
	bool fin = _fin;
	_finMutex.unlock();

	while (!fin) {
		std::vector<std::string> localLines;
		{
			boost::unique_lock<boost::mutex> lock(_linesMutex);
			if(_lines.size()<1) {
				_linesCond.timed_wait(lock, boost::posix_time::milliseconds(100));
			}
			while (_lines.size()>0) {
				localLines.push_back(_lines.front());
				_lines.pop();
			}
		}
		BOOST_FOREACH(std::string l, localLines) {
			output( l );
		}
		localLines.clear();

		_flushMutex.lock();
		if (_waitingFlush) {
			_flushCond.notify_one();
		}
		_flushMutex.unlock();

		_finMutex.lock();
		fin = _fin;
		_finMutex.unlock();
	}
	while (_lines.size()>0) {
		output(_lines.front());
		_lines.pop();
	}
}

void Target::fin() {
	_finMutex.lock();
	_fin = true;
	_finMutex.unlock();
	_linesCond.notify_one();

	_thread->join();
	delete _thread;
	_thread = NULL;
}

void Cout::output( const std::string &line ) {
	std::cout << line;
}

LogFile::LogFile( const std::string &fileName ) {
	_file = NULL;
	_fileOpened = false;
	_fileName = fileName;
}

LogFile::~LogFile() {
	if (_fileOpened) {
		char cTimeString[100];
		time_t tRawTime;
		struct tm *tmInfo;

		time( &tRawTime );
		tmInfo = localtime( &tRawTime );
		strftime(cTimeString, 100, "%c", tmInfo);

		std::string msg("Log ended at: ");
		msg += cTimeString;
		msg += "\n";
		fwrite( msg.c_str(), sizeof( char ), msg.size(), _file );
		fclose( _file );
		_file = NULL;
	}
}

void LogFile::open() {
	_file = fopen( _fileName.c_str(), "w" );
	if (_file) {
		size_t result;

		char cTimeString[100];
		time_t tRawTime;
		struct tm *tmInfo;

		time( &tRawTime );
		tmInfo = localtime( &tRawTime );
		strftime(cTimeString, 100, "%c", tmInfo);
	
		std::string msg("Log started at: ");
		msg += cTimeString;
		msg += "\n";
		result = fwrite( msg.c_str(), sizeof( char ), msg.size(), _file );
		if (result>0) {
			_fileOpened = true;
		} else {
			fclose( _file );
			_file = NULL;
		}
	}
}

void LogFile::output( const std::string &line ) {
	if (!_fileOpened) {
		open();
	}
	if (_fileOpened) {
		fwrite( line.c_str(), sizeof( char ), line.size(), _file );
	}
}

void LogFile::flushImpl() {
	assert(_file);
	fflush(_file);
}

}
}
