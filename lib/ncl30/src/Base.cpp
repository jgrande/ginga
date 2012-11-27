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

#include "../include/Base.h"
#include <boost/foreach.hpp>
#include <algorithm>

namespace br {
namespace pucrio {
namespace telemidia {
namespace ncl {
Base::Base( const std::string & paramId ) :
		id( paramId ),
		baseAliases( new std::map<std::string, Base*> ),
		baseLocations( new std::map<std::string, Base*> ) {

	typeSet.insert( "Base" );
}

Base::~Base() {
	if (baseAliases != NULL) {
		baseAliases->clear();
		delete baseAliases;
		baseAliases = NULL;
	}
	if (baseLocations != NULL) {
		baseLocations->clear();
		delete baseLocations;
		baseLocations = NULL;
	}
//         if (baseSet != NULL){
//             baseSet->clear();
//             delete baseSet;
//             baseSet = NULL;
//         }
}

bool Base::addBase( Base* base, const std::string & alias, const std::string & location ) {

	if (base == NULL || location == "") {
		return false;
	}

	std::vector<Base*>::const_iterator i;
	i = std::find( baseSet.begin(), baseSet.end(), base );
	if (i != baseSet.end()) {
		return false;
	}

	baseSet.push_back( base );

	if (alias != "") {
		(*baseAliases)[alias] = base;
	}

	(*baseLocations)[location] = base;
	return true;
}

void Base::clear() {
	baseSet.clear();
	baseAliases->clear();
	baseLocations->clear();
}

Base* Base::getBase( const std::string & baseId ) {
	BOOST_FOREACH( Base * tempBase, baseSet )
	{
		if (tempBase->getId() == baseId) {
			return tempBase;
		}
	}
	return NULL;
}

std::string Base::getBaseAlias( Base* base ) {
	std::map<std::string, Base*>::iterator i;
	for (i = baseAliases->begin(); i != baseAliases->end(); ++i) {
		if (i->second == base) {
			return i->first;
		}
	}
	return "";
}

std::string Base::getBaseLocation( Base* base ) {
	std::map<std::string, Base*>::iterator i;
	for (i = baseLocations->begin(); i != baseLocations->end(); ++i) {
		if (i->second == base) {
			return i->first;
		}
	}
	return "";
}

std::vector<Base*>* Base::getBases() {
	return &baseSet;
}

bool Base::removeBase( Base* base ) {
	std::string alias, location;

	alias = getBaseAlias( base );
	location = getBaseLocation( base );

	std::vector<Base*>::iterator i;
	i = std::find( baseSet.begin(), baseSet.end(), base );
	if (i != baseSet.end()) {
		baseSet.erase( i );
		if (alias != "") {
			baseAliases->erase( alias );
		}
		baseLocations->erase( location );
		return true;
	}
	return false;
}

void Base::setBaseAlias( Base* base, const std::string & alias ) {
	std::string oldAlias;
	oldAlias = getBaseAlias( base );

	if (oldAlias != "") {
		baseAliases->erase( oldAlias );
	}

	if (alias != "") {
		(*baseAliases)[alias] = base;
	}
}

void Base::setBaseLocation( Base* base, const std::string & location ) {
	std::string oldLocation;

	oldLocation = getBaseLocation( base );
	if (oldLocation == "")
		return;

	baseLocations->erase( oldLocation );
	(*baseLocations)[location] = base;
}

const std::string & Base::getId() {
	return id;
}

void Base::setId( const std::string & id ) {
	this->id = id;
}

bool Base::instanceOf( const std::string & s ) {
	if (!typeSet.empty()) {
		return (typeSet.find( s ) != typeSet.end());
	} else {
		return false;
	}
}
}
}
}
}
