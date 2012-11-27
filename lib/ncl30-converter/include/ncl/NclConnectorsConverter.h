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

#ifndef NclConnectorsConverter_H
#define NclConnectorsConverter_H

#include "../framework/ncl/NclConnectorsParser.h"
namespace bptcfn = ::br::pucrio::telemidia::converter::framework::ncl;

namespace br {
namespace pucrio {
namespace telemidia {
namespace ncl {
namespace connectors {
 	class Role;
}}}}}

#include <string>

namespace br {
namespace pucrio {
namespace telemidia {
namespace converter {
namespace ncl {
class NclConnectorsConverter: public bptcfn::NclConnectorsParser
{

public:
	explicit NclConnectorsConverter( bptcf::DocumentParser *documentParser );
	void addCausalConnectorToConnectorBase(bptncon::ConnectorBase *parentObject, bptncon::Connector *childObject);
	void addConnectorParamToCausalConnector(bptncon::Connector *parentObject, bptn::Parameter *childObject);
	void addImportBaseToConnectorBase(bptncon::ConnectorBase *parentObject, DOMElement *childObject );
	bptncon::CausalConnector *createCausalConnector( DOMElement *parentElement );
	bptncon::ConnectorBase *createConnectorBase( DOMElement *parentElement );
	bptn::Parameter *createConnectorParam( DOMElement *parentElement );

private:
	void compileRoleInformation( bptncon::Role *role, DOMElement *parentElement );

public:
	bptncon::SimpleCondition *createSimpleCondition( DOMElement *parentElement );
	bptncon::CompoundCondition *createCompoundCondition( DOMElement *parentElement );
	bptncon::AttributeAssessment *createAttributeAssessment( DOMElement *parentElement );
	bptncon::ValueAssessment *createValueAssessment( DOMElement *parentElement );
	bptncon::AssessmentStatement *createAssessmentStatement( DOMElement *parentElement );
	bptncon::CompoundStatement *createCompoundStatement( DOMElement *parentElement );
	bptncon::SimpleAction *createSimpleAction( DOMElement *parentElement );
	bptncon::CompoundAction *createCompoundAction( DOMElement *parentElement );

private:
	short convertActionType( const std::string &actionType );

public:
	static short convertEventState( const std::string &eventState );
	void addConditionExpressionToCompoundCondition(bptncon::CompoundCondition *parentObject, bptncon::ConditionExpression *childObject);
	void addAttributeAssessmentToAssessmentStatement(bptncon::AssessmentStatement *parentObject, bptncon::AttributeAssessment *childObject );
	void addValueAssessmentToAssessmentStatement(bptncon::AssessmentStatement *parentObject, bptncon::ValueAssessment *childObject);
	void addStatementToCompoundStatement(bptncon::CompoundStatement *parentObject, bptncon::Statement *childObject);
	void addActionToCompoundAction(bptncon::CompoundAction *parentObject, bptncon::Action *childObject);
	void addConditionToCausalConnector(bptncon::CausalConnector *parentObject, bptncon::ConditionExpression *childObject);
	void addActionToCausalConnector(bptncon::CausalConnector *parentObject, bptncon::Action *childObject);
};
}
}
}
}
}

#endif
