#pragma once

#include <canvas/point.h>
#include <canvas/size.h>
#include <canvas/rect.h>
#include <util/keydefs.h>
#include <string>

namespace player {

class Property {
public:
	Property( void );
	virtual ~Property();

	virtual bool assign( const bool &value );
	virtual bool assign( const int &value );
	virtual bool assign( const float &value );
	virtual bool assign( const std::string &value );
	bool assign( const char *value );		
	virtual bool assign( const canvas::Size &value );
	virtual bool assign( const canvas::Point &value );
	virtual bool assign( const canvas::Rect &value );
	virtual bool assign( const std::pair<std::string,std::string> &value );	
	virtual bool assign( const std::pair<util::key::type,bool> &value );

	virtual bool canStart() const;
	virtual bool needRefresh() const;
	virtual void markModified();
	virtual bool isOnlyDynamic(){
		return false;
	}
	bool apply();
	bool changed() const;

protected:
	virtual void applyChanges();

private:
	bool _changed;
};

}

