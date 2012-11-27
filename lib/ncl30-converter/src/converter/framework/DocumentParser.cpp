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

#include "../../../include/framework/DocumentParser.h"
#include "../../../include/framework/XMLChHandler.h"
#include <ncl30/NclDocument.h>
#include <util/log.h>
#include <boost/filesystem/path.hpp>
#include <vector>

namespace bptn = ::br::pucrio::telemidia::ncl;
namespace fs = boost::filesystem;

namespace br {
namespace pucrio {
namespace telemidia {
namespace converter {
namespace framework {

DocumentParser::DocumentParser() {
	genericTable = new std::map<std::string, void*>;
	//initialize();
	//setDependencies();
	documentTree = NULL;
	xmlParser = NULL;
	_xmlHandler = NULL;
}

DocumentParser::~DocumentParser() {
	if (genericTable != NULL) {
		std::map<std::string, void*>* table;
		std::map<std::string, void*>::iterator i;
		i = genericTable->begin();
		while (i != genericTable->end()) {
			table = (std::map<std::string, void*>*) (i->second);
			if (table != NULL) {
				table->clear();
				delete table;
				table = NULL;
			}
			++i;
		}
		genericTable->clear();
		delete genericTable;
	}

	if (_xmlHandler) {
		delete _xmlHandler;
	}

	if (documentTree != NULL) {
		delete documentTree;
	}

	if (xmlParser != NULL) {
		delete xmlParser;
	}
}

void* DocumentParser::parse( std::string &uri ) {
	DOMElement* rootElement;

	uri = (fs::path( documentPath ) / uri).string();

	if (xmlParser == NULL) {
		xmlParser = new XMLParsing();
	}

	if (!_xmlHandler) {
		_xmlHandler = new XMLChHandler();
	}

	if (documentTree != NULL) {
		delete documentTree;
	}

	documentTree = xmlParser->parse( uri );

	if (documentTree == NULL) {
		LERROR("DocumentParser", "Error when parsing %s (file not found)", uri.c_str());
		return NULL;
	}

	//elemento raiz
	rootElement = (DOMElement*) documentTree->getDocumentElement();

	void* retValue = parse( rootElement, uri );

	if (documentTree != NULL) {
		delete documentTree;
		documentTree = NULL;
	}
	return retValue;
}

void* DocumentParser::parse( DOMElement* rootElement, std::string &uri ) {
	documentUri = uri;
	fs::path url( uri );
	documentPath = url.parent_path().string();

	return parseRootElement( rootElement );
}

void DocumentParser::setDependencies() {

}

const std::string &DocumentParser::getDocumentPath() {
	return documentPath;
}

const std::string &DocumentParser::getDocumentUri() {
	return documentUri;
}

DOMDocument *DocumentParser::getDocumentTree() {
	return documentTree;
}

XMLChHandler *DocumentParser::getXmlHandler() {
	return _xmlHandler;
}

void DocumentParser::addObject( const std::string &tableName, const std::string &key, void* value ) {

	std::map<std::string, void*>* table;
	std::map<std::string, void*>::iterator i;
	for (i = genericTable->begin(); i != genericTable->end(); ++i) {
		if (i->first == tableName) {
			table = (std::map<std::string, void*>*) (i->second);
			(*table)[key] = value;
			return;
		}
	}

	table = new std::map<std::string, void*>;
	(*table)[key] = value;
	(*genericTable)[tableName] = table;
}

void* DocumentParser::getObject( const std::string &tableName, const std::string &key ) {
	std::map<std::string, void*>* table = NULL;
	std::map<std::string, void*>::iterator i;
	for (i = genericTable->begin(); i != genericTable->end(); i++) {
		if (i->first == tableName) {
			table = (std::map<std::string, void*>*) i->second;
			break;
		}
	}
	if (table == NULL) {
		return NULL;
	} else {
		for (i = table->begin(); i != table->end(); i++) {
			if (i->first == key) {
				return i->second;
			}
		}
		return NULL;
	}
}

std::map<std::string, void*>* DocumentParser::getTable( const std::string &tableName ) {
	if (genericTable->find( tableName ) != genericTable->end())
		return (std::map<std::string, void*>*) ((*genericTable)[tableName]);
	else
		return NULL;
}

void DocumentParser::removeObject( const std::string &tableName, const std::string &key ) {
	std::map<std::string, void*>* table = NULL;
	std::map<std::string, void*>::iterator i;
	for (i = genericTable->begin(); i != genericTable->end(); i++) {
		if (i->first == tableName) {
			table = (std::map<std::string, void*>*) i->second;
			break;
		}
	}
	if (table == NULL) {
		LERROR("DocumentParser", "removing object");
	} else {
		for (i = table->begin(); i != table->end(); i++) {
			if (i->first == key) {
				//delete i->second;
				table->erase( i );
				return;
			}
		}
	}
	LERROR("DocumentParser", "removing object, key=%s, not found", key.c_str());
}

}
}
}
}
}
