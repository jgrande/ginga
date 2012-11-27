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

#include "../../../include/ncl/NclLinkingConverter.h"
#include "../../../include/framework/XMLChHandler.h"
#include "../../../include/framework/DocumentParser.h"
#include <ncl30/connectors/CompoundCondition.h>
#include <ncl30/connectors/AssessmentStatement.h>
#include <ncl30/connectors/AttributeAssessment.h>
#include <ncl30/connectors/ValueAssessment.h>
#include <ncl30/connectors/EventUtil.h>
#include <ncl30/connectors/Role.h>
#include <ncl30/connectors/CausalConnector.h>
#include <ncl30/util/Comparator.h>
#include <ncl30/descriptor/GenericDescriptor.h>
#include <ncl30/link/Bind.h>
#include <ncl30/link/Link.h>
#include <ncl30/link/CausalLink.h>
#include <ncl30/components/Node.h>
#include <ncl30/components/NodeEntity.h>
#include <ncl30/components/CompositeNode.h>
#include <ncl30/NclDocument.h>
#include <ncl30/Parameter.h>
#include <ncl30/interfaces/InterfacePoint.h>
#include <ncl30/interfaces/Port.h>
#include <ncl30/interfaces/Anchor.h>
#include <util/log.h>
#include <iostream>

namespace bptn = ::br::pucrio::telemidia::ncl;
namespace bptnli = ::br::pucrio::telemidia::ncl::link;
namespace bptnd = ::br::pucrio::telemidia::ncl::descriptor;
namespace bptni = ::br::pucrio::telemidia::ncl::interfaces;

namespace br {
namespace pucrio {
namespace telemidia {
namespace converter {
namespace ncl {
NclLinkingConverter::NclLinkingConverter( bptcf::DocumentParser *documentParser ) :
		NclLinkingParser( documentParser ) {

}

void NclLinkingConverter::addBindToLink( void* /*parentObject*/, void* /*childObject*/ ) {

	// nothing to do, since to be created the bind needs to be associated
	// with
	// its link
}

void NclLinkingConverter::addBindParamToBind( void *parentObject, void *childObject ) {

	((bptnli::Bind*) parentObject)->addParameter( (bptn::Parameter*) childObject );
}

void NclLinkingConverter::addLinkParamToLink( void *parentObject, void *childObject ) {

	((bptnli::Link*) parentObject)->addParameter( (bptn::Parameter*) childObject );
}

void *NclLinkingConverter::createBind( DOMElement *parentElement, void *objGrandParent ) {

	std::string roleId;
	bptncon::Role* role;
	bptnc::Node* anchorNode;
	bptnc::NodeEntity* anchorNodeEntity;
	bptni::InterfacePoint* interfacePoint;
	bptn::NclDocument* document;
	bptnd::GenericDescriptor* descriptor;
	XMLCh* tmpStr;
	std::string tmpChar;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	// papel
	tmpStr = xmlHndl->getXMLCh( "role" );
	tmpChar = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );
	role = connector->getRole( tmpChar.c_str() );

	// no' ancora do bind
	tmpStr = xmlHndl->getXMLCh( "component" );
	std::string componentChar = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );

	if (componentChar == composite->getId()) {
		anchorNode = (bptnc::Node*) composite;

	} else {
		anchorNode = (bptnc::Node*) (composite->getNode( componentChar ));
	}

	// TODO - verificar erro na autoria
	if (anchorNode == NULL) {
		LWARN("NclLinkingConverter", "anchorNode is NULL for component '%s'", componentChar.c_str());
		return NULL;
	}

	anchorNodeEntity = (bptnc::NodeEntity*) (anchorNode->getDataEntity());

	// ponto de interface do bind
	// testa se o bind define uma interface
	tmpStr = xmlHndl->getXMLCh( "interface" );
	if (parentElement->hasAttribute( tmpStr )) {
		if (anchorNodeEntity == NULL) {
			interfacePoint = NULL;

		} else {
			tmpChar = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );
			interfacePoint = anchorNodeEntity->getAnchor( tmpChar );
		}

		if (interfacePoint == NULL) {
			tmpChar = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );
			if (anchorNodeEntity != NULL && anchorNodeEntity->instanceOf( "CompositeNode" )) {

				bptni::Port *tempPort = (static_cast<bptnc::CompositeNode*>( anchorNodeEntity ))->getPort( tmpChar );
				interfacePoint = dynamic_cast<bptni::InterfacePoint*>( tempPort );
			} else {
				interfacePoint = anchorNode->getAnchor( tmpChar );
			}

			if (interfacePoint == NULL) {
				return NULL;
			}
		}

	} else if (anchorNodeEntity != NULL) {
		// se nao houver interface, faz bind para a ancora lambda
		interfacePoint = anchorNodeEntity->getAnchor( 0 );

	} else {
		// se nao houver interface, faz bind para a ancora lambda
		interfacePoint = anchorNode->getAnchor( 0 );
	}

	// atribui o bind ao elo (link)
	tmpStr = xmlHndl->getXMLCh( "descriptor" );
	if (parentElement->hasAttribute( tmpStr )) {
		document = (bptn::NclDocument*) getDocumentParser()->getObject( "return", "document" );
		std::string str2 = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );
		descriptor = document->getDescriptor( str2.c_str() );
	} else {
		descriptor = NULL;
	}

	if (role == NULL) {
		// &got
		tmpStr = xmlHndl->getXMLCh( "role" );
		if (parentElement->hasAttribute( tmpStr )) {
			bptncon::ConditionExpression* condition;
			bptncon::CompoundCondition* compoundCondition;
			bptncon::AssessmentStatement* statement;
			bptncon::AttributeAssessment* assessment;
			bptncon::ValueAssessment* otherAssessment;

			roleId = xmlHndl->getStr( parentElement->getAttribute( tmpStr ) );

			assessment = new bptncon::AttributeAssessment( roleId );
			assessment->setEventType( bptncon::EventUtil::EVT_ATTRIBUTION );
			assessment->setAttributeType( bptncon::EventUtil::ATT_NODE_PROPERTY );
			assessment->setMinCon( 0 );
			assessment->setMaxCon( bptncon::Role::UNBOUNDED );

			otherAssessment = new bptncon::ValueAssessment( roleId );

			statement = new bptncon::AssessmentStatement( ncl_util::Comparator::CMP_NE );
			statement->setMainAssessment( assessment );
			statement->setOtherAssessment( otherAssessment );

			condition = ((bptncon::CausalConnector*) connector)->getConditionExpression();

			if (condition->instanceOf( "CompoundCondition" )) {
				((bptncon::CompoundCondition*) condition)->addConditionExpression( statement );

			} else {
				compoundCondition = new bptncon::CompoundCondition( condition, statement, bptncon::CompoundCondition::OP_OR );

				((bptncon::CausalConnector*) connector)->setConditionExpression( (bptncon::ConditionExpression*) compoundCondition );
			}
			role = (bptncon::Role*) assessment;

		} else {
			return NULL;
		}
	}

	return ((bptnli::Link*) objGrandParent)->bind( anchorNode, interfacePoint, descriptor, role->getLabel() );
}

void *NclLinkingConverter::createLink( DOMElement *parentElement, void *objGrandParent ) {

	bptn::NclDocument *document;
	bptnli::Link *link;

	// obtendo o conector do link
	document = (bptn::NclDocument*) getDocumentParser()->getObject( "return", "document" );

	XMLCh* tmpStr = getXmlHandler()->getXMLCh( "xconnector" );
	std::string tmpChar = getXmlHandler()->getStr( parentElement->getAttribute( tmpStr ) );

	connector = document->getConnector( tmpChar.c_str() );

	if (connector == NULL) {
		// connector not found
		return NULL;
	}

	// criando o link
	if (connector->instanceOf( "CausalConnector" )) {
		link = new bptnli::CausalLink( getId( parentElement ), connector );

	} else {
		link = NULL;
	}

	composite = (bptnc::CompositeNode*) objGrandParent;
	return link;
}

void *NclLinkingConverter::createBindParam( DOMElement *parentElement ) {

	bptn::Parameter *parameter;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	XMLCh *nameXMLChar = xmlHndl->getXMLCh( "name" );
	std::string nameParam = xmlHndl->getStr( parentElement->getAttribute( nameXMLChar ) );

	XMLCh *valueXmlChar = xmlHndl->getXMLCh( "value" );
	std::string valueParam = xmlHndl->getStr( parentElement->getAttribute( valueXmlChar ) );

	parameter = new bptn::Parameter( nameParam, valueParam );

	return parameter;
}

void *NclLinkingConverter::createLinkParam( DOMElement *parentElement ) {

	bptn::Parameter *parameter;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	XMLCh *nameXMLChar = xmlHndl->getXMLCh( "name" );
	std::string nameParam = xmlHndl->getStr( parentElement->getAttribute( nameXMLChar ) );

	XMLCh *valueXmlChar = xmlHndl->getXMLCh( "value" );
	std::string valueParam = xmlHndl->getStr( parentElement->getAttribute( valueXmlChar ) );

	parameter = new bptn::Parameter( nameParam, valueParam );

	return parameter;
}

std::string NclLinkingConverter::getId( DOMElement *element ) {
	std::string strRet = "";
	XMLCh* tmpStr = getXmlHandler()->getXMLCh( "id" );
	if (element->hasAttribute( tmpStr )) {
		strRet = getXmlHandler()->getStr( element->getAttribute( tmpStr ) );
	} else {
		strRet = "";		//"NclLinkingConverterId" + idCount++;
	}
	return strRet;

}
}
}
}
}
}
