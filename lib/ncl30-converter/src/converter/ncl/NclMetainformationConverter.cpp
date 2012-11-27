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

#include "../../../include/ncl/NclMetainformationConverter.h"
#include "../../../include/framework/XMLChHandler.h"
#include "ncl30/metainformation/Meta.h"
#include "ncl30/metainformation/Metadata.h"

namespace bptnm = ::br::pucrio::telemidia::ncl::metainformation;

namespace br {
namespace pucrio {
namespace telemidia {
namespace converter {
namespace ncl {
NclMetainformationConverter::NclMetainformationConverter( bptcf::DocumentParser *documentParser ) :
		NclMetainformationParser( documentParser ) {

}

void* NclMetainformationConverter::createMeta( DOMElement* parentElement ) {

	std::string name, content;
	bptnm::Meta* meta;
	bptcf::XMLChHandler* xmlHndl = getXmlHandler();

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "name" ) )) {
		name = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "name" ) ) );

	} else {
		return NULL;
	}

	if (parentElement->hasAttribute( xmlHndl->getXMLCh( "content" ) )) {
		content = xmlHndl->getStr( parentElement->getAttribute( xmlHndl->getXMLCh( "content" ) ) );

	} else {
		return NULL;
	}

	meta = new bptnm::Meta( name, (void*) content.c_str() );
	return (void*) meta;
}

void* NclMetainformationConverter::createMetadata() {

	bptnm::Metadata* metadata;

	metadata = new bptnm::Metadata();
	return (void*) metadata;
}
}
}
}
}
}
