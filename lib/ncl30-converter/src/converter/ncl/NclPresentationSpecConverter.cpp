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

#include "../../../include/ncl/NclPresentationSpecConverter.h"
#include "../../../include/ncl/NclImportConverter.h"
#include "../../../include/ncl/NclPresentationControlConverter.h"
#include "../../../include/ncl/NclDocumentConverter.h"
#include "../../../include/framework/ncl/NclLayoutParser.h"
#include "../../../include/framework/XMLChHandler.h"
#include "ncl30/Parameter.h"
#include "ncl30/NclDocument.h"
#include "ncl30/descriptor/Descriptor.h"
#include "ncl30/descriptor/DescriptorBase.h"
#include "ncl30/descriptor/GenericDescriptor.h"
#include "ncl30/switches/RuleBase.h"
#include "ncl30/navigation/FocusDecoration.h"
#include "ncl30/navigation/KeyNavigation.h"
#include "ncl30/transition/TransitionBase.h"
#include "ncl30/transition/Transition.h"
#include "ncl30/layout/RegionBase.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

namespace bptnd = ::br::pucrio::telemidia::ncl::descriptor;
namespace bptns = ::br::pucrio::telemidia::ncl::switches;
namespace bptnn = ::br::pucrio::telemidia::ncl::navigation;
namespace bptnt = ::br::pucrio::telemidia::ncl::transition;
namespace bptnl = ::br::pucrio::telemidia::ncl::layout;
namespace bptn = ::br::pucrio::telemidia::ncl;

namespace br {
namespace pucrio {
namespace telemidia {
namespace converter {
namespace ncl {
NclPresentationSpecConverter::NclPresentationSpecConverter( bptcf::DocumentParser *documentParser ) :
	NclPresentationSpecificationParser( documentParser ) {

}

void NclPresentationSpecConverter::addDescriptorToDescriptorBase( void *parentObject, void *childObject ) {

	((bptnd::DescriptorBase*) parentObject)->addDescriptor( (bptnd::GenericDescriptor*) childObject );
}

void NclPresentationSpecConverter::addDescriptorSwitchToDescriptorBase( void *parentObject, void *childObject ) {

	((bptnd::DescriptorBase*) parentObject)->addDescriptor( (bptnd::GenericDescriptor*) childObject );
}

void NclPresentationSpecConverter::addDescriptorParamToDescriptor( void *parentObject, void *childObject ) {

	bptcf::XMLChHandler *xmlHndl = getXmlHandler();
	// cast para descritor
	bptnd::Descriptor *descriptor = (bptnd::Descriptor*) parentObject;
	DOMElement*param = (DOMElement*) childObject;
	// recuperar nome e valor da variavel
	std::string paramName = xmlHndl->getStr( param->getAttribute( xmlHndl->getXMLCh( "name" ) ) );

	std::string paramValue = xmlHndl->getStr( param->getAttribute( xmlHndl->getXMLCh( "value" ) ) );

	// adicionar variavel ao descritor
	bptn::Parameter *descParam = new bptn::Parameter( paramName, paramValue );
	descriptor->addParameter( descParam );
}

void NclPresentationSpecConverter::addImportBaseToDescriptorBase( void *parentObject, void *childObject ) {

	std::string baseAlias, baseLocation;
	NclDocumentConverter* compiler;
	bptn::NclDocument *importedDocument, *thisDocument;
	bptnd::DescriptorBase *descriptorBase;
	std::map<int, bptnl::RegionBase*>* regionBases;
	std::map<int, bptnl::RegionBase*>::iterator i;
	bptns::RuleBase *ruleBase;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	// get the external base alias and location
	baseAlias = xmlHndl->getStr( ((DOMElement*) childObject)->getAttribute( xmlHndl->getXMLCh( "alias" ) ) );

	baseLocation = xmlHndl->getStr( ((DOMElement*) childObject)->getAttribute( xmlHndl->getXMLCh( "documentURI" ) ) );

	compiler = (NclDocumentConverter*) getDocumentParser();
	importedDocument = compiler->importDocument( baseLocation );
	if (importedDocument == NULL) {
		return;
	}

	descriptorBase = importedDocument->getDescriptorBase();
	if (descriptorBase == NULL) {
		return;
	}

	// insert the imported base into the document descriptor base
	try {
		((bptnd::DescriptorBase*) parentObject)->addBase( descriptorBase, baseAlias, baseLocation );

	} catch (...) {

	}

	// importing descriptor bases implies importing region, rule, and cost
	// function bases in order to maintain reference consistency
	thisDocument = (bptn::NclDocument*) getDocumentParser()->getObject( "return", "document" );

	regionBases = importedDocument->getRegionBases();
	if (regionBases != NULL && !regionBases->empty()) {
		i = regionBases->begin();
		while (i != regionBases->end()) {
			thisDocument->getRegionBase( 0 )->addBase( i->second, baseAlias, baseLocation );

			++i;
		}
	}

	ruleBase = importedDocument->getRuleBase();
	if (ruleBase != NULL) {
		try {
			thisDocument->getRuleBase()->addBase( ruleBase, baseAlias, baseLocation );

		} catch (...) {

		}
	}
}

void *NclPresentationSpecConverter::createDescriptorParam( DOMElement *parentElement ) {

	return parentElement;
}

void *NclPresentationSpecConverter::createDescriptorBind( DOMElement *parentElement ) {

	// ver componentCompilers para comentarios
	return parentElement;
}

void *NclPresentationSpecConverter::createDescriptorBase( DOMElement *parentElement ) {

	bptnd::DescriptorBase *descBase;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();
	// criar nova base de conectores com id gerado a partir do nome de seu
	// elemento
	descBase = new bptnd::DescriptorBase( xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "id" ) ) ) );

	return descBase;
}

void* NclPresentationSpecConverter::createDescriptor( DOMElement *parentElement ) {

	bptnd::Descriptor *descriptor;
	bptn::NclDocument *document;
	bptnl::LayoutRegion* region;

	long duration;

	bptnn::KeyNavigation* keyNavigation;
	bptnn::FocusDecoration* focusDecoration;
	std::string color;
	std::string attValue;
	std::vector<std::string> transIds;
	unsigned int i;
	bptnt::TransitionBase* transitionBase;
	bptnt::Transition* transition;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	XMLCh *tmpStr;
	std::string tmpChar;

	// cria descritor
	descriptor = new bptnd::Descriptor( xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "id" ) ) ) );

	document = (bptn::NclDocument*) getDocumentParser()->getObject( "return", "document" );

	// atributo region
	tmpStr = xmlHndl->getXMLCh( "region" );
	if (parentElement->hasAttribute( tmpStr )) {
		tmpChar = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );
		region = document->getRegion( tmpChar );

		if (region != NULL) {
			descriptor->setRegion( region );
		}
	}

	// atributo explicitDur
	tmpStr = xmlHndl->getXMLCh( "explicitDur" );
	if (parentElement->hasAttribute( tmpStr )) {

		std::string durStr = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );

		duration = (long) (boost::lexical_cast<float>( durStr.substr( 0, durStr.length() - 1 ) ) * 1000);

		descriptor->setExplicitDuration( duration );
	}

	tmpStr = xmlHndl->getXMLCh( "freeze" );
	if (parentElement->hasAttribute( tmpStr )) {
		std::string freeze = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );

		if (freeze == "true") {
			descriptor->setFreeze( true );

		} else {
			descriptor->setFreeze( false );
		}
	}

	// atributo player
	tmpStr = xmlHndl->getXMLCh( "player" );
	if (parentElement->hasAttribute( tmpStr )) {
		tmpChar = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );
		descriptor->setPlayerName( tmpChar );
	}

	// key navigation attributes
	keyNavigation = new bptnn::KeyNavigation();
	descriptor->setKeyNavigation( keyNavigation );
	tmpStr = xmlHndl->getXMLCh( "focusIndex" );
	if (parentElement->hasAttribute( tmpStr )) {
		tmpChar = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );
		keyNavigation->setFocusIndex( tmpChar );
	}

	tmpStr = xmlHndl->getXMLCh( "moveUp" );
	if (parentElement->hasAttribute( tmpStr )) {
		tmpChar = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );
		keyNavigation->setMoveUp( tmpChar );
	}

	tmpStr = xmlHndl->getXMLCh( "moveDown" );
	if (parentElement->hasAttribute( tmpStr )) {
		tmpChar = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );
		keyNavigation->setMoveDown( tmpChar );
	}

	tmpStr = xmlHndl->getXMLCh( "moveLeft" );
	if (parentElement->hasAttribute( tmpStr )) {
		tmpChar = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );
		keyNavigation->setMoveLeft( tmpChar );
	}

	tmpStr = xmlHndl->getXMLCh( "moveRight" );
	if (parentElement->hasAttribute( tmpStr )) {
		tmpChar = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );
		keyNavigation->setMoveRight( tmpChar );
	}

	focusDecoration = new bptnn::FocusDecoration();
	descriptor->setFocusDecoration( focusDecoration );
	tmpStr = xmlHndl->getXMLCh( "focusSrc" );
	if (parentElement->hasAttribute( tmpStr )) {
		focusDecoration->setFocusSrc( xmlHndl->getStr( parentElement->getAttribute( tmpStr ) ) );
	}

	tmpStr = xmlHndl->getXMLCh( "focusBorderColor" );
	if (parentElement->hasAttribute( tmpStr )) {
		tmpChar = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );
		color = tmpChar;

		focusDecoration->setFocusBorderColor( color );
	}

	tmpStr = xmlHndl->getXMLCh( "focusBorderWidth" );
	if (parentElement->hasAttribute( tmpStr )) {
		focusDecoration->setFocusBorderWidth( xmlHndl->getStr( parentElement->getAttribute( tmpStr ) ) );
	}

	tmpStr = xmlHndl->getXMLCh( "focusBorderTransparency" );
	if (parentElement->hasAttribute( tmpStr )) {
		focusDecoration->setFocusBorderTransparency( xmlHndl->getStr( parentElement->getAttribute( tmpStr ) ) );
	}

	tmpStr = xmlHndl->getXMLCh( "focusSelSrc" );
	if (parentElement->hasAttribute( tmpStr )) {
		focusDecoration->setFocusSelSrc( xmlHndl->getStr( parentElement->getAttribute( tmpStr ) ) );
	}

	tmpStr = xmlHndl->getXMLCh( "selBorderColor" );
	if (parentElement->hasAttribute( tmpStr )) {
		focusDecoration ->setSelBorderColor( xmlHndl->getStr( parentElement->getAttribute( tmpStr ) ) );
	}

	tmpStr = xmlHndl->getXMLCh( "transIn" );
	if (parentElement->hasAttribute( tmpStr )) {
		transitionBase = document->getTransitionBase();
		if (transitionBase != NULL) {
			std::string value;
			attValue = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );

			boost::split( transIds, attValue, boost::is_any_of( ";" ) );

			if (!transIds.empty()) {
				std::vector<std::string>::iterator i;
				i = transIds.begin();
				int j = 0;
				while (i != transIds.end()) {
					value = (*i);
					boost::trim( value );
					*i = value;
					transition = transitionBase->getTransition( value );
					if (transition != NULL) {
						descriptor->addInputTransition( transition, j );
					}
					++i;
					j++;
				}
			}

			transIds.clear();
		}
	}

	tmpStr = xmlHndl->getXMLCh( "transOut" );
	if (parentElement->hasAttribute( tmpStr )) {
		transitionBase = document->getTransitionBase();
		if (transitionBase != NULL) {
			std::string value;
			attValue = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );

			boost::split( transIds, attValue, boost::is_any_of( ";" ) );

			if (!transIds.empty()) {
				for (i = 0; i < transIds.size(); i++) {
					value = transIds[i];
					boost::trim( value );
					transition = transitionBase->getTransition( value );
					if (transition != NULL) {
						descriptor->addOutputTransition( transition, i );
					}
				}
			}

			transIds.clear();
		}
	}

	return descriptor;
}

bptnd::GenericDescriptor* NclPresentationSpecConverter::createDummyDescriptorBase(){

	bptn::NclDocument *document = static_cast<bptn::NclDocument*>( getDocumentParser()->getObject( "return", "document" ) );
	bptnd::GenericDescriptor *descriptor = document->getDescriptor( "dummyDescriptor" );

	if ( descriptor == NULL ) {
		bptnd::DescriptorBase *descBase = document->getDescriptorBase();
		if ( descBase == NULL ) {
			descBase = new bptnd::DescriptorBase( "dummyDescriptorBase" );
			document->setDescriptorBase( descBase );
		}

		bptnl::LayoutRegion *region = ((NclDocumentConverter*)getDocumentParser())->getLayoutParser()->createDummyRegBase();
		descriptor = new bptnd::Descriptor( "dummyDescriptor" );
		((bptnd::Descriptor*)descriptor)->setRegion( region );


		addDescriptorToDescriptorBase(descBase, descriptor);
	}

	return descriptor;
}

}
}
}
}
}
