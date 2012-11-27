#pragma once

#include "property.h"
#include "check.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace player {

template<typename T>
class PropertyImpl : public Property {
public:
	PropertyImpl( bool needRefresh, T &value )
		: _value(value), _needRefresh(needRefresh), _check(boost::bind(&check::always<T>,_1)) {}
	virtual ~PropertyImpl() {}
	
	virtual bool canStart() const { return _check(_value); }
	virtual bool needRefresh() const { return _needRefresh; }
	virtual bool assign( const T &value ) {
		bool result=false;
		if (check(value) && _value != value) {
			_value = value;
			markModified();
			result=true;
		}
		return result;
	}
	
	//	Getters and setters
	typedef boost::function<bool (const T &value )> Method;
	typedef boost::function<void (void)> VoidMethod;	
	void setCheck( const Method &method ) { assert( !method.empty() ); _check = method; }
	void setApply( const VoidMethod &method ) { assert( !method.empty() ); _apply = method; }
	void setNeedResfresh(bool needRefresh) { _needRefresh = needRefresh; }

protected:
	virtual void applyChanges() {
		if (!_apply.empty()) {
			_apply();
		}
	}

	bool check( const T &value ) {
		if (!_check(value)) {
			throw std::runtime_error( "Invalid value" );
		}
		return true;
	}

private:
	T &_value;
	bool _needRefresh;
	Method _check;
	VoidMethod _apply;

	PropertyImpl() {}
	PropertyImpl &operator=( const PropertyImpl &other ) { return *this; }
};

template<typename T>
class MultiPropertyImpl : public PropertyImpl<T> {
public:
	MultiPropertyImpl( bool &propertyIsApplied, bool needRefresh, T &value )
		: PropertyImpl<T>( needRefresh, value ), _propertyIsApplied(propertyIsApplied) {}
	virtual ~MultiPropertyImpl() {}

protected:
	virtual void markModified() {
		PropertyImpl<T>::markModified();
		_propertyIsApplied=false;
	}
	
	virtual void applyChanges() {
		if (!_propertyIsApplied) {
			PropertyImpl<T>::applyChanges();
			_propertyIsApplied=true;
		}
	}

private:
	bool &_propertyIsApplied;
};


}
