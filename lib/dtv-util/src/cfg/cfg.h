#pragma once

#include "propertynode.h"
#include <string>

namespace util {
namespace cfg {

typedef PropertyNode PropertyTree;

PropertyTree &get();
PropertyTree &get( const std::string &path );

template<class T>
const T getValue( const std::string &path ) {
	return get().get<T> (path);
}

template<class T>
void setValue( const std::string &path, T val ) {
	get().set<T> (path, val);
}

}
}
