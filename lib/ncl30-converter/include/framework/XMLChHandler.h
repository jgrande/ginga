#ifndef XMLChHandler_H
#define XMLChHandler_H

#include <map>
#include <string>
#include <xercesc/dom/DOM.hpp>
XERCES_CPP_NAMESPACE_USE

namespace br {
namespace pucrio {
namespace telemidia {
namespace converter {
namespace framework {

typedef std::map<const std::string, XMLCh*> xmlMap;

class XMLChHandler {
public:
	XMLChHandler();
	~XMLChHandler();

	std::string getStr( const XMLCh* anIdentifier );
	XMLCh* getXMLCh( const std::string &str );

protected:
	void unitiliaze();

private:
	xmlMap xmls;
};

}
}
}
}
}

#endif /*XMLChHandler_H_*/
