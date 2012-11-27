#include "sockaddr.h"
#include <boost/static_assert.hpp>
#include <string.h>

#ifdef _WIN32
#	include <winsock2.h>
#	include <Ws2tcpip.h>
#else
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <arpa/inet.h>
#	include <netdb.h>
#endif

#define ASSIGN_SA(sa) { struct sockaddr *tmp = (struct sockaddr *)_sa; *tmp = sa; }

namespace util {
namespace net {

bool SockAddr::isFamilySupported( family::type family ) {
	return family == family::ipv4 || family == family::ipv6;
}

SockAddr::SockAddr( void )
{
	BOOST_STATIC_ASSERT(sizeof(_sa) >= sizeof(struct sockaddr));
	memset(_sa,0,sizeof(_sa));
}

SockAddr::SockAddr( const SockAddr &sa )
{
	BOOST_STATIC_ASSERT(sizeof(_sa) >= sizeof(struct sockaddr));
	memcpy(_sa,sa._sa,sizeof(_sa));
}

SockAddr::SockAddr( struct sockaddr &sa )
{
	BOOST_STATIC_ASSERT(sizeof(_sa) >= sizeof(struct sockaddr));
	ASSIGN_SA(sa);
}

SockAddr::SockAddr( ipv4::SockAddr &sa )
{
	BOOST_STATIC_ASSERT(sizeof(_sa) >= sizeof(struct sockaddr));
	ASSIGN_SA(sa);
}

SockAddr::SockAddr( ipv6::SockAddr &sa )
{
	BOOST_STATIC_ASSERT(sizeof(_sa) >= sizeof(struct sockaddr));
	ASSIGN_SA(sa);
}

SockAddr::~SockAddr( void )
{
}

SockAddr &SockAddr::operator=( const SockAddr &sa ) {
	memcpy(_sa,sa._sa,sizeof(_sa));
	return *this;
}

SockAddr &SockAddr::operator=( struct sockaddr &sa ) {
	ASSIGN_SA(sa);
	return *this;
}

bool SockAddr::operator==( const SockAddr &other ) const {
	return !memcmp(_sa,other._sa,sizeof(_sa));
}

class SockAddrBoolVisitor {
public:
	SockAddrBoolVisitor( const sockaddr &sa ) : _sa(sa) {}

	bool operator()( ipv4::SockAddr &sa4 ) { return sa4 == *(sockaddr_in *)&_sa; }
	bool operator()( ipv6::SockAddr &sa6 ) { return sa6 == *(sockaddr_in6 *)&_sa; }

	const sockaddr &_sa;

private:
	SockAddrBoolVisitor &operator=( const SockAddrBoolVisitor &/*sa*/ ) {
		return *this;
	}

};

bool SockAddr::operator==( const struct sockaddr &sa ) const {
	struct sockaddr *tmp = (struct sockaddr *)_sa;
	if (tmp->sa_family == sa.sa_family) {
		return visit<bool>( SockAddrBoolVisitor(sa) );
	}
	return false;
}

SockAddr::operator struct sockaddr() const {
	struct sockaddr *tmp = (struct sockaddr *)_sa;
	return *tmp;
}

//	Methods
family::type SockAddr::family() const {
	struct sockaddr *tmp = (struct sockaddr *)_sa;
	return (family::type)tmp->sa_family;
}

class SockAddrStringVisitor {
public:
	std::string operator()( ipv4::SockAddr &sa4 ) { return sa4; }
	std::string operator()( ipv6::SockAddr &sa6 ) { return sa6; }
};

std::string SockAddr::asString() const {
	return visit<std::string>( SockAddrStringVisitor() );
}

}
}

