/******************************************************************************
 Este arquivo eh parte da implementacao do ambiente declarativo do middleware
 Ginga (Ginga-NCL).

 Direitos Autorais Reservados (c) 1989-2007 PUC-Rio/Laboratorio TeleMidia

 Este programa eh software livre; voce pode redistribui-lo e/ou modificah-lo sob
 os termos da Licenca Publica Geral GNU versao 2 conforme publicada pela Free
 Software Foundation.

 Este programa eh distribuido na expectativa de que seja util, porem, SEM
 NENHUMA GARANTIA; nem mesmo a garantia implicita de COMERCIABILIDADE OU
 ADEQUACAO A UMA FINALIDADE ESPECIFICA. Consulte a Licenca Publica Geral do
 GNU versao 2 para mais detalhes.

 Voce deve ter recebido uma copia da Licenca Publica Geral do GNU versao 2 junto
 com este programa; se nao, escreva para a Free Software Foundation, Inc., no
 endereco 59 Temple Street, Suite 330, Boston, MA 02111-1307 USA.

 Para maiores informacoes:
 ncl @ telemidia.puc-rio.br
 http://www.ncl.org.br
 http://www.ginga.org.br
 http://www.telemidia.puc-rio.br
 ******************************************************************************
 This file is part of the declarative environment of middleware Ginga (Ginga-NCL)

 Copyright: 1989-2007 PUC-RIO/LABORATORIO TELEMIDIA, All Rights Reserved.
 Copyright 2010 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata


 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License version 2 as published by
 the Free Software Foundation.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 PARTICULAR PURPOSE.  See the GNU General Public License version 2 for more
 details.

 You should have received a copy of the GNU General Public License version 2
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA

 For further information contact:
 ncl @ telemidia.puc-rio.br
 http://www.ncl.org.br
 http://www.ginga.org.br
 http://www.telemidia.puc-rio.br
 *******************************************************************************/

#include "presentationenginemanager.h"
#include "../include/FormatterMediator.h"
#include "../include/adapters/FormatterPlayerAdapter.h"
#include "../include/privatebase/IPrivateBaseManager.h"
#include "generated/config.h"
#include <gingaplayer/system.h>
#include <gingaplayer/device.h>
#include <gingaplayer/player/settings.h>
#include <canvas/size.h>
#include <canvas/system.h>
#include <util/keydefs.h>
#include <util/log.h>
#include <util/mcr.h>

using std::string;
using std::vector;
using std::map;

using ::br::pucrio::telemidia::ginga::ncl::FormatterMediator;
using ::br::pucrio::telemidia::ginga::ncl::PrivateBaseManager;
using ::br::pucrio::telemidia::ginga::ncl::adapters::FormatterPlayerAdapter;

namespace br {
namespace pucrio {
namespace telemidia {
namespace ginga {
namespace ncl {

PresentationEngineManager::PresentationEngineManager( player::System *sys ) :
		_sys( sys ),
		_formatter( NULL ),
		_paused( false ),
		_stopped( false ),
		_currentPrivateBaseId( "-1" ) {
	assert( _sys );
}

PresentationEngineManager::~PresentationEngineManager() {
}

void PresentationEngineManager::setBaseId( const std::string &id ) {
	_currentPrivateBaseId = id;
}

//	Compare
static boost::condition_variable _stopWakeup;
static boost::mutex _stopMutex;

bool PresentationEngineManager::startDocument( const std::string &file ) {
	LDEBUG( "PresentationEngineManager", "Start document: doc=%s", file.c_str() );

	if (formatter()) {
		_sys->enqueue( boost::bind( &PresentationEngineManager::stopDocument, this ) );
		{ //	Wait for compare
			boost::unique_lock<boost::mutex> lock( _stopMutex );
			while (!_stopped) {
				_stopWakeup.wait( lock );
			}
			_stopped = false;
		}

	}

	//	Init settings module
	player::settings::init();

	initFormatter( file );
	if (!formatter()->parseDocument()) {
		LWARN( "PresentationEngineManager", "parseDocument fail" );
		return false;
	}

	//	Play formatter
	_sys->enqueue( boost::bind( &FormatterMediator::play, formatter() ) );

	return true;
}

void PresentationEngineManager::stopDocument() {
	LDEBUG( "PresentationEngineManager", "Stop document" );

	_stopMutex.lock();

	//	Stop formatter
	formatter()->stop();
	delFormatter();

	//	Stop settings module
	player::settings::fin();

	_stopped = true;
	_stopMutex.unlock();
	_stopWakeup.notify_one();

}

bool PresentationEngineManager::run() {
	if (!_sys->canRun()) {
		LWARN( "PresentationEngineManager", "no device configurated" );
		return false;
	}

	onStart();

	{	//	Add listener for keys
		::util::key::Keys keys;

		keys.insert( ::util::key::greater_than_sign );
		keys.insert( ::util::key::less_than_sign );

		keys.insert( ::util::key::f10 );
		keys.insert( ::util::key::power );
		keys.insert( ::util::key::escape );
		keys.insert( ::util::key::stop );
		keys.insert( ::util::key::exit );

		keys.insert( ::util::key::f12 );
		keys.insert( ::util::key::pause );

		player::input::InputCallback fnc = boost::bind( &PresentationEngineManager::userEventReceived, this, _1, _2 );
		_sys->addInputListener( this, fnc, keys );
	}

	//	Run canvas loop
	_sys->run();

	stopDocument();
	onStop();

	//	Remove listeners
	_sys->delInputListener( this );

	return true;
}

void PresentationEngineManager::userEventReceived( ::util::key::type key, bool isUp ) {
	if (!isUp) {
		return;
	}

	switch ( key ) {
		case ::util::key::f10:
		case ::util::key::power:
		case ::util::key::escape:
		case ::util::key::stop:
		case ::util::key::exit: {
			_sys->exit();
			break;
		}
		case ::util::key::f12:
		case ::util::key::pause: {
			if (_paused) {
				formatter()->pause();
			} else {
				formatter()->resume();
			}
			_paused = !_paused;
			break;
		}
		case ::util::key::greater_than_sign: {
			formatter()->forward();
			break;
		}
		case ::util::key::less_than_sign: {
			formatter()->backward();
			break;
		}
		default:
			break;
	};

}

void PresentationEngineManager::onKeyPress( const KeyPressCallback &callback ) {
	FormatterPlayerAdapter::onKeyPress( callback );
	FormatterFocusManager::onKeyPress( callback );
}

//	Enqueue task into presentation thread
void PresentationEngineManager::enqueue( const boost::function<void( void )> &func ) {
	_sys->enqueue( func );
}

player::Device *PresentationEngineManager::mainScreen() const {
	return _sys->getDevice( "systemScreen(0)", 0 );
}

player::System *PresentationEngineManager::sys() {
	return _sys;
}

FormatterMediator *PresentationEngineManager::formatter() {
	return _formatter;
}

const std::string &PresentationEngineManager::baseId() {
	return _currentPrivateBaseId;
}

void PresentationEngineManager::initFormatter( const std::string &file ) {
	_formatter = new FormatterMediator( _currentPrivateBaseId, file, _sys );
}

void PresentationEngineManager::delFormatter() {
	DEL( _formatter );
}

void PresentationEngineManager::onStart() {
}

void PresentationEngineManager::onStop() {
}

}
}
}
}
}
