#include "types.h"
#include <canvas/color.h>
#include <boost/algorithm/string.hpp>

namespace player {
namespace property {

#define DO_ENUM_PROPERTY_STRING( p ) #p,
static const char* properties[] = {
    "NULL",
    PROPERTY_LIST(DO_ENUM_PROPERTY_STRING)
    "LAST"
};
#undef DO_ENUM_PROPERTY_STRING

type::Type getProperty( const char *propertyName ) {
	for (int i=0; i<type::LAST; i++) {
		if (!strcmp( properties[i], propertyName)) {
			return (type::Type)i;
		}
	}
	return type::null;
}

const char *getPropertyName( type::Type pValue ) {
	if (pValue > type::LAST) {
		pValue=type::null;
	}
	return properties[pValue];
}

}	//	namespace property
}	//	namespace player
