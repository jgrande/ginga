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
namespace ipv6 {

Address::Address( void )
{
}

Address::~Address( void )
{
}

std::string Address::asString() const {
	return "";
}

}
}
}

