#include "../log.h"
#include "propertynode.h"
#include "propertyvalue.h"
#include "xmlparser.h"
#include <boost/foreach.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/util/PlatformUtils.hpp>

namespace util {
namespace cfg {

namespace imp {

bool pretendFilter( PropertyValue *p ) {
	return p->isModified() && p->isVisible();
}
bool defaultFilter( PropertyValue *p ) {
	return p->isVisible();
}
std::string pretendPrinter( PropertyValue *p ) {
	return p->asString();
}

std::string defaultPrinter( PropertyValue *p ) {
	return p->asStringDefault();
}

}

XmlParser::XmlParser() {
	try {
		xercesc::XMLPlatformUtils::Initialize();
	} catch (const xercesc::XMLException &toCatch) {
		char *message = xercesc::XMLString::transcode( toCatch.getMessage() );
		LERROR("cfg::XMLParser", "during initialization: %s", message );
		xercesc::XMLString::release( &message );
	}
}
XmlParser::~XmlParser() {
	xercesc::XMLPlatformUtils::Terminate();
}

//Set a xml config and read the file
//return a DOMDocument for process the input file
xercesc::DOMDocument *XmlParser::parserDoc( const std::string &name, xercesc::XercesDOMParser *config ) {
	config->setValidationScheme( xercesc::XercesDOMParser::Val_Auto );
	config->setDoNamespaces( false );
	config->setDoSchema( false );
	config->setLoadExternalDTD( false );
	config->setCreateEntityReferenceNodes( false );

	XMLCh *str = xercesc::XMLString::transcode( name.c_str() );
	xercesc::LocalFileInputSource source( str );
	xercesc::XMLString::release( &str );
	config->parse( source );

	if (config->getErrorCount() != 0) {
		delete ( config );
		throw std::runtime_error( "Error parsing xml configuration file: Source file cannot be open" );
	}

	return config->getDocument();
}

// Recursive method to parser the DOMElements to tree
void XmlParser::recursiveIn( xercesc::DOMElement *elementRoot, PropertyNode *tree ) {
	xercesc::DOMElement *currentElement;
	xercesc::DOMNodeList *childrens = elementRoot->getChildNodes();
	const XMLSize_t nodeCount = childrens->getLength();

	//for each node called recursiveIn with this node, and for each property changes the value in the tree
	for (XMLSize_t xx = 0; xx < nodeCount; ++xx) {
		xercesc::DOMNode *currentNode = childrens->item( xx );
		//if the currentNode is a DomElement
		if (currentNode->getNodeType() && currentNode->getNodeType() == xercesc::DOMNode::ELEMENT_NODE) {
			currentElement = dynamic_cast<xercesc::DOMElement *> ( currentNode );

			//if the item has children, it means that is a node
			if (currentElement->getChildElementCount() > 0) {
				char *tmpNode = xercesc::XMLString::transcode( currentElement->getTagName() );
				if (tree->hasChild( tmpNode )) {
					recursiveIn( currentElement, &( *tree )( tmpNode ) );
					delete ( tmpNode );
				} else {
					delete ( tmpNode );
					throw std::runtime_error( "[util::cfg::XParser::recursiveIn]Invalid node in configuration file" );
				}
			} else {
				//The item hasn't children, it means that is a value
				char *tmpName = xercesc::XMLString::transcode( currentElement->getTagName() );
				std::string tmpNameS( tmpName );

				if (tree->existsValue(tmpName)) {
					char *tmpVal = xercesc::XMLString::transcode( currentElement->getTextContent() );
					std::string tmpvalS( tmpVal );
					tree->setStr( tmpNameS, tmpvalS );
					delete ( tmpVal );
					delete ( tmpName );
				} else {
					delete ( tmpName );
					throw std::runtime_error( "[util::cfg::XParser::recursiveIn]Invalid Value in configuration file" );
				}


			}
		}
	}

}

//This function set a pretendFilter and a pretendPrinter and call parserOut for export the tree with xml format to the stream.
//Return false if the data is  empty and true otherwise
bool XmlParser::pretend(std::ostream &aStream, PropertyNode *tree ) {
	_first = true;
	_filter = &imp::pretendFilter;
	_printer = &imp::pretendPrinter;
	std::string data;
	data = parserOut( tree );
	boost::replace_all(data,"\n\n","\n");
	if (!data.empty()) {
		aStream << data;
		return true;
	} else {
		return false;
	}
}

//This function set a default Filter and a default Printer and call parserOut for export the tree with xml format to the stream.
//Return false if the data is  empty and true otherwise
bool XmlParser::defaults(std::ostream &aStream, PropertyNode *tree ) {
	_first = true;
	_filter = &imp::defaultFilter;
	_printer = &imp::defaultPrinter;
	std::string data;
	data = parserOut( tree );
	boost::replace_all(data,"\n\n","\n");
	if (!data.empty()) {
		aStream << data;
		return true;
	} else {
		return false;
	}
}

//Check the filter Value and create the DomElement value
void XmlParser::operator()( PropertyValue *val ) {
	if (( *_filter )( val )) {
		xercesc::DOMElement *tag;
		xercesc::DOMText *v;
		XMLCh tempTag[250];
		XMLCh tempVal[250];
		xercesc::XMLString::transcode( (( *_printer )( val )).c_str(), tempVal, 249 );
		v = _DOMDoc->createTextNode( tempVal );
		xercesc::XMLString::transcode( val->name().c_str(), tempTag, 249 );
		try {
			tag = _DOMDoc->createElement( tempTag );
		} catch ( const xercesc::DOMException & /*e*/ ) {
			//TODO: remove all illegals character
			std::string replace = val->name();
			replace.replace(replace.find("("),1,"");
			replace.replace(replace.find(")"),1,"");
			xercesc::XMLString::transcode( replace.c_str(), tempTag, 249 );
			tag = _DOMDoc->createElement( tempTag );
		}
		tag->appendChild( v );
		_elements.push_back( tag );
	}
}

//for each node visit its values, and visit its nodes. if their values ​​or nodes meet the filter at least once, then we create the DOMElement node
void XmlParser::operator()( PropertyNode *node ) {
	bool print = false;
	size_t pos = _nodes.size();
	xercesc::DOMElement *n;

	//Xerces manage differently the first DOMElement (root) and the rest of the nodes
	if (_first) {
		n = _DOMDoc->getDocumentElement();
		_first = false;
	} else {
		XMLCh tempNode[250];
		xercesc::XMLString::transcode( node->name().c_str(), tempNode, 249 );
		n = _DOMDoc->createElement( tempNode );
	}
	//Visit its properties values
	node->visitValues( *this );
	if (!_elements.empty()) {
		print = true;
		BOOST_FOREACH( xercesc::DOMElement *e, _elements ) {
			n->appendChild( e );
		}
		while (!_elements.empty()) {
			_elements.pop_back();
		}
	}

	//Visit its children nodes
	if (node->hasChildren()) {
		node->visitNodes( *this );
		if (pos < _nodes.size()) {
			print = true;
			//Add its DOMElements children
			for (size_t b = pos; b < _nodes.size(); b++) {
				n->appendChild( _nodes.at( b ) );
			}
			//Erase the DOMElements children in the list because they are attach in its parent
			size_t size = _nodes.size();
			for (size_t b = pos; b < size; b++) {
				_nodes.erase( _nodes.end()-1 );
			}
		}
	}
	if (print) {
		_nodes.push_back( n );
	}
}

//This function initializes the Xerces format, call the function to walk the tree to create the DOMElements. And finally return a string with DOMDocument.
std::string XmlParser::parserOut( PropertyNode *tree ) {
	XMLCh *core = xercesc::XMLString::transcode( "core" );
	_DOMimp = xercesc::DOMImplementationRegistry::getDOMImplementation( core );
	XMLCh tempStrNameRoot[100];
	xercesc::XMLString::transcode( tree->name().c_str(), tempStrNameRoot, 99 );

	_DOMDoc = _DOMimp->createDocument( 0, tempStrNameRoot, 0 );

	( *this )( tree );
	xercesc::DOMLSSerializer *pSerializer = _DOMimp->createLSSerializer();

	pSerializer->getDomConfig()->setParameter( xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true );
	XMLCh *lfSeq = xercesc::XMLString::transcode("\n");
	pSerializer->setNewLine(lfSeq);

	XMLCh *tempData = pSerializer->writeToString(_DOMDoc);
	char *outPutChar = xercesc::XMLString::transcode(tempData);
	std::string outPutString(outPutChar);

	_nodes.clear();
	xercesc::XMLString::release(&lfSeq);
	_DOMDoc->release();
	pSerializer->release();
	xercesc::XMLString::release( &core );
	delete tempData;
	delete outPutChar;
	return outPutString;
}

//Call the function parserDoc to read the file, check if is possible, and call the recursiveIn with the tree.
void XmlParser::parserIn( const std::string &name, PropertyNode *tree ) {
	if (!tree) {
		throw std::runtime_error( "Error occurred parsing xml file: NULL Config Tree" );
	}

	xercesc::XercesDOMParser *config = new xercesc::XercesDOMParser();
	xercesc::DOMDocument *aDomDocument = parserDoc( name, config );
	if (aDomDocument) {
		xercesc::DOMElement *first = aDomDocument->getDocumentElement();
		char *tmpNode = xercesc::XMLString::transcode( first->getTagName() );
		if (tree->name().compare(tmpNode) != 0) {
			delete tmpNode;
			delete config;
			throw std::runtime_error( "Error occurred parsing xml file: The xml not match with de Config Tree" );
		}
		delete tmpNode;
		try {
			recursiveIn( first, tree );
		} catch (const std::runtime_error &e) {
			delete config;
			throw e;

		}

	} else {
		xercesc::XMLPlatformUtils::Terminate();
		throw std::runtime_error( "Error occurred parsing xml file" );
	}
	delete config;
}

}
}
