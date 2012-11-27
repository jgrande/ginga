/*******************************************************************************

  Copyright (C) 2010, 2011 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata

********************************************************************************

  This file is part of DTV-util implementation.

    DTV-util is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by the Free
  Software Foundation, either version 2 of the License.

    DTV-util is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
  this program. If not, see <http://www.gnu.org/licenses/>.

********************************************************************************

  Este archivo es parte de la implementación de DTV-util.

    DTV-util es Software Libre: Ud. puede redistribuirlo y/o modificarlo
  bajo los términos de la Licencia Pública General Reducida GNU como es publicada por la
  Free Software Foundation, según la versión 2 de la licencia.

    DTV-util se distribuye esperando que resulte de utilidad, pero SIN NINGUNA
  GARANTÍA; ni siquiera la garantía implícita de COMERCIALIZACIÓN o ADECUACIÓN
  PARA ALGÚN PROPÓSITO PARTICULAR. Para más detalles, revise la Licencia Pública
  General Reducida GNU.

    Ud. debería haber recibido una copia de la Licencia Pública General Reducida GNU
  junto a este programa. Si no, puede verla en <http://www.gnu.org/licenses/>.

*******************************************************************************/
#include "taskqueue.h"
#include "task.h"
#include "log.h"
#include <boost/foreach.hpp>

namespace util {

TaskQueue::TaskQueue( void )
{
	_exit = false;
}

TaskQueue::~TaskQueue( void )
{
	clear();
}

void TaskQueue::clear( void ) {
	Task *task;
	_mutex.lock();
	while (!_tasks.empty()) {
		task = _tasks.front();
		LDEBUG("TaskQueue", "[TaskQueue %p] clear task=%p, empty=%d", this, task, _tasks.empty());
		delete task;
		_tasks.pop();
	}
	_mutex.unlock();
}

void TaskQueue::push( Task *task ) {
	assert(task);

	LDEBUG("TaskQueue", "[TaskQueue %p] push task=%p", this, task);
	_mutex.lock();
	_tasks.push( task );
	_mutex.unlock();

	//	Wakeup thread
	_cond.notify_all();
}

bool TaskQueue::start( bool withThread/*=true*/ ) {
	LINFO("TaskQueue", "[TaskQueue %p] start", this);

	_exit = false;
	if (withThread) {
		_thread = boost::thread( boost::bind( &TaskQueue::loop, this) );
	}
	return true;
}

void TaskQueue::stop( void ) {
	LINFO("TaskQueue", "[TaskQueue %p] stop", this);

	_mutex.lock();
	_exit = true;
	_mutex.unlock();

	//	Wakeup thread
	_cond.notify_all();

	if (_thread.joinable()) {
		_thread.join();
	}
}

void TaskQueue::processTasks() {
	Task *task;
	std::vector<Task *> tasks;

	//	Get all task to run
	_mutex.lock();
	while (!_tasks.empty()) {
		task = _tasks.front();
		_tasks.pop();
		tasks.push_back( task );
	}
	_mutex.unlock();

	//	Run without lock
	runTasks( tasks );
}

bool TaskQueue::getTasks( std::vector<Task *> &tasks ) {
	Task *task;
	boost::unique_lock<boost::mutex> lock( _mutex );
	bool exit=(_exit && _tasks.empty());
	if (!exit) {
		if (_tasks.empty()) {
			//	Wait for task or exit!
			_cond.wait( lock );

			//	Save exit status
			exit = _exit;
		}

		//	Get tasks to run
		while (!_tasks.empty()) {
			task = _tasks.front();
			_tasks.pop();
			tasks.push_back( task );
		}
	}
	
	return exit;
}

void TaskQueue::loop() {
	bool exit=false;
	std::vector<Task *> tasks;

	LINFO("TaskQueue", "[TaskQueue %p] Begin loop", this);
	
	while (!exit) {
		exit = getTasks( tasks );
		runTasks( tasks );
	}

	clear();
	LINFO("TaskQueue", "[TaskQueue %p] exit loop", this);
}

void TaskQueue::runTasks( std::vector<Task *> &tasks ) {
	//	Run tasks
	BOOST_FOREACH( Task *task, tasks ) {
		LDEBUG("TaskQueue", "[TaskQueue %p] run task=%p", this, task);
		try {
			task->run();
		} catch ( const std::exception &e ) {
			LINFO("TaskQueue", "Catch exception: %s", e.what());
		}
		delete task;
		LDEBUG("TaskQueue", "[TaskQueue %p] run task=%p end!", this, task);
	}
	tasks.clear();
}

}
