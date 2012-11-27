#include "../../../include/framework/XMLChHandler.h"
#include <iostream>
#include <map>

namespace br {
namespace pucrio {
namespace telemidia {
namespace converter {
namespace framework {

XMLChHandler::XMLChHandler() {
}

XMLChHandler::~XMLChHandler() {
	unitiliaze();
}

std::string XMLChHandler::getStr( const XMLCh* anIdentifier ) {
	char *transcodedValue = XMLString::transcode( anIdentifier );
	std::string newValue = std::string( transcodedValue );

	XMLString::release( &transcodedValue );
	return newValue;
}

XMLCh* XMLChHandler::getXMLCh( const std::string &str ) {
	xmlMap::iterator it = xmls.find( str );
	if (it != xmls.end())
		return it->second;
	else {
		XMLCh* newValue = XMLString::transcode( str.c_str() );
		xmls[str] = newValue;
		return newValue;
	}
}

void XMLChHandler::unitiliaze() {
	for (xmlMap::const_iterator it = xmls.begin(); it != xmls.end(); it++) {
		XMLCh* value = it->second;
		XMLString::release( &value );
	}
	xmls.clear();
}

}
}
}
}
}
