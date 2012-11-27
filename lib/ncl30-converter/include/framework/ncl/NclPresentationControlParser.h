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

#ifndef NCLPRESENTATIONCONTROLPARSER_H_
#define NCLPRESENTATIONCONTROLPARSER_H_

#include "../ModuleParser.h"

namespace br {
namespace pucrio {
namespace telemidia {
namespace converter {
namespace framework {
class DocumentParser;
}
}
}
}
}
namespace bptcf = ::br::pucrio::telemidia::converter::framework;

#include <xercesc/dom/DOM.hpp>
XERCES_CPP_NAMESPACE_USE

namespace br {
namespace pucrio {
namespace telemidia {
namespace converter {
namespace framework {
namespace ncl {

class NclPresentationSpecificationParser;
class NclInterfacesParser;
class NclImportParser;

class NclPresentationControlParser: public ModuleParser
{
private:
	NclPresentationSpecificationParser *presentationSpecificationParser;
	void *componentsParser;
	NclInterfacesParser *interfacesParser;
	NclImportParser *importParser;

public:
	explicit NclPresentationControlParser( bptcf::DocumentParser *documentParser );

	void *parseBindRule( DOMElement *parentElement );
	virtual void *createBindRule( DOMElement *parentElement )=0;

	void *parseRuleBase( DOMElement *parentElement );
	virtual void *createRuleBase( DOMElement *parentElement )=0;

	virtual void addImportBaseToRuleBase( void *parentObject, void *childObject )=0;

	virtual void addRuleToRuleBase( void *parentObject, void *childObject )=0;

	virtual void addCompositeRuleToRuleBase( void *parentObject, void *childObject )=0;

	void *parseRule( DOMElement *parentElement );
	virtual void *createRule( DOMElement *parentElement )=0;

	void *parseSwitch( DOMElement *parentElement );
	virtual void *posCompileSwitch( DOMElement *parentElement, void *parentObject );

	void *parseDefaultComponent( DOMElement *parentElement );

	virtual void *createDefaultComponent( DOMElement *parentElement )=0;

	virtual void addDefaultComponentToSwitch( void *parentObject, void *childObject )=0;

	void *parseDefaultDescriptor( DOMElement *parentElement );

	virtual void *createDefaultDescriptor( DOMElement *parentElement )=0;

	virtual void addDefaultDescriptorToDescriptorSwitch( void *parentObject, void *childObject )=0;

	virtual void *createSwitch( DOMElement *parentElement )=0;

	virtual void addSwitchPortToSwitch( void *parentObject, void *childObject )=0;

	virtual void addMediaToSwitch( void *parentObject, void *childObject )=0;
	virtual void addContextToSwitch( void *parentObject, void *childObject )=0;

	virtual void addSwitchToSwitch( void *parentObject, void *childObject )=0;

	virtual void addBindRuleToSwitch( void *parentObject, void *childObject )=0;

	void *parseCompositeRule( DOMElement *parentElement );

	virtual void *createCompositeRule( DOMElement *parentElement )=0;

	virtual void addRuleToCompositeRule( void *parentObject, void *childObject )=0;

	virtual void addCompositeRuleToCompositeRule( void *parentObject, void *childObject )=0;

	void *parseDescriptorSwitch( DOMElement *parentElement );

	virtual void *createDescriptorSwitch( DOMElement *parentElement )=0;

	virtual void addBindRuleToDescriptorSwitch( void *parentObject, void *childObject )=0;

	virtual void addDescriptorToDescriptorSwitch( void *parentObject, void *childObject )=0;

	NclPresentationSpecificationParser*
	getPresentationSpecificationParser();

	void setPresentationSpecificationParser( NclPresentationSpecificationParser* presentationSpecificationParser );

	void *getComponentsParser();
	void setComponentsParser( void *componentsParser );
	NclInterfacesParser *getInterfacesParser();
	void setInterfacesParser( NclInterfacesParser *interfacesParser );
	NclImportParser *getImportParser();
	void setImportParser( NclImportParser *importParser );
};
}
}
}
}
}
}

#endif /*NCLPRESENTATIONCONTROLPARSER_H_*/
