#include "compositeproperty.h"
#include <util/mcr.h>
#include <boost/foreach.hpp>

namespace player {

CompositeProperty::CompositeProperty()
{
}

CompositeProperty::~CompositeProperty()
{
	CLEAN_ALL( Property *, _properties );
}

bool CompositeProperty::canStart() const {
	bool result=true;
	BOOST_FOREACH( Property *prop, _properties) {
		result &= prop->canStart();
	}
	return result;
}

void CompositeProperty::add( Property *prop ) {
	_properties.push_back( prop );
}

bool CompositeProperty::needRefresh() const {
	bool result=false;
	BOOST_FOREACH( Property *prop, _properties) {
		result |= prop->needRefresh();
	}
	return result;
}

void CompositeProperty::applyChanges() {
	BOOST_FOREACH( Property *prop, _properties) {
		prop->apply();
	}
}

}

