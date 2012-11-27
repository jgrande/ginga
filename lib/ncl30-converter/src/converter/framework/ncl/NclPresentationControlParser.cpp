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

#include "../../../../include/framework/ncl/NclPresentationControlParser.h"
#include "../../../../include/framework/ncl/NclComponentsParser.h"
#include "../../../../include/framework/ncl/NclImportParser.h"
#include "../../../../include/framework/ncl/NclInterfacesParser.h"
#include "../../../../include/framework/ncl/NclPresentationSpecificationParser.h"
#include "../../../../include/framework/XMLChHandler.h"

namespace br {
namespace pucrio {
namespace telemidia {
namespace converter {
namespace framework {
namespace ncl {
NclPresentationControlParser::NclPresentationControlParser( DocumentParser *documentParser ) :
		ModuleParser( documentParser ) {

}

void *NclPresentationControlParser::parseBindRule( DOMElement *parentElement ) {
	return createBindRule( parentElement );
}

void *NclPresentationControlParser::parseRuleBase( DOMElement *parentElement ) {
	void *parentObject;
	DOMNodeList *elementNodeList;
	DOMElement *element;
	DOMNode *node;
	std::string elementTagName;
	void *elementObject;

	parentObject = createRuleBase( parentElement );
	if (parentObject == NULL) {
		return NULL;
	}

	XMLChHandler *xmlHndl = getXmlHandler();

	elementNodeList = parentElement->getChildNodes();
	for (int i = 0; i < (int) elementNodeList->getLength(); i++) {
		node = elementNodeList->item( i );
		if (node->getNodeType() == DOMNode::ELEMENT_NODE) {
			element = (DOMElement*) node;
			elementTagName = xmlHndl->getStr( element->getTagName() );

			if (elementTagName.compare( "importBase" ) == 0) {

				elementObject = element;

				if (elementObject != NULL) {
					addImportBaseToRuleBase( parentObject, elementObject );
				}

			} else if (elementTagName.compare( "rule" ) == 0) {

				elementObject = parseRule( element );
				if (elementObject != NULL) {
					addRuleToRuleBase( parentObject, elementObject );
				}

			} else if (elementTagName.compare( "compositeRule" ) == 0) {

				elementObject = parseCompositeRule( element );
				if (elementObject != NULL) {
					addCompositeRuleToRuleBase( parentObject, elementObject );
				}
			}
		}
	}

	return parentObject;
}

void *NclPresentationControlParser::parseRule( DOMElement *parentElement ) {
	return createRule( parentElement );
}

void *NclPresentationControlParser::parseSwitch( DOMElement *parentElement ) {

	void *parentObject;
	DOMNodeList *elementNodeList;
	int i, size;
	DOMNode *node;
	DOMElement *element;
	std::string elementTagName;
	void *elementObject;

	parentObject = createSwitch( parentElement );
	if (parentObject == NULL) {
		return NULL;
	}

	XMLChHandler *xmlHndl = getXmlHandler();

	elementNodeList = parentElement->getChildNodes();
	size = elementNodeList->getLength();

	for (i = 0; i < size; i++) {
		node = elementNodeList->item( i );
		if (node->getNodeType() == DOMNode::ELEMENT_NODE) {
			element = (DOMElement*) node;
			elementTagName = xmlHndl->getStr( element->getTagName() );
			if (elementTagName.compare( "media" ) == 0) {

				elementObject = ((NclComponentsParser*) getComponentsParser())->parseMedia( element );

				if (elementObject != NULL) {
					addMediaToSwitch( parentObject, elementObject );
				}

			} else if (elementTagName.compare( "context" ) == 0) {

				elementObject = ((NclComponentsParser*) getComponentsParser())->parseContext( element );

				if (elementObject != NULL) {
					addContextToSwitch( parentObject, elementObject );
				}

			} else if (elementTagName.compare( "switch" ) == 0) {

				elementObject = parseSwitch( element );
				if (elementObject != NULL) {
					addSwitchToSwitch( parentObject, elementObject );
				}
			}
		}
	}

	for (i = 0; i < size; i++) {
		node = elementNodeList->item( i );
		if (node->getNodeType() == DOMNode::ELEMENT_NODE) {
			element = (DOMElement*) node;
			elementTagName = xmlHndl->getStr( element->getTagName() );
			if (elementTagName.compare( "bindRule" ) == 0) {

				elementObject = parseBindRule( (DOMElement*) node );

				if (elementObject != NULL) {
					addBindRuleToSwitch( parentObject, elementObject );
				}

			} else if (elementTagName.compare( "defaultComponent" ) == 0) {

				elementObject = parseDefaultComponent( (DOMElement*) node );

				if (elementObject != NULL) {
					addDefaultComponentToSwitch( parentObject, elementObject );
				}
			}
		}
	}

	return parentObject;
}

void *NclPresentationControlParser::posCompileSwitch( DOMElement *parentElement, void *parentObject ) {

	DOMNodeList *elementNodeList;
	int i, size;
	DOMNode *node;
	void *elementObject;

	elementNodeList = parentElement->getChildNodes();
	size = elementNodeList->getLength();
	XMLChHandler *xmlHndl = getXmlHandler();

	for (i = 0; i < size; i++) {
		node = elementNodeList->item( i );
		if (node->getNodeType() == DOMNode::ELEMENT_NODE && XMLString::compareIString( ((DOMElement*) node)->getTagName(), xmlHndl->getXMLCh( "switchPort" ) ) == 0) {

			elementObject = getInterfacesParser()->parseSwitchPort( (DOMElement*) node, parentObject );

			if (elementObject != NULL) {
				addSwitchPortToSwitch( parentObject, elementObject );
			}
		}
	}

	return parentObject;
}

void *NclPresentationControlParser::parseDefaultComponent( DOMElement *parentElement ) {
	return createDefaultComponent( parentElement );
}

void *NclPresentationControlParser::parseDefaultDescriptor( DOMElement *parentElement ) {
	return createDefaultDescriptor( parentElement );
}

void *NclPresentationControlParser::parseCompositeRule( DOMElement *parentElement ) {

	void *parentObject;
	DOMNodeList *elementNodeList;
	DOMElement *element;
	DOMNode *node;
	std::string elementTagName;
	void *elementObject;

	parentObject = createCompositeRule( parentElement );
	if (parentObject == NULL) {
		return NULL;
	}

	XMLChHandler *xmlHndl = getXmlHandler();

	elementNodeList = parentElement->getChildNodes();
	for (int i = 0; i < (int) elementNodeList->getLength(); i++) {
		node = elementNodeList->item( i );
		if (node->getNodeType() == DOMNode::ELEMENT_NODE) {
			element = (DOMElement*) node;
			elementTagName = xmlHndl->getStr( element->getTagName() );

			if (elementTagName.compare( "rule" ) == 0) {

				elementObject = parseRule( element );
				if (elementObject != NULL) {
					addRuleToCompositeRule( parentObject, elementObject );
				}

			} else if (elementTagName.compare( "compositeRule" ) == 0) {

				elementObject = parseCompositeRule( element );
				if (elementObject != NULL) {
					addCompositeRuleToCompositeRule( parentObject, elementObject );
				}
			}
		}
	}

	return parentObject;
}

void *NclPresentationControlParser::parseDescriptorSwitch( DOMElement *parentElement ) {

	void *parentObject;
	DOMNodeList *elementNodeList;
	int i, size;
	DOMElement *element;
	DOMNode *node;
	std::string elementTagName;
	void *elementObject;

	parentObject = createDescriptorSwitch( parentElement );
	if (parentObject == NULL) {
		return NULL;
	}

	XMLChHandler *xmlHndl = getXmlHandler();

	elementNodeList = parentElement->getChildNodes();
	size = elementNodeList->getLength();

	for (i = 0; i < size; i++) {
		node = elementNodeList->item( i );
		if (node->getNodeType() == DOMNode::ELEMENT_NODE && XMLString::compareIString( ((DOMElement*) node)->getTagName(), xmlHndl->getXMLCh( "descriptor" ) ) == 0) {

			elementObject = getPresentationSpecificationParser()->parseDescriptor( (DOMElement*) node );

			if (elementObject != NULL) {
				addDescriptorToDescriptorSwitch( parentObject, elementObject );
			}
		}
	}

	for (i = 0; i < size; i++) {
		node = elementNodeList->item( i );
		if (node->getNodeType() == DOMNode::ELEMENT_NODE) {
			element = (DOMElement*) node;
			elementTagName = xmlHndl->getStr( element->getTagName() );
			if (elementTagName.compare( "bindRule" ) == 0) {

				elementObject = parseBindRule( (DOMElement*) node );

				if (elementObject != NULL) {
					addBindRuleToDescriptorSwitch( parentObject, elementObject );
				}

			} else if (elementTagName.compare( "defaultDescriptor" ) == 0) {

				elementObject = parseDefaultDescriptor( (DOMElement*) node );

				if (elementObject != NULL) {
					addDefaultDescriptorToDescriptorSwitch( parentObject, elementObject );
				}
			}
		}
	}

	return parentObject;
}

NclPresentationSpecificationParser*
NclPresentationControlParser::getPresentationSpecificationParser() {

	return presentationSpecificationParser;
}

void NclPresentationControlParser::setPresentationSpecificationParser( NclPresentationSpecificationParser* presentationSpecificationParser ) {

	this->presentationSpecificationParser = presentationSpecificationParser;
}

void *NclPresentationControlParser::getComponentsParser() {
	return componentsParser;
}

void NclPresentationControlParser::setComponentsParser( void *componentsParser ) {

	this->componentsParser = componentsParser;
}

NclInterfacesParser *NclPresentationControlParser::getInterfacesParser() {
	return interfacesParser;
}

void NclPresentationControlParser::setInterfacesParser( NclInterfacesParser *interfacesParser ) {

	this->interfacesParser = interfacesParser;
}

NclImportParser *NclPresentationControlParser::getImportParser() {
	return importParser;
}

void NclPresentationControlParser::setImportParser( NclImportParser *importParser ) {

	this->importParser = importParser;
}
}
}
}
}
}
}
