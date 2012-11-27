#pragma once

#include "types.h"
#include "ipv4/sockaddr.h"
#include "ipv6/sockaddr.h"
#include <string>
#include <exception>
#include <typeinfo>

struct sockaddr;

namespace util {
namespace net {

class SockAddr {
public:
	SockAddr( void );
	SockAddr( const SockAddr &sa );
	SockAddr( ipv4::SockAddr &sa );
	SockAddr( ipv6::SockAddr &sa );
	SockAddr( struct sockaddr &sa );
	~SockAddr( void );

	//	Operators
	SockAddr &operator=( const SockAddr &sa );
	SockAddr &operator=( struct sockaddr &sa );
	bool operator==( const SockAddr &other ) const;
	bool operator==( const struct sockaddr &sa ) const;
	operator struct sockaddr() const;

	//	Methods
	static bool isFamilySupported( family::type family );
	family::type family() const;
	std::string asString() const;
	template<typename T,class Operator> inline T visit( Operator oper ) const;
	template<class Operator> inline void visit( Operator oper );

private:
	char _sa[16];
};

template<typename T,class Operator>
inline T SockAddr::visit( Operator oper ) const {
	struct sockaddr *tmp = (struct sockaddr *)_sa;
	
	if (family() == family::ipv4) {
		ipv4::SockAddr sa4( *tmp );
		return oper(sa4);
	}
	else if (family() == family::ipv6) {
		ipv6::SockAddr sa6( *tmp );
		return oper(sa6);
	}
	else {
		throw std::bad_cast();
	}
}

template<class Operator>
inline void SockAddr::visit( Operator oper ) {
	struct sockaddr *tmp = (struct sockaddr *)_sa;

	if (family() == family::ipv4) {
		ipv4::SockAddr sa4( *tmp );
		oper(sa4);
	}
	else if (family() == family::ipv6) {
		ipv6::SockAddr sa6( *tmp );
		oper(sa6);
	}
	else {
		throw std::bad_cast( "Socket family unknown" );
	}
}

}
}

