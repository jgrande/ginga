#include "statics.h"
#include "const.h"
#include "message.h"
#include "target.h"
#include "formatter.h"
#include <stdexcept>
#include <boost/foreach.hpp>

namespace util {
namespace log {

LOG_LEVEL_TYPE Statics::_defaultLevel;
Groups Statics::_groups;
std::vector<Target*> Statics::_outputs;
Formatter *Statics::_formatter;

bool Statics::_initialized = false;
boost::mutex Statics::_initializedMutex;

int Statics::_nTransmitting;
boost::mutex Statics::_nTransmittingMutex;
boost::condition_variable Statics::_nTransmittingCond;

void Statics::initStatics( LOG_LEVEL_TYPE level ) {
	Statics::_initializedMutex.lock();
	if (Statics::_initialized) {
		throw std::logic_error("Log library already initialized!");
	}
	Statics::_defaultLevel = level;
	Statics::_nTransmitting = 0;
	Statics::_groups["all"]["all"] = _defaultLevel;
	Statics::_formatter = new Formatter();
	Statics::_initialized = true;
	Statics::_initializedMutex.unlock();
}

void Statics::finStatics() {
	Statics::_initializedMutex.lock();
	{
		boost::unique_lock<boost::mutex> lock(Statics::_nTransmittingMutex);
		while (Statics::_nTransmitting) {
			Statics::_nTransmittingCond.wait(lock);
		}
	}
	if (!Statics::_initialized) {
		throw std::logic_error("Log library already finalized!");
	}
	Statics::_initialized = false;
	BOOST_FOREACH( Target *t, Statics::_outputs) {
		t->fin();
		delete t;
	}
	Statics::_outputs.clear();
	delete Statics::_formatter;
	Statics::_formatter = NULL;
	Statics::_initializedMutex.unlock();
}

bool Statics::canLog( LOG_LEVEL_TYPE level, const std::string &group, const std::string &category ){
	LOG_LEVEL_TYPE curLev = Statics::_groups["all"]["all"];
	Groups::const_iterator group_it = Statics::_groups.find( group );
	if (group_it != Statics::_groups.end()) {
		Categories::const_iterator cat_it = group_it->second.find( category );
		if (cat_it != group_it->second.end()) {
			curLev = cat_it->second;
		} else {
			curLev = _groups[group]["all"];
		}
	} else {
		Categories::const_iterator cat_it = Statics::_groups["all"].find( category );
		if (cat_it != Statics::_groups["all"].end()) {
			curLev = cat_it->second;
		}
	}
	return (level<=curLev);
}

void Statics::transmitMessage( const Message &m ) {
	Statics::_initializedMutex.lock();
	if (!Statics::_initialized) {
		Statics::_initializedMutex.unlock();
		return;
	} else {
		Statics::_nTransmittingMutex.lock();
		Statics::_nTransmitting++;
		Statics::_nTransmittingMutex.unlock();
		Statics::_initializedMutex.unlock();
	}

	BOOST_FOREACH( Target *t, Statics::_outputs) {
		t->receive(m);
	}

	Statics::_nTransmittingMutex.lock();
	Statics::_nTransmitting--;
	Statics::_nTransmittingCond.notify_one();
	Statics::_nTransmittingMutex.unlock();
}

Formatter *Statics::getFormatter() {
	return Statics::_formatter;
}

void Statics::addTarget( Target *t ) {
	Statics::_outputs.push_back(t);
}

void Statics::flushMessages() {
	BOOST_FOREACH( Target *t, Statics::_outputs ) {
		t->flush();
	}
}

void Statics::setLevel( const std::string &group, const std::string &category, const LOG_LEVEL_TYPE level ) {
	Statics::_groups[group][category] = level;
	if (_groups[group].count("all") == 0) {
		Statics::_groups[group]["all"] = _defaultLevel;
	}
}

}
}
