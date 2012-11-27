#pragma once

#include "../types.h"
#include <string>

namespace util {
namespace net {
namespace ipv4 {

class Address {
public:
	Address( void );
	Address( const Address &other );
	explicit Address( const char *ip );
	explicit Address( const std::string &ip );
	~Address( void );

	//	operators
	Address &operator=( const Address &other );
	bool operator==( const Address &other );
	Address &operator=( DWORD ip );
	operator DWORD() const;

	//	methods
	family::type family() const;
	std::string asString() const;
	bool isMulticast() const;
	bool isUnicast() const;
	bool isAnycast() const;

private:
	DWORD _ip;
};

}
}
}

