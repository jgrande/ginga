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

#include "../../../include/ncl/NclConnectorsConverter.h"
#include "../../../include/ncl/NclDocumentConverter.h"
#include "../../../include/framework/XMLChHandler.h"
#include "ncl30/NclDocument.h"
#include "ncl30/Parameter.h"
#include "ncl30/animation/Animation.h"
#include "ncl30/connectors/EventUtil.h"
#include "ncl30/connectors/ValueAssessment.h"
#include "ncl30/connectors/ConnectorBase.h"
#include "ncl30/connectors/CausalConnector.h"
#include "ncl30/connectors/SimpleAction.h"
#include "ncl30/connectors/SimpleCondition.h"
#include "ncl30/connectors/CompoundAction.h"
#include "ncl30/connectors/CompoundCondition.h"
#include "ncl30/connectors/CompoundStatement.h"
#include "ncl30/connectors/AttributeAssessment.h"
#include "ncl30/connectors/AssessmentStatement.h"
#include "ncl30/connectors/ConditionExpression.h"
#include "ncl30/connectors/Statement.h"
#include "ncl30/connectors/Action.h"
#include "ncl30/util/Comparator.h"
#include <util/log.h>
#include <boost/lexical_cast.hpp>

namespace bptna = ::br::pucrio::telemidia::ncl::animation;

namespace br {
namespace pucrio {
namespace telemidia {
namespace converter {
namespace ncl {
NclConnectorsConverter::NclConnectorsConverter( bptcf::DocumentParser* documentParser ) :
		NclConnectorsParser( documentParser ) {

}

void NclConnectorsConverter::addCausalConnectorToConnectorBase(bptncon::ConnectorBase *parentObject, bptncon::Connector *childObject){

	parentObject->addConnector(childObject);
}

void NclConnectorsConverter::addConnectorParamToCausalConnector(bptncon::Connector *parentObject, bptn::Parameter *childObject) {

	parentObject->addParameter(childObject);
}

void NclConnectorsConverter::addImportBaseToConnectorBase(bptncon::ConnectorBase *parentObject, DOMElement *childObject ) {

	std::string baseAlias, baseLocation;
	NclDocumentConverter *compiler;
	bptn::NclDocument *importedDocument;
	bptncon::ConnectorBase *connectorBase;
	bptcf::XMLChHandler *xmlHndl = getXmlHandler();

	// get the external base alias and location
	baseAlias = xmlHndl->getStr(childObject->getAttribute( xmlHndl->getXMLCh( "alias" ) ) );

	baseLocation = xmlHndl->getStr(childObject->getAttribute( xmlHndl->getXMLCh( "documentURI" ) ) );

	compiler = (NclDocumentConverter*) getDocumentParser();
	importedDocument = compiler->importDocument( baseLocation );
	if (importedDocument == NULL) {
		return;
	}

	connectorBase = importedDocument->getConnectorBase();
	if (connectorBase == NULL) {
		return;
	}

	// insert the imported base into the document connector base
	parentObject->addBase( connectorBase, baseAlias, baseLocation );

	/*
	 * Hashtable connBaseimports = new Hashtable();
	 * connBaseimports->put(baseAlias,baseLocation);
	 * getDocumentParser()->addObject("return","ConnectorImports",
	 * connBaseimports);
	 */
}

bptncon::CausalConnector *NclConnectorsConverter::createCausalConnector( DOMElement *parentElement ) {

	std::string connectorId = "";
	bptcf::XMLChHandler* xmlHndl = getXmlHandler();
	/*
	 * if (connectorUri->equalsIgnoreCase("")) { //se nao tiver uma uri do
	 * arquivo do conector, atribuir somente o id
	 * do elemento conector como id do conector
	 * connectorId = parentElement->getAttribute("id"); connectorId =
	 * "#" + parentElement->getAttribute("id"); } else { //atribuir a id do
	 * conector como sendo a uri do seu arquivo
	 * connectorId = connectorUri;
	 */
	connectorId = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "id" ) ) );

	bptncon::CausalConnector *connector = new bptncon::CausalConnector( connectorId );
	return connector;
}

bptncon::ConnectorBase *NclConnectorsConverter::createConnectorBase( DOMElement *parentElement ) {

	bptncon::ConnectorBase *connBase;
	bptcf::XMLChHandler* xmlHndl = getXmlHandler();
	// criar nova base de conectores com id gerado a partir do nome de seu
	// elemento
	connBase = new bptncon::ConnectorBase( xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "id" ) ) ) );

	return connBase;
}

bptn::Parameter *NclConnectorsConverter::createConnectorParam( DOMElement *parentElement ) {

	bptcf::XMLChHandler* xmlHndl = getXmlHandler();
	bptn::Parameter *parameter;
	parameter = new bptn::Parameter( xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "name" ) ) ),

	xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "type" ) ) ) );

	return parameter;
}

void NclConnectorsConverter::compileRoleInformation( bptncon::Role *role, DOMElement *parentElement ) {

	std::string attValue;
	bptcf::XMLChHandler* xmlHndl = getXmlHandler();
	// event type
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "eventType" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "eventType" ) ) );

		role->setEventType( bptncon::EventUtil::getTypeCode( attValue ) );
	}

	//  cardinality
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "min" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "min" ) ) );

		role->setMinCon( (atoi( attValue.c_str() )) );
	}

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "max" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "max" ) ) );

		if (attValue.compare( "unbounded" ) == 0) {
			role->setMaxCon( bptncon::Role::UNBOUNDED );

		} else {
			role->setMaxCon( atoi( attValue.c_str() ) );
		}
	}
}

bptncon::SimpleCondition *NclConnectorsConverter::createSimpleCondition( DOMElement *parentElement ) {

	bptncon::SimpleCondition* conditionExpression;
	std::string attValue;
	bptcf::XMLChHandler* xmlHndl = getXmlHandler();

	std::string roleLabel = xmlHndl->getStr( parentElement->getAttribute(xmlHndl->getXMLCh( "role" )));

	conditionExpression = new bptncon::SimpleCondition(roleLabel);

	compileRoleInformation(conditionExpression, parentElement);

	// transition
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "transition" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "transition" ) ) );

		conditionExpression->setTransition( bptncon::EventUtil::getTransitionCode( attValue ) );
	}

	// parametro
	if (conditionExpression->getEventType() == bptncon::EventUtil::EVT_SELECTION) {
		if (parentElement->hasAttribute( xmlHndl->getXMLCh( "key" ) )) {
			attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "key" ) ) );

			conditionExpression->setKey( attValue );
		}
	}

	// qualifier
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "qualifier" ) )) {

		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "qualifier" ) ) );

		if (attValue.compare( "or" ) == 0) {
			conditionExpression->setQualifier( bptncon::CompoundCondition::OP_OR );

		} else {
			conditionExpression->setQualifier( bptncon::CompoundCondition::OP_AND );
		}
	}

	//testar delay
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "delay" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "delay" ) ) );

		if (attValue[0] == '$') {
			conditionExpression->setDelay( attValue );

		} else {
			double delayValue;
			delayValue = boost::lexical_cast<float>( attValue.substr( 0, (attValue.length() - 1) ) ) * 1000;

			conditionExpression->setDelay( boost::lexical_cast<std::string>( delayValue ) );
		}
	}

	// retornar expressao de condicao
	return conditionExpression;
}

bptncon::CompoundCondition *NclConnectorsConverter::createCompoundCondition( DOMElement *parentElement ) {

	bptncon::CompoundCondition *conditionExpression;
	std::string attValue;
	bptcf::XMLChHandler* xmlHndl = getXmlHandler();

	conditionExpression = new bptncon::CompoundCondition();

	if ((xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "operator" ) ) )).compare( "and" ) == 0) {

		conditionExpression->setOperator( bptncon::CompoundCondition::OP_AND );

	} else {
		conditionExpression->setOperator( bptncon::CompoundCondition::OP_OR );
	}

	//  testar delay
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "delay" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "delay" ) ) );

		if (attValue[0] == '$') {
			conditionExpression->setDelay( attValue );

		} else {
			double delayValue = boost::lexical_cast<float>( attValue.substr( 0, (attValue.length() - 1) ) ) * 1000;

			conditionExpression->setDelay( boost::lexical_cast<std::string>( delayValue ) );
		}
	}

	// retornar expressao de condicao
	return conditionExpression;
}

bptncon::AttributeAssessment* NclConnectorsConverter::createAttributeAssessment( DOMElement *parentElement ) {

	bptncon::AttributeAssessment *attributeAssessment;
	std::string attValue;
	bptcf::XMLChHandler* xmlHndl = getXmlHandler();

	std::string roleLabel;
	roleLabel = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "role" ) ) );

	attributeAssessment = new bptncon::AttributeAssessment( roleLabel );

	// event type
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "eventType" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "eventType" ) ) );

		attributeAssessment->setEventType( bptncon::EventUtil::getTypeCode( attValue ) );
	}

	// event type
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "attributeType" ) )) {

		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "attributeType" ) ) );

		attributeAssessment->setAttributeType( bptncon::EventUtil::getAttributeTypeCode( attValue ) );
	}

	// parameter
	if (attributeAssessment->getEventType() == bptncon::EventUtil::EVT_SELECTION) {
		if (parentElement->hasAttribute( xmlHndl->getXMLCh( "key" ) )) {
			attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "key" ) ) );

			attributeAssessment->setKey( attValue );
		}
	}

	//testing offset
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "offset" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "offset" ) ) );

		attributeAssessment->setOffset( attValue );
	}

	return attributeAssessment;
}

bptncon::ValueAssessment *NclConnectorsConverter::createValueAssessment( DOMElement *parentElement ) {

	std::string attValue;
	bptcf::XMLChHandler* xmlHndl = getXmlHandler();

	attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "value" ) ) );

	return new bptncon::ValueAssessment(attValue);
}

bptncon::AssessmentStatement *NclConnectorsConverter::createAssessmentStatement( DOMElement *parentElement ) {

	bptncon::AssessmentStatement *assessmentStatement;
	std::string attValue;
	bptcf::XMLChHandler* xmlHndl = getXmlHandler();

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "comparator" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "comparator" ) ) );

		assessmentStatement = new bptncon::AssessmentStatement( ncl_util::Comparator::fromString( attValue ) );

	} else {
		assessmentStatement = new bptncon::AssessmentStatement( ncl_util::Comparator::CMP_EQ );
	}

	return assessmentStatement;
}

bptncon::CompoundStatement *NclConnectorsConverter::createCompoundStatement( DOMElement *parentElement ) {

	bptncon::CompoundStatement *compoundStatement;
	std::string attValue;
	bptcf::XMLChHandler* xmlHndl = getXmlHandler();

	compoundStatement = new bptncon::CompoundStatement();

	if ((xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "operator" ) ) )).compare( "and" ) == 0) {

		compoundStatement->setOperator( bptncon::CompoundStatement::OP_AND );

	} else {
		compoundStatement->setOperator( bptncon::CompoundStatement::OP_OR );
	}

	// testing isNegated
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "isNegated" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "isNegated" ) ) );

		compoundStatement->setNegated( attValue.compare( "true" ) == 0 );
	}

	return compoundStatement;
}

bptncon::SimpleAction *NclConnectorsConverter::createSimpleAction( DOMElement *parentElement ) {

	bptncon::SimpleAction *actionExpression;
	std::string attValue;
	bptcf::XMLChHandler* xmlHndl = getXmlHandler();

	attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "role" ) ) );

	actionExpression = new bptncon::SimpleAction( attValue );

	//animation
	if (attValue == "set") {
		bptna::Animation* animation = NULL;
		if (parentElement->hasAttribute( xmlHndl->getXMLCh( "duration" ) )) {

			attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "duration" ) ) );

			animation = new bptna::Animation();
			if (attValue[0] != '$') {
				if (attValue != "" && attValue.find_last_of( 's' ) == attValue.length() - 1)
					attValue = attValue.substr( 0, attValue.length() - 1 );
				try {
					boost::lexical_cast<float>( attValue );
				} catch (boost::bad_lexical_cast &) {
					LERROR("NclConnectorsConverter", "Invalid parameter (duration) for animation");
					attValue = "0";
				}
			}
			animation->setDuration( attValue );
		}

		if (parentElement->hasAttribute( xmlHndl->getXMLCh( "by" ) )) {

			attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "by" ) ) );

			if (animation == NULL) {
				animation = new bptna::Animation();
			}

			if (attValue[0] == '$') {
				animation->setBy( attValue );
			} else {
				try {
					boost::lexical_cast<float>( attValue );
					animation->setBy( attValue );
				} catch (boost::bad_lexical_cast &) {
					LERROR("NclConnectorsConverter", "Invalid parameter (by) for animation");
					animation->setBy( "0" );
				}
			}

		}
		actionExpression->setAnimation( animation );
	}

	compileRoleInformation( actionExpression, parentElement );

	// transition
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "actionType" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "actionType" ) ) );

		actionExpression->setActionType( convertActionType( attValue ) );
	}

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "qualifier" ) )) {
		if ((xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "qualifier" ) ) )).compare( "seq" ) == 0) {

			actionExpression->setQualifier( bptncon::CompoundAction::OP_SEQ );

		} else { // any
			actionExpression->setQualifier( bptncon::CompoundAction::OP_PAR );
		}
	}

	//testing delay
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "delay" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "delay" ) ) );

		if (attValue[0] == '$') {
			actionExpression->setDelay( attValue );

		} else {
			actionExpression->setDelay( boost::lexical_cast<std::string>( boost::lexical_cast<float>( attValue.substr( 0, attValue.length() - 1 ) ) * 1000 ) );
		}
	}

	//  testing repeatDelay
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "repeatDelay" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "repeatDelay" ) ) );

		actionExpression->setDelay( attValue );
		if (attValue[0] == '$') {
			actionExpression->setDelay( attValue );

		} else {
			actionExpression->setDelay( boost::lexical_cast<std::string>( boost::lexical_cast<float>( attValue.substr( 0, attValue.length() - 1 ) ) * 1000 ) );
		}
	}

	// repeat
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "repeat" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "repeat" ) ) );

		if (attValue.compare( "infinite" ) == 0) {
			actionExpression->setRepeat( boost::lexical_cast<std::string>( 2 ^ 30 ) );

		} else {
			actionExpression->setRepeat( attValue );
		}
	}

	// testing value
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "value" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "value" ) ) );

		actionExpression->setValue( attValue );
	}

	// returning action expression
	return actionExpression;
}

bptncon::CompoundAction *NclConnectorsConverter::createCompoundAction( DOMElement *parentElement ) {

	bptncon::CompoundAction *actionExpression;
	std::string attValue;
	bptcf::XMLChHandler* xmlHndl = getXmlHandler();

	actionExpression = new bptncon::CompoundAction();

	if ((xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "operator" ) ) )).compare( "seq" ) == 0) {

		actionExpression->setOperator( bptncon::CompoundAction::OP_SEQ );

	} else {
		actionExpression->setOperator( bptncon::CompoundAction::OP_PAR );
	}

	//  testar delay
	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "delay" ) )) {
		attValue = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "delay" ) ) );

		if (attValue[0] == '$') {
			actionExpression->setDelay( attValue );

		} else {
			actionExpression->setDelay( boost::lexical_cast<std::string>( boost::lexical_cast<float>( attValue.substr( 0, attValue.length() - 1 ) ) * 1000 ) );
		}
	}

	// retornar expressao de condicao
	return actionExpression;
}

short NclConnectorsConverter::convertActionType( const std::string &actionType ) {
	if (actionType == "start")
		return bptncon::SimpleAction::ACT_START;

	else if (actionType == "stop")
		return bptncon::SimpleAction::ACT_STOP;

	else if (actionType == "set")
		return bptncon::SimpleAction::ACT_SET;

	else if (actionType == "pause")
		return bptncon::SimpleAction::ACT_PAUSE;

	else if (actionType == "resume")
		return bptncon::SimpleAction::ACT_RESUME;

	else if (actionType == "abort")
		return bptncon::SimpleAction::ACT_ABORT;

	return -1;
}

short NclConnectorsConverter::convertEventState( const std::string &eventState ) {
	if (eventState == "occurring") {
		return bptncon::EventUtil::ST_OCCURRING;

	} else if (eventState == "paused") {
		return bptncon::EventUtil::ST_PAUSED;

	} else if (eventState == "sleeping") {
		return bptncon::EventUtil::ST_SLEEPING;

	}

	return -1;
}

void NclConnectorsConverter::addConditionExpressionToCompoundCondition(bptncon::CompoundCondition *parentObject, bptncon::ConditionExpression *childObject){

	parentObject->addConditionExpression(childObject);
}

void NclConnectorsConverter::addAttributeAssessmentToAssessmentStatement(bptncon::AssessmentStatement *parentObject, bptncon::AttributeAssessment *childObject ) {

	if (parentObject->getMainAssessment() == NULL) {
		parentObject->setMainAssessment(childObject);

	} else {
		parentObject->setOtherAssessment(childObject);
	}
}

void NclConnectorsConverter::addValueAssessmentToAssessmentStatement(bptncon::AssessmentStatement *parentObject, bptncon::ValueAssessment *childObject) {

	parentObject->setOtherAssessment(childObject);
}

void NclConnectorsConverter::addStatementToCompoundStatement(bptncon::CompoundStatement *parentObject, bptncon::Statement *childObject) {

	parentObject->addStatement(childObject );
}

void NclConnectorsConverter::addActionToCompoundAction(bptncon::CompoundAction *parentObject, bptncon::Action *childObject) {

	parentObject->addAction(childObject);
}

void NclConnectorsConverter::addConditionToCausalConnector(bptncon::CausalConnector *parentObject, bptncon::ConditionExpression *childObject) {

	parentObject->setConditionExpression(childObject);
}

void NclConnectorsConverter::addActionToCausalConnector(bptncon::CausalConnector *parentObject, bptncon::Action *childObject){

	parentObject->setAction(childObject);
}

}
}
}
}
}
