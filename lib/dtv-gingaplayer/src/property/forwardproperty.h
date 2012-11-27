#pragma once

#include "property.h"

namespace player {

template<typename T>
class ForwardProperty : public Property {
public:
	typedef boost::function<void (const T&value)> SetFunction;

	ForwardProperty( const SetFunction &setter, bool onlyDynamic=false ) : _set( setter ),  _onlyDynamic(onlyDynamic) {}
	virtual ~ForwardProperty() {}
	
	virtual bool assign( const T &value ) {
		_set( value );
		return true;
	}
	
	virtual bool isOnlyDynamic(){
		return _onlyDynamic;
	}

private:
	SetFunction _set;
	bool _onlyDynamic;
};

}

