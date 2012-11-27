#pragma once

#include <string>
#include <queue>
#include <boost/thread.hpp>

namespace util {
namespace log {

class Formatter;
class Message;

class Target {
public :
	Target();
	virtual ~Target();

	void fin();
	void receive( const Message &message );
	void flush();

protected:
	void loggerThread();
	virtual void output( const std::string &line ) = 0;
	virtual void flushImpl();
	Formatter *_formatter;

	std::queue<std::string> _lines;
	boost::mutex _linesMutex;
	boost::condition_variable _linesCond;

	bool _waitingFlush;
	boost::mutex _flushMutex;
	boost::condition_variable _flushCond;
	
	bool _fin;
	boost::mutex _finMutex;
	
	boost::thread *_thread;
};

class Cout : public Target {
    virtual void output( const std::string &line );
};

class LogFile : public Target {
public:
	LogFile( const std::string &fileName );
	virtual ~LogFile();

	virtual void output( const std::string &line );

protected:
	void open();
	void flushImpl();

	std::string _fileName;
	bool _fileOpened;
	FILE *_file;

private:
	LogFile();
};

}
}
