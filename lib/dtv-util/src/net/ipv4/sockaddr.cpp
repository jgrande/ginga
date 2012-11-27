#include "sockaddr.h"
#include "../../string.h"

#ifdef _WIN32
#	include <winsock2.h>
#	include <Ws2tcpip.h>
#else
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <arpa/inet.h>
#	include <netdb.h>
#endif

namespace util {
namespace net {
namespace ipv4 {

SockAddr::SockAddr( void )
{
	_port = 0;
}

SockAddr::SockAddr( const SockAddr &other )
{
	_addr = other._addr;
	_port = other._port;
}

SockAddr::SockAddr( unsigned short port )
{
	_port = port;
}

SockAddr::SockAddr( const Address &addr, unsigned short port/*=0*/ )
{
	_addr = addr;
	_port = port;
}

SockAddr::SockAddr( struct sockaddr &sa )
{
	struct sockaddr_in *saddr=(struct sockaddr_in *)&sa;
	_addr = saddr->sin_addr.s_addr;
	_port = ntohs(saddr->sin_port);
}

SockAddr::~SockAddr( void )
{
}

//  Getters
unsigned short SockAddr::port() const {
	return _port;
}

Address SockAddr::address() const {
	return _addr;
}

//	Operators
SockAddr &SockAddr::operator=( const SockAddr &other ) {
	_addr = other._addr;
	_port = other._port;
	return *this;
}

SockAddr &SockAddr::operator=( struct sockaddr_in &saddr ) {
	_addr = saddr.sin_addr.s_addr;
	_port = ntohs(saddr.sin_port);
	return *this;
}

SockAddr &SockAddr::operator=( struct sockaddr &sa ) {
	struct sockaddr_in *saddr=(struct sockaddr_in *)&sa;
	*this = *saddr;
	return *this;
}

bool SockAddr::operator==( const SockAddr &other ) {
	return _addr == other._addr && _port == other._port;
}

bool SockAddr::operator==( const sockaddr_in &other ) {
	return other.sin_port == htons(_port) && other.sin_addr.s_addr == _addr;
}

SockAddr::operator struct sockaddr_in() const {
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = _addr;
	saddr.sin_port = htons(_port);
	return saddr;
}

SockAddr::operator struct sockaddr() const {
	struct sockaddr saddr;
	struct sockaddr_in *saddr_in=(struct sockaddr_in *)&saddr;
	saddr_in->sin_family = AF_INET;
	saddr_in->sin_addr.s_addr = _addr;
	saddr_in->sin_port = htons(_port);
	return saddr;
}

SockAddr::operator std::string() const {
	if (_port) {
		return format( "%s:%d", _addr.asString().c_str(), _port );
	}
	else {
		return _addr.asString();
	}
}

}
}
}

