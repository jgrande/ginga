#pragma once

#include "address.h"
#include <string>

struct sockaddr;
struct sockaddr_in;

namespace util {
namespace net {
namespace ipv4 {

class SockAddr {
public:
	SockAddr( void );
	SockAddr( const SockAddr &other );
	SockAddr( unsigned short port );
	SockAddr( const Address &ip, unsigned short port=0 );
	SockAddr( struct sockaddr &sa );
	~SockAddr( void );			

	//  Getters
	Address address() const;
	unsigned short port() const;

	//	Operators
	SockAddr &operator=( const SockAddr &other );
	SockAddr &operator=( struct sockaddr_in &sa );
	SockAddr &operator=( struct sockaddr &sa );
	operator struct sockaddr_in() const;
	operator struct sockaddr() const;
	operator std::string() const;
	bool operator==( const SockAddr &other );
	bool operator==( const sockaddr_in &other );

private:
	unsigned short  _port;
	Address _addr;
};

}
}
}

