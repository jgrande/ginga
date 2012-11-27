#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>

namespace util {
namespace cfg {

class PropertyNode;
class PropertyValue;

namespace imp {

bool pretendFilter( PropertyValue *p );
bool defaultFilter( PropertyValue *p );
std::string pretendPrinter( PropertyValue *p );
std::string defaultPrinter( PropertyValue *p );

}

class XmlParser {
public:
	XmlParser();
	virtual ~XmlParser();

	bool pretend(std::ostream &aStream, PropertyNode *tree );
	bool defaults(std::ostream &aStream, PropertyNode *tree );
	void parserIn( const std::string &name, PropertyNode *tree );

	void operator()( PropertyValue *val );
	void operator()( PropertyNode *node );

protected:
	std::string parserOut( PropertyNode *tree );
	xercesc::DOMDocument *parserDoc( const std::string &name, xercesc::XercesDOMParser *config );
	void recursiveIn( xercesc::DOMElement *elementRoot, PropertyNode *tree );

	typedef bool ( *Filter )( PropertyValue * );
	typedef std::string ( *Printer )( PropertyValue * );

private:
	xercesc::DOMDocument *_DOMDoc;
	xercesc::DOMElement *_pRootElement;
	xercesc::DOMImplementation *_DOMimp;
	std::vector<xercesc::DOMElement *> _elements;
	std::vector<xercesc::DOMElement *> _nodes;
	Filter _filter;
	Printer _printer;
	bool _first;

};

}
}
