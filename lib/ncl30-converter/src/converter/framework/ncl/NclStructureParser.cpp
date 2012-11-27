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

#include "../../../../include/framework/ncl/NclStructureParser.h"
#include "../../../../include/framework/ncl/NclComponentsParser.h"
#include "../../../../include/framework/ncl/NclPresentationControlParser.h"
#include "../../../../include/framework/ncl/NclInterfacesParser.h"
#include "../../../../include/framework/ncl/NclImportParser.h"
#include "../../../../include/framework/ncl/NclLayoutParser.h"
#include "../../../../include/framework/ncl/NclTransitionParser.h"
#include "../../../../include/framework/ncl/NclPresentationSpecificationParser.h"
#include "../../../../include/framework/ncl/NclConnectorsParser.h"
#include "../../../../include/framework/ncl/NclMetainformationParser.h"
#include "../../../../include/framework/XMLChHandler.h"

namespace br {
namespace pucrio {
namespace telemidia {
namespace converter {
namespace framework {
namespace ncl {
NclStructureParser::NclStructureParser( DocumentParser *documentParser ) :
		ModuleParser( documentParser ) {

}

void *NclStructureParser::parseBody( DOMElement *parentElement ) {

	void *parentObject;
	DOMNodeList *elementNodeList;
	int i, size;
	DOMNode *node;
	DOMElement *element;
	std::string elementTagName;
	void *elementObject;

	parentObject = createBody( parentElement );
	if (parentObject == NULL) {
		return NULL;
	}

	elementNodeList = parentElement->getChildNodes();
	size = elementNodeList->getLength();

	for (i = 0; i < size; i++) {
		node = elementNodeList->item( i );
		if (node->getNodeType() == DOMNode::ELEMENT_NODE) {
			element = (DOMElement*) node;
			elementTagName = getXmlHandler()->getStr( element->getTagName() );
			if (elementTagName.compare( "media" ) == 0) {

				elementObject = getComponentsParser()->parseMedia( element );

				if (elementObject != NULL) {
					addMediaToBody( parentObject, elementObject );
				}
			} else if (elementTagName.compare( "context" ) == 0) {

				elementObject = getComponentsParser()->parseContext( element );

				if (elementObject != NULL) {
					addContextToBody( parentObject, elementObject );
				}
			} else if (elementTagName.compare( "switch" ) == 0) {

				elementObject = getPresentationControlParser()->parseSwitch( element );

				if (elementObject != NULL)
					addSwitchToBody( parentObject, elementObject );
			}
		}
	}

	for (i = 0; i < size; i++) {
		node = elementNodeList->item( i );
		const XMLCh* tmpStr = getXmlHandler()->getXMLCh( "property" );
		if (node->getNodeType() == DOMNode::ELEMENT_NODE && XMLString::compareIString( ((DOMElement*) node)->getTagName(), tmpStr ) == 0) {

			elementObject = getInterfacesParser()->parseProperty( (DOMElement*) node );

			if (elementObject != NULL) {
				addPropertyToBody( parentObject, elementObject );
			}
		}
	}

	return parentObject;
}

void *NclStructureParser::posCompileBody( DOMElement *parentElement, void *parentObject ) {

	return getComponentsParser()->posCompileContext( parentElement, static_cast<bptnc::ContextNode*>(parentObject));
}

void *NclStructureParser::parseHead( DOMElement *parentElement ) {

	void *parentObject = NULL;
	DOMNodeList *elementNodeList;
	int i, size;
	DOMNode *node;
	void *elementObject = NULL;
	std::string elementTagName;
	DOMElement *element;

	parentObject = createHead( parentElement );
	if (parentObject == NULL) {
		return NULL;
	}

	elementNodeList = parentElement->getChildNodes();
	size = elementNodeList->getLength();

	for (i = 0; i < size; i++) {
		node = elementNodeList->item( i );
		if (node->getNodeType() == DOMNode::ELEMENT_NODE) {
			element = (DOMElement*) node;
			elementTagName = getXmlHandler()->getStr( element->getTagName() );
			if (elementTagName.compare( "importedDocumentBase" ) == 0) {
				elementObject = getImportParser()->parseImportedDocumentBase( element );
				if (elementObject == NULL)
					return NULL;
			} else if (elementTagName.compare( "regionBase" ) == 0) {
				elementObject = getLayoutParser()->parseRegionBase( element );
				if (elementObject != NULL)
					addRegionBaseToHead( elementObject );
				else
					return NULL;
			} else if (elementTagName.compare( "ruleBase" ) == 0) {
				elementObject = getPresentationControlParser()->parseRuleBase( element );
				if (elementObject != NULL)
					addRuleBaseToHead( elementObject );
			} else if (elementTagName.compare( "transitionBase" ) == 0) {
				elementObject = getTransitionParser()->parseTransitionBase( element );
				if (elementObject != NULL)
					addTransitionBaseToHead( elementObject );
			} else if (elementTagName.compare( "descriptorBase" ) == 0) {
				elementObject = getPresentationSpecificationParser()->parseDescriptorBase( element );
				if (elementObject != NULL)
					addDescriptorBaseToHead( elementObject );
			} else if (elementTagName.compare( "connectorBase" ) == 0) {
				elementObject = getConnectorsParser()->parseConnectorBase( element );
				if (elementObject != NULL)
					addConnectorBaseToHead( elementObject );
			} else if (elementTagName.compare( "meta" ) == 0) {
				elementObject = getMetainformationParser()->parseMeta( element );
				if (elementObject != NULL)
					addMetaToHead( elementObject );
			} else if (elementTagName.compare( "metadata" ) == 0) {
				elementObject = getMetainformationParser()->parseMetadata();
				if (elementObject != NULL)
					addMetadataToHead( elementObject );
			}
		}
	}

	return parentObject;
}

void *NclStructureParser::parseNcl( DOMElement *parentElement ) {

	void *parentObject = NULL;
	DOMNodeList *elementNodeList;
	int i, size;
	DOMNode *node;

	parentObject = createNcl( parentElement );
	if (parentObject == NULL) {
		return NULL;
	}

	elementNodeList = parentElement->getChildNodes();
	size = elementNodeList->getLength();

	for (i = 0; i < size; i++) {
		node = elementNodeList->item( i );
		if (node->getNodeType() == DOMNode::ELEMENT_NODE && XMLString::compareIString( ((DOMElement*) node)->getTagName(), getXmlHandler()->getXMLCh( "head" ) ) == 0) {

			void *elementObject = parseHead( (DOMElement*) node );
			if (elementObject != NULL) {
				break;
			} else
				return NULL;
		}
	}

	for (i = 0; i < size; i++) {
		node = elementNodeList->item( i );
		if (node->getNodeType() == DOMNode::ELEMENT_NODE && XMLString::compareIString( ((DOMElement*) node)->getTagName(), getXmlHandler()->getXMLCh( "body" ) ) == 0) {

			void *elementObject = parseBody( (DOMElement*) node );
			if (elementObject != NULL) {
				posCompileBody( (DOMElement*) node, elementObject );
				break;
			} else
				return NULL;
		}

	}
	return parentObject;
}

NclTransitionParser* NclStructureParser::getTransitionParser() {
	return transitionParser;
}

void NclStructureParser::setTransitionParser( NclTransitionParser* transitionParser ) {

	this->transitionParser = transitionParser;
}

NclPresentationSpecificationParser *NclStructureParser::getPresentationSpecificationParser() {

	return presentationSpecificationParser;
}

void NclStructureParser::setPresentationSpecificationParser( NclPresentationSpecificationParser * presentationSpecificationParser ) {

	this->presentationSpecificationParser = presentationSpecificationParser;
}

NclComponentsParser *NclStructureParser::getComponentsParser() {
	return componentsParser;
}

void NclStructureParser::setComponentsParser( NclComponentsParser *componentsParser ) {

	this->componentsParser = componentsParser;
}

NclLinkingParser *NclStructureParser::getLinkingParser() {
	return linkingParser;
}

void NclStructureParser::setLinkingParser( NclLinkingParser *linkingParser ) {

	this->linkingParser = linkingParser;
}

NclLayoutParser *NclStructureParser::getLayoutParser() {
	return layoutParser;
}

void NclStructureParser::setLayoutParser( NclLayoutParser *layoutParser ) {

	this->layoutParser = layoutParser;
}

NclMetainformationParser*
NclStructureParser::getMetainformationParser() {

	return metainformationParser;
}

NclInterfacesParser *NclStructureParser::getInterfacesParser() {
	return interfacesParser;
}

void NclStructureParser::setInterfacesParser( NclInterfacesParser *interfacesParser ) {

	this->interfacesParser = interfacesParser;
}

NclPresentationControlParser *NclStructureParser::getPresentationControlParser() {

	return presentationControlParser;
}

void NclStructureParser::setPresentationControlParser( NclPresentationControlParser *presentationControlParser ) {

	this->presentationControlParser = presentationControlParser;
}

NclConnectorsParser *NclStructureParser::getConnectorsParser() {
	return connectorsParser;
}

void NclStructureParser::setConnectorsParser( NclConnectorsParser *connectorsParser ) {

	this->connectorsParser = connectorsParser;
}

NclImportParser *NclStructureParser::getImportParser() {
	return importParser;
}

void NclStructureParser::setImportParser( NclImportParser *importParser ) {

	this->importParser = importParser;
}

void NclStructureParser::setMetainformationParser( NclMetainformationParser* metainformationParser ) {

	this->metainformationParser = metainformationParser;
}
}
}
}
}
}
}
