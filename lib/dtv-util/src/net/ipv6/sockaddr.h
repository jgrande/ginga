#pragma once

#include "address.h"
#include <string>

struct sockaddr;
struct sockaddr_in6;

namespace util {
namespace net {
namespace ipv6 {

class SockAddr {
public:
	SockAddr( void );
	SockAddr( const SockAddr & );
	SockAddr( struct sockaddr &sa );
	~SockAddr( void ) {};

	//  Getters
	Address address() const;
	unsigned short port() const;

	//	Operators
	SockAddr &operator=( const SockAddr &other );
	SockAddr &operator=( struct sockaddr_in6 &sa );
	SockAddr &operator=( struct sockaddr &sa );
	operator struct sockaddr_in6() const;
	operator struct sockaddr() const;
	operator std::string() const;
	bool operator==( const SockAddr &other );
	bool operator==( const sockaddr_in6 &other );
};

}
}
}

