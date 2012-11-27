#include "sockaddr.h"

#ifdef _WIN32
#	include <winsock2.h>
#	include <Ws2tcpip.h>
#else
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <arpa/inet.h>
#	include <netdb.h>
#endif

//	TODO: Implement ipv6

namespace util {
namespace net {
namespace ipv6 {

SockAddr::SockAddr( void )
{
}

SockAddr::SockAddr( const SockAddr & )
{
}

SockAddr::SockAddr( struct sockaddr & )
{
}

//	Operators
SockAddr &SockAddr::operator=( const SockAddr & /*other*/ ) {
	return *this;
}

SockAddr &SockAddr::operator=( struct sockaddr_in6 & /*sa*/ ) {
	return *this;
}

SockAddr &SockAddr::operator=( struct sockaddr &sa ) {
	struct sockaddr_in6 *saddr=(struct sockaddr_in6 *)&sa;
	*this = *saddr;
	return *this;
}

SockAddr::operator struct sockaddr_in6() const {
	struct sockaddr_in6 saddr;
	saddr.sin6_family = AF_INET6;
	return saddr;
}

SockAddr::operator struct sockaddr() const {
	struct sockaddr saddr;
	saddr.sa_family = AF_INET6;
	return saddr;
}

SockAddr::operator std::string() const {
	return std::string();
}

bool SockAddr::operator==( const SockAddr & /*other*/ ) {
	return true;
}

bool SockAddr::operator==( const sockaddr_in6 & /*other*/ ) {
	return true;
}

//  Getters
Address SockAddr::address() const {
	return Address();
}

unsigned short SockAddr::port() const {
	return 10;
}

}
}
}

