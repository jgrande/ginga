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

#include "../../../include/ncl/NclTransitionConverter.h"
#include "../../../include/ncl/NclDocumentConverter.h"
#include "../../../include/framework/XMLChHandler.h"
#include "ncl30/NclDocument.h"
#include "ncl30/transition/Transition.h"
#include "ncl30/transition/TransitionBase.h"
#include "ncl30/transition/TransitionUtil.h"
#include <util/log.h>
#include <boost/lexical_cast.hpp>

namespace bptn = ::br::pucrio::telemidia::ncl;
namespace bptnt = ::br::pucrio::telemidia::ncl::transition;

namespace br {
namespace pucrio {
namespace telemidia {
namespace converter {
namespace ncl {
NclTransitionConverter::NclTransitionConverter( bptcf::DocumentParser *documentParser ) :
		NclTransitionParser( documentParser ) {
}

void NclTransitionConverter::addTransitionToTransitionBase( void* parentObject, void* childObject ) {

	((bptnt::TransitionBase*) parentObject)->addTransition( (bptnt::Transition*) childObject );
}

void* NclTransitionConverter::createTransitionBase( DOMElement* parentElement ) {
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	return new bptnt::TransitionBase( xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "id" ) ) ) );
}

void* NclTransitionConverter::createTransition( DOMElement *parentElement ) {

	bptnt::Transition* transition;
	std::string id, attValue;
	int type, subtype;
	short direction;
	double dur;
	std::string color;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	if (!parentElement->hasAttribute( xmlHndl->getXMLCh( "id" ) )) {

		return NULL;
	}

	id = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "id" ) ) );

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "type" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "type" ) ) );

		type = bptnt::TransitionUtil::getTypeCode( attValue );
		if (type < 0) {
			return NULL;
		}

	} else {
		// type must be defined
		LERROR("NclTransitionConverter", "createTransition, transition type must be defined");
		return NULL;
	}

	transition = new bptnt::Transition( id, type );

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "subtype" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "subtype" ) ) );

		subtype = bptnt::TransitionUtil::getSubtypeCode( type, attValue );
		if (subtype >= 0) {
			transition->setSubtype( subtype );
		}
	}

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "dur" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "dur" ) ) );

		dur = boost::lexical_cast<float>( attValue.substr( 0, attValue.length() - 1 ) );
		transition->setDur( dur * 1000 );
	}

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "startProgress" ) )) {

		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "startProgress" ) ) );

		transition->setStartProgress( boost::lexical_cast<float>( attValue ) );
	}

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "endProgress" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "endProgress" ) ) );

		transition->setEndProgress( boost::lexical_cast<float>( attValue ) );
	}

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "direction" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "direction" ) ) );

		direction = bptnt::TransitionUtil::getDirectionCode( attValue );
		if (direction >= 0) {
			transition->setDirection( direction );
		}
	}

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "fadeColor" ) )) {
		color = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "fadeColor" ) ) );

		transition->setFadeColor( color );
	}

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "horzRepeat" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "horzRepeat" ) ) );

		transition->setHorzRepeat( boost::lexical_cast<int>( attValue ) );
	}

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "vertRepeat" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "vertRepeat" ) ) );

		transition->setVertRepeat( boost::lexical_cast<int>( attValue ) );
	}

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "borderWidth" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "borderWidth" ) ) );

		transition->setBorderWidth( boost::lexical_cast<int>( attValue ) );
	}

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "borderColor" ) )) {
		color = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "borderColor" ) ) );

		transition->setBorderColor( color );
	}

	return transition;
}

void NclTransitionConverter::addImportBaseToTransitionBase( void* parentObject, void* childObject ) {

	std::string baseAlias, baseLocation;
	NclDocumentConverter* compiler;
	bptn::NclDocument* importedDocument;
	bptnt::TransitionBase* createdBase;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	// get the external base alias and location
	baseAlias = xmlHndl->getStr( ((DOMElement*) childObject)->getAttribute( xmlHndl->getXMLCh( "alias" ) ) );

	baseLocation = xmlHndl->getStr( ((DOMElement*) childObject)->getAttribute( xmlHndl->getXMLCh( "documentURI" ) ) );

	compiler = (NclDocumentConverter*) getDocumentParser();
	importedDocument = compiler->importDocument( baseLocation );
	if (importedDocument == NULL) {
		return;
	}

	createdBase = importedDocument->getTransitionBase();
	if (createdBase == NULL) {
		return;
	}

	// insert the imported base into the document region base
	try {
		((bptnt::TransitionBase*) parentObject)->addBase( createdBase, baseAlias, baseLocation );

	} catch (std::exception* exc) {
		LERROR("NclTransitionConverter", "addImportBaseToTransitionBase, exception '%s'", exc->what());
	}
}
}
}
}
}
}
