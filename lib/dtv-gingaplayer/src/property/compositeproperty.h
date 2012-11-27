#pragma once

#include "property.h"
#include <vector>

namespace player {

class CompositeProperty : public Property {
public:
	CompositeProperty();
	virtual ~CompositeProperty();

	virtual bool assign( const bool &value ) { return loopAssign( value ); }
	virtual bool assign( const int &value )  { return loopAssign( value ); }
	virtual bool assign( const float &value )  { return loopAssign( value ); }
	virtual bool assign( const std::string &value ) { return loopAssign( value ); }
	virtual bool assign( const canvas::Size &value )  { return loopAssign( value ); }
	virtual bool assign( const canvas::Point &value ) { return loopAssign( value ); }
	virtual bool assign( const canvas::Rect &value ) { return loopAssign( value ); }	
	virtual bool assign( const std::pair<std::string,std::string> &value ) { return loopAssign( value ); }
	virtual bool canStart() const;

	void add( Property *prop );

protected:
	virtual bool needRefresh() const;
	virtual void applyChanges();
	
	template<typename T>
	bool loopAssign( const T &value ) {
		std::vector<Property *>::const_iterator it=_properties.begin();
		while (it != _properties.end()) {
			Property *prop = (*it);
			if (!prop->assign( value )) {
				return false;
			}
			if (prop->changed()) {
				markModified();
			}
			it++;
		}
		return true;
	}

private:
	std::vector<Property *> _properties;
};

}

