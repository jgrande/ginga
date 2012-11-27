#include "address.h"

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

Address::Address( void )
{
	_ip = INADDR_ANY;
}

Address::Address( const Address &other )
{
	_ip = other._ip;
}

Address::Address( const char *ip )
{
	_ip = ::inet_addr(ip);
}

Address::Address( const std::string &ip )
{
	_ip = ::inet_addr(ip.c_str());
}

Address::~Address( void )
{
}

//	Operators
Address &Address::operator=( const Address &other ) {
	_ip = other._ip;
	return *this;
}

bool Address::operator==( const Address &other ) {
	return _ip == other._ip;
}

Address &Address::operator=( DWORD ip ) {
	_ip = ip;
	return *this;
}

Address::operator DWORD() const {
	return _ip;
}

//	Methods
family::type Address::family() const {
	return family::ipv4;
}

std::string Address::asString() const {
	in_addr addr;
	addr.s_addr = _ip;
	return ::inet_ntoa(addr);
}

bool Address::isMulticast() const {
	return true;
}

bool Address::isUnicast() const {
	return true;
}

bool Address::isAnycast() const {
	return true;
}

}
}
}

