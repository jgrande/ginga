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

#include "../../../include/ncl/NclInterfacesConverter.h"
#include "../../../include/ncl/NclDocumentConverter.h"
#include "../../../include/framework/XMLChHandler.h"
#include <ncl30/components/Node.h>
#include <ncl30/components/CompositeNode.h>
#include <ncl30/components/NodeEntity.h>
#include <ncl30/interfaces/PropertyAnchor.h>
#include <ncl30/interfaces/InterfacePoint.h>
#include <ncl30/interfaces/RectangleSpatialAnchor.h>
#include <ncl30/interfaces/SampleIntervalAnchor.h>
#include <ncl30/interfaces/TextAnchor.h>
#include <ncl30/interfaces/LabeledAnchor.h>
#include <ncl30/interfaces/Port.h>
#include <ncl30/interfaces/IntervalAnchor.h>
#include <ncl30/interfaces/RelativeTimeIntervalAnchor.h>
#include <ncl30/interfaces/ContentAnchor.h>
#include <ncl30/interfaces/SwitchPort.h>
#include <ncl30/switches/SwitchNode.h>
#include <util/log.h>
#include <boost/lexical_cast.hpp>
#include <cstdio>

namespace bptnc = ::br::pucrio::telemidia::ncl::components;
namespace bptni = ::br::pucrio::telemidia::ncl::interfaces;
namespace bptns = ::br::pucrio::telemidia::ncl::switches;

namespace br {
namespace pucrio {
namespace telemidia {
namespace converter {
namespace ncl {
NclInterfacesConverter::NclInterfacesConverter( bptcf::DocumentParser *documentParser ) :
		NclInterfacesParser( documentParser ) {

}

void *NclInterfacesConverter::createPort( DOMElement* parentElement, void *objGrandParent ) {

	std::string id, attValue;
	bptnc::Node *portNode;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	bptnc::CompositeNode *context = (bptnc::CompositeNode*) objGrandParent;
	
	id = xmlHndl->getStr( parentElement->getAttribute(xmlHndl->getXMLCh("id")));
	if (id.empty()) {
		LERROR("NclInterfacesConverter", "a port element was declared without an id attribute.");
		return NULL;
	}

	if (context->getPort( id ) != NULL) {
		LERROR("NclInterfacesConverter", "a port already exists with the same id=%s in context=%s", id.c_str(), context->getId().c_str());
		return NULL;
	}

	attValue = xmlHndl->getStr(parentElement->getAttribute(xmlHndl->getXMLCh("component")));
	if (attValue.empty()) {
		LERROR("NclInterfacesConverter", "%s port must refer a context component using component attribute", id.c_str());
		return NULL;
	}
	
	portNode = context->getNode(attValue);
	if (portNode == NULL) {
		LERROR("NclInterfacesConverter", "Composition does not contain the referenced component=%s", attValue.c_str());
		return NULL;
	}

	bptnc::NodeEntity *portNodeEntity = static_cast<bptnc::NodeEntity*>(portNode->getDataEntity());
	bptni::InterfacePoint *portInterfacePoint = NULL;

// 	component = ;
	attValue = xmlHndl->getStr(parentElement->getAttribute(xmlHndl->getXMLCh("interface")));
	if (attValue.empty()) {
		// port element nao tem o atributo port, logo pegar a
		// ancora lambda do docment node->
		portInterfacePoint = portNodeEntity->getAnchor( 0 );

	} else {
		// tem-se o atributo port
		// tentar pegar a ancora do document node
		

		portInterfacePoint = portNodeEntity->getAnchor(attValue);
		if (portInterfacePoint == NULL && portNodeEntity->instanceOf( "CompositeNode" )) {

			// the interface may refer to a composition port and instead of
			// an anchor
			portInterfacePoint = ((bptnc::CompositeNode*) portNodeEntity)->getPort( attValue );
		}
	}

	if (portInterfacePoint == NULL) {
		LERROR("NclInterfacesConverter", "The referenced %s  component does not contain the referenced %s interface", portNode->getId().c_str(), attValue.c_str());
		return NULL;
	}
	
	bptni::Port *port = new bptni::Port( id, portNode, portInterfacePoint );
	return port;
}

bptni::SpatialAnchor *NclInterfacesConverter::createSpatialAnchor( DOMElement *areaElement ) {

	bptni::SpatialAnchor *anchor = NULL;
	std::string coords, shape;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	coords = xmlHndl->getStr(areaElement->getAttribute(xmlHndl->getXMLCh("coords")));
	if (!coords.empty()){
		
		shape = xmlHndl->getStr(areaElement->getAttribute(xmlHndl->getXMLCh("shape")));
		if (shape.empty()) {
			shape = "rect";
		}

		if (shape == "rect" || shape == "default") {
			long int x1, y1, x2, y2;
			std::sscanf( coords.c_str(), "%ld,%ld,%ld,%ld", &x1, &y1, &x2, &y2 );
			anchor = new bptni::RectangleSpatialAnchor( xmlHndl->getStr( areaElement->getAttribute( xmlHndl->getXMLCh( "id" ) ) ), x1, y1, x2 - x1, y2 - y1 );

		} else if (shape == "circle") {
			// TODO
		} else if (shape == "poly") {
			// TODO
		}
	}
	return anchor;
}

bptni::IntervalAnchor *NclInterfacesConverter::createTemporalAnchor( DOMElement *areaElement ) {

	bptni::IntervalAnchor *anchor = NULL;
	std::string begin, end;
	double begVal, endVal;
	short firstSyntax, lastSyntax;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	if (areaElement->hasAttribute( xmlHndl->getXMLCh( "begin" ) ) || areaElement->hasAttribute( xmlHndl->getXMLCh( "end" ) )) {

		if (areaElement->hasAttribute( xmlHndl->getXMLCh( "begin" ) )) {
			begin = xmlHndl->getStr( areaElement->getAttribute( xmlHndl->getXMLCh( "begin" ) ) );

			if (begin[begin.length() - 1] == 's') {
				begin = begin.substr( 0, begin.length() - 1 );
			}
			begVal = boost::lexical_cast<float>( begin ) * 1000;

		} else {
			begVal = 0;
		}

		if (areaElement->hasAttribute( xmlHndl->getXMLCh( "end" ) )) {
			end = xmlHndl->getStr( areaElement->getAttribute( xmlHndl->getXMLCh( "end" ) ) );

			if (end[end.length() - 1] == 's') {
				end = end.substr( 0, end.length() - 1 );
			}
			endVal = boost::lexical_cast<float>( end ) * 1000;

		} else {
			endVal = bptni::IntervalAnchor::OBJECT_DURATION;
		}
		anchor = new bptni::RelativeTimeIntervalAnchor( xmlHndl->getStr( areaElement->getAttribute( xmlHndl->getXMLCh( "id" ) ) ), begVal, endVal );
	}

	// region delimeted through sample identifications
	if (areaElement->hasAttribute( xmlHndl->getXMLCh( "first" ) ) || areaElement->hasAttribute( xmlHndl->getXMLCh( "last" ) )) {

		begVal = 0;
		endVal = bptni::IntervalAnchor::OBJECT_DURATION;
		firstSyntax = bptni::ContentAnchor::CAT_NPT;
		lastSyntax = bptni::ContentAnchor::CAT_NPT;

		if (areaElement->hasAttribute( xmlHndl->getXMLCh( "first" ) )) {
			begin = xmlHndl->getStr( areaElement->getAttribute( xmlHndl->getXMLCh( "first" ) ) );

			if (begin.find( "s" ) != std::string::npos) {
				firstSyntax = bptni::ContentAnchor::CAT_SAMPLES;
				begVal = boost::lexical_cast<float>( begin.substr( 0, begin.length() - 1 ) );

			} else if (begin.find( "f" ) != std::string::npos) {
				firstSyntax = bptni::ContentAnchor::CAT_FRAMES;
				begVal = boost::lexical_cast<float>( begin.substr( 0, begin.length() - 1 ) );

			} else if (begin.find( "npt" ) != std::string::npos) {
				firstSyntax = bptni::ContentAnchor::CAT_NPT;
				begVal = boost::lexical_cast<float>( begin.substr( 0, begin.length() - 3 ) );
			}
		}

		if (areaElement->hasAttribute( xmlHndl->getXMLCh( "last" ) )) {
			end = xmlHndl->getStr( areaElement->getAttribute( xmlHndl->getXMLCh( "last" ) ) );

			if (begin.find( "s" ) != std::string::npos) {
				lastSyntax = bptni::ContentAnchor::CAT_SAMPLES;
				endVal = boost::lexical_cast<float>( end.substr( 0, end.length() - 1 ) );

			} else if (begin.find( "f" ) != std::string::npos) {
				lastSyntax = bptni::ContentAnchor::CAT_FRAMES;
				endVal = boost::lexical_cast<float>( end.substr( 0, end.length() - 1 ) );

			} else if (begin.find( "npt" ) != std::string::npos) {
				lastSyntax = bptni::ContentAnchor::CAT_NPT;
				endVal = boost::lexical_cast<float>( end.substr( 0, end.length() - 3 ) );
			}
		}

		anchor = new bptni::SampleIntervalAnchor( xmlHndl->getStr( areaElement->getAttribute( xmlHndl->getXMLCh( "id" ) ) ), begVal, endVal );

		((bptni::SampleIntervalAnchor*) anchor)->setValueSyntax( firstSyntax, lastSyntax );

	}
	return anchor;
}

void *NclInterfacesConverter::createProperty( DOMElement *parentElement ) {

	std::string attributeName, attributeValue;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	attributeName = xmlHndl->getStr( parentElement->getAttribute(xmlHndl->getXMLCh("name")));
	if (attributeName.empty()) {
		LERROR("NclInterfacesConverter", "A property element=%s was declared without a name attribute", xmlHndl->getStr( parentElement->getTagName() ).c_str());
		return NULL;
	}

	bptni::PropertyAnchor *anchor = new bptni::PropertyAnchor(attributeName);

	attributeValue = xmlHndl->getStr( parentElement->getAttribute(xmlHndl->getXMLCh("value")));
	if (! attributeValue.empty()){
		anchor->setPropertyValue(attributeValue);
	}
	return anchor;
}

void *NclInterfacesConverter::createArea( DOMElement *parentElement ) {

	std::string anchorId;
	std::string position, anchorLabel;
	bptni::Anchor *anchor = NULL;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	anchorId = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh("id"))) ;
	if (anchorId.empty()) {
		LERROR("NclInterfacesConverter", "A media interface element=%s was declared without an id attribute", (xmlHndl->getStr(parentElement->getTagName())).c_str());
		return NULL;
	}

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "begin" ) ) || parentElement->hasAttribute( xmlHndl->getXMLCh( "end" ) ) || parentElement->hasAttribute( xmlHndl->getXMLCh( "first" ) )
	        || parentElement->hasAttribute( xmlHndl->getXMLCh( "last" ) )) {

		anchor = createTemporalAnchor( parentElement );

		// ancora textual
	} else if (parentElement->hasAttribute( xmlHndl->getXMLCh( "text" ) )) {
		position = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "position" ) ) );

		anchor = new bptni::TextAnchor( anchorId, xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "text" ) ) ), atoi( position.c_str() ) );

	} else if (parentElement->hasAttribute( xmlHndl->getXMLCh( "coords" ) )) {

		anchor = createSpatialAnchor( parentElement );

	} else if (parentElement->hasAttribute( xmlHndl->getXMLCh( "label" ) )) {

		anchorLabel = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "label" ) ) );

		anchor = new bptni::LabeledAnchor( anchorId, anchorLabel );

	} else {
		anchor = new bptni::LabeledAnchor( anchorId, anchorId );
	}

	if (anchor == NULL) {
		LERROR("NclInterfacesConverter", "error on createArea");
		return NULL;
	}

	return anchor;
}

bptni::Port *NclInterfacesConverter::createMapping( DOMElement *parentElement, bptni::SwitchPort *objGrandParent ) {

	DOMElement *switchElement;
	bptns::SwitchNode *switchNode;
	bptnc::NodeEntity *mappingNodeEntity;
	bptnc::Node *mappingNode;
	bptni::InterfacePoint *interfacePoint;
	bptni::Port *port;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	switchElement = (DOMElement*) parentElement->getParentNode()->getParentNode();

	switchNode = (bptns::SwitchNode*) ((NclDocumentConverter*) getDocumentParser())->getNode( xmlHndl->getStr( switchElement->getAttribute( xmlHndl->getXMLCh( "id" ) ) ) );

	std::string componentValue = xmlHndl->getStr(parentElement->getAttribute(xmlHndl->getXMLCh("component")));
	mappingNode = switchNode->getNode(componentValue);

	if (mappingNode == NULL) {
		LERROR("NclInterfacesConverter", "A mapping element points to a node (%s) not contained by the %s switch", componentValue.c_str(), switchNode->getId().c_str());
		return NULL;
	}

	mappingNodeEntity = (bptnc::NodeEntity*) mappingNode->getDataEntity();
	std::string interfaceValue = xmlHndl->getStr(parentElement->getAttribute(xmlHndl->getXMLCh("interface")));
	if (! interfaceValue.empty()) {
		// tem-se o atributo, tentar pegar a ancora do document node
		interfacePoint = mappingNodeEntity->getAnchor(interfaceValue);

		if (interfacePoint == NULL) {
			// ou o document node era um terminal node e nao
			// possuia a ancora (erro), ou port indicava uma porta em uma
			// composicao
			if (mappingNodeEntity->instanceOf( "CompositeNode" )) {
				interfacePoint = ((bptnc::CompositeNode*) mappingNodeEntity)->getPort(interfaceValue);
			}
		}

	} else {
		// port element nao tem o atributo port, logo pegar a
		// ancora lambda do no->
		interfacePoint = mappingNodeEntity->getAnchor( 0 );
	}

	if (interfacePoint == NULL) {
		LERROR("NclInterfacesConverter", "a mapping element points to a node interface (%s) not contained by the %s node", interfaceValue.c_str(), mappingNode->getId().c_str());
		return NULL;
	}

	port = new bptni::Port(objGrandParent->getId(), mappingNode, interfacePoint);

	return port;
}

bptni::SwitchPort *NclInterfacesConverter::createSwitchPort( DOMElement *parentElement, void *objGrandParent ) {

	bptns::SwitchNode *switchNode;
	bptni::SwitchPort *switchPort;
	std::string id;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	switchNode = (bptns::SwitchNode*) objGrandParent;

	id = xmlHndl->getStr(parentElement->getAttribute(xmlHndl->getXMLCh("id")));
	if (id.empty()) {
		LERROR("NclInterfacesConverter", "the switch port element was declared without an id attribute.");
		return NULL;
	}

	if (switchNode->getPort( id ) != NULL) {
		LERROR("NclInterfacesConverter", "a port already exists with the same %s id in %s context", id.c_str(), switchNode->getId().c_str());
		return NULL;
	}

	switchPort = new bptni::SwitchPort( id, switchNode );
	return switchPort;
}

void NclInterfacesConverter::addMappingToSwitchPort(bptni::SwitchPort *parentObject, bptni::Port *childObject) {

	parentObject->addPort(childObject);
}

}
}
}
}
}
