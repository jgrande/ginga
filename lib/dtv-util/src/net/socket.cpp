#include "socket.h"
#include "../mcr.h"
#include "../log.h"
#include "../registrator.h"
#include <boost/assert.hpp>

#ifdef _WIN32
#	include <winsock2.h>
#	include <Ws2tcpip.h>

#	define SOCKET_REQUESTED_HI     2
#	define SOCKET_REQUESTED_LOW    2
#	define socklen_t               int
#	define SOCK                    (::SOCKET(_hSocket))
#	define LOG_SOCKET_ERR_AUX(err) LERROR( "net", "API socket error: %d", err );
#	define LOG_SOCKET_ERR          LOG_SOCKET_ERR_AUX( ::WSAGetLastError() );
#else
#	include <sys/socket.h>
#	include <sys/ioctl.h>
#	include <netinet/in.h>
#	include <netinet/tcp.h>
#	include <errno.h>
#	include <cassert>

#	define INVALID_SOCKET -1
#	define SOCKET_ERROR   -1
#	define SOCK           (SOCKET(_hSocket))
#	define LOG_SOCKET_ERR LERROR( "net", "API socket error: %d", errno );
#endif
#define LOG_ERR          if (!result) { LOG_SOCKET_ERR; }

namespace util {
namespace net {

static void static_init() {
#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( SOCKET_REQUESTED_HI, SOCKET_REQUESTED_LOW );
	err=::WSAStartup( wVersionRequested, &wsaData );
	if (err) {
		LOG_SOCKET_ERR;
	}
	else {
		/* Confirm that the WinSock DLL supports 2.2.*/
		/* Note that if the DLL supports versions greater    */
		/* than 2.2 in addition to 2.2, it will still return */
		/* 2.2 in wVersion since that is the version we      */
		/* requested.                                        */
		if ( LOBYTE( wsaData.wVersion ) != SOCKET_REQUESTED_LOW ||
			HIBYTE( wsaData.wVersion ) != SOCKET_REQUESTED_HI )
		{
			::WSACleanup( );
			LERROR( "net", "Socket API incompatible." );
		}
	}
#endif
}

static void static_fin() {
#ifdef _WIN32
	::WSACleanup();
#endif
}

REGISTER_INIT( net ) {
	util::net::static_init();
}

REGISTER_FIN( net ) {
	util::net::static_fin();
}

//	Class socket
Socket::Socket()
{
	_hSocket = INVALID_SOCKET;
}

Socket::~Socket()
{
	if (isOpen()) {
		close();
		_hSocket = INVALID_SOCKET;
	}
}

bool Socket::create( enum type::type type/*=stream*/, int protocol/*=0*/ ) {
	bool result=openSocket( type, protocol );
	LOG_ERR;
	return result;
}

bool Socket::shutdown( sd::type how/*=sd::both*/ ) {
	BOOST_ASSERT(isOpen());

	bool result=::shutdown( SOCK, how ) == 0;
	LOG_ERR;
	return result;
}

bool Socket::close() {
	BOOST_ASSERT(isOpen());
#ifdef _WIN32
	bool result=(::closesocket(SOCK) != SOCKET_ERROR);
	LOG_ERR;
	return result;
#else
	return (::close(SOCK) != SOCKET_ERROR);
#endif
}

bool Socket::isOpen() const {
	return _hSocket != INVALID_SOCKET;
}

bool Socket::bind( SockAddr &bindAddress ) {
	BOOST_ASSERT(isOpen());

	struct sockaddr addr=bindAddress;
	bool result=::bind(SOCK, (struct sockaddr *)&addr, sizeof(struct sockaddr)) != SOCKET_ERROR;
	LOG_ERR;
	return result;
}

bool Socket::listen( int maxConn/*=MAX_CONN_QUEUE*/ ) {
	BOOST_ASSERT(isOpen());

	bool result=::listen(SOCK, maxConn) != SOCKET_ERROR;
	LOG_ERR;
	return result;
}

bool Socket::connect( SockAddr &connectAddress ) {
	BOOST_ASSERT(isOpen());

	struct sockaddr addr=connectAddress;
	// should timeout by itself
	bool result=::connect(SOCK, (struct sockaddr *)&addr, sizeof(struct sockaddr)) != SOCKET_ERROR;
	LOG_ERR;
	return result;
}

bool Socket::accept( Socket *sConnect ) {
	BOOST_ASSERT(isOpen());
	BOOST_ASSERT(sConnect && sConnect->_hSocket == INVALID_SOCKET);

	struct sockaddr a;
	socklen_t nLengthAddr = sizeof(struct sockaddr);
	sConnect->_hSocket = (SOCKET) ::accept(SOCK, (struct sockaddr *)&a, &nLengthAddr);
	bool result=sConnect->_hSocket != INVALID_SOCKET;
	LOG_ERR;
	return result;
}

bool Socket::peer( SockAddr &peerAddress ) {
	BOOST_ASSERT(isOpen());

	struct sockaddr addr;
	socklen_t nLengthAddr=sizeof(struct sockaddr);
	bool result=::getpeername(SOCK, (struct sockaddr *)&addr, &nLengthAddr) != SOCKET_ERROR;
	if (result) {
		peerAddress=addr;
	}
	LOG_ERR;
	return result;
}

bool Socket::local( SockAddr &localAddress ) {
	BOOST_ASSERT(isOpen());

	struct sockaddr addr;
	socklen_t nLengthAddr;
	nLengthAddr=sizeof(struct sockaddr);
	bool result=::getsockname(SOCK, (struct sockaddr *)&addr, &nLengthAddr) != SOCKET_ERROR;
	if (result) {
		localAddress=addr;
	}
	LOG_ERR;
	return result;
}

SSIZE_T Socket::send( const void *msg, size_t len ) {
	return ::send( SOCK, (const char *)msg, len, 0 );
}

SSIZE_T Socket::sendto( const void *msg, size_t len, int flags, const SockAddr &to ) {
	struct sockaddr toAddr=to;
	socklen_t toLen=sizeof(struct sockaddr);
	return ::sendto( SOCK, (const char *)msg, len, flags, &toAddr, toLen );
}

SSIZE_T Socket::recv( void *buf, size_t size ) {
	return ::recv( SOCK, (char *)buf, size, 0 );
}

SSIZE_T Socket::recvfrom( void *buf, size_t size ) {
	return ::recvfrom( SOCK, (char *)buf, size, 0, NULL, 0 );
}

SSIZE_T Socket::recvfrom( void *buf, size_t size, SockAddr &from ) {
	struct sockaddr priv;
	socklen_t nLengthAddr=sizeof(struct sockaddr);
	int ret=::recvfrom( SOCK, (char *)buf, size, 0, &priv, &nLengthAddr );
	if (ret > 0) {
		from = priv;
	}
	return ret;
}

SOCKET Socket::fd() const {
	return _hSocket;
}

////	multicast
//bool Socket::addMembership( const SockAddr &addr, DWORD addrIface/*=INADDR_ANY*/ ) {
//#ifdef _WIN32
//	struct ip_mreq_source mreq;
//#else
//	struct ip_mreq mreq;
//#endif
//
//	memset(&mreq, 0, sizeof(mreq));
//	mreq.imr_multiaddr.s_addr=addr;
//    mreq.imr_interface.s_addr=htonl(addrIface);
//	return setOptions( IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq) );
//}
//
//bool Socket::leaveMembership( const SockAddr &addr, DWORD addrIface/*=INADDR_ANY*/ ) {
//#ifdef _WIN32
//	struct ip_mreq_source mreq;
//#else
//	struct ip_mreq mreq;
//#endif
//
//	memset(&mreq, 0, sizeof(mreq));
//	mreq.imr_multiaddr.s_addr=addr;
//    mreq.imr_interface.s_addr=htonl(addrIface);
//	return setOptions( IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq) );
//}

//	options
bool Socket::setRcvBuf( int size ) {
	return setOptions( SOL_SOCKET, SO_RCVBUF, &size, sizeof(int));
}

bool Socket::getRcvBuf( int &size ) {
	size=0;
	return getOptions( SOL_SOCKET, SO_RCVBUF, &size, sizeof(size) );
}

bool Socket::setSndBuf( int size ) {
	return setOptions( SOL_SOCKET, SO_SNDBUF, &size, sizeof(int));
}

bool Socket::getSndBuf( int &size ) {
	return getOptions( SOL_SOCKET, SO_SNDBUF, &size, sizeof(int));
}

bool Socket::setSndTimeout( int timeout ) {
	return setOptions( SOL_SOCKET, SO_SNDBUF, &timeout, sizeof(timeout));
}

bool Socket::getSndTimeout( int &timeout ) {
	return getOptions( SOL_SOCKET, SO_SNDBUF, &timeout, sizeof(timeout));
}

bool Socket::setRcvTimeout( int timeout ) {
	return setOptions( SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
}

bool Socket::getRcvTimeout( int &timeout ) {
	return getOptions( SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
}

bool Socket::setTCPNoDelay( bool noDelay ) {
	int tcpNoDelay=noDelay;
	return setOptions( IPPROTO_TCP, TCP_NODELAY, &tcpNoDelay, sizeof(int));
}

bool Socket::getTCPNoDelay( bool &noDelay ) {
	bool result;
	int tcpNoDelay=noDelay;
	result=setOptions( IPPROTO_TCP, TCP_NODELAY, &tcpNoDelay, sizeof(int));
	noDelay=tcpNoDelay ? true : false;
	return result;
}

bool Socket::setReuseAddr( bool reuse ) {
	int reuseAddr=reuse;
	return setOptions( SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(int));
}

bool Socket::getReuseAddr( bool &reuse ) {	
	int reuseAddr=reuse;
	bool result=setOptions( SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(int));
	reuse = reuseAddr ? true : false;
	return result;
}

bool Socket::setAllowBroadcast( bool allowBroadcast ) {
	int allow=allowBroadcast;
	return setOptions( SOL_SOCKET, SO_BROADCAST, (const char *)&allow, sizeof(int));
}

bool Socket::getAllowBroadcast( bool &allowBroadcast ) {
	int allow=allowBroadcast;
	bool result=setOptions( SOL_SOCKET, SO_BROADCAST, (const char *)&allow, sizeof(int));
	allow = allowBroadcast ? true : false;
	return result;
}

bool Socket::setNonBlocking( bool enable ) {
	BOOST_ASSERT(isOpen());
	
	// If iMode = 0, blocking is enabled; 
	// If iMode != 0, non-blocking mode is enabled.

#ifdef _WIN32
	u_long iMode=enable ? 1 : 0;
	bool result= ::ioctlsocket( SOCK, FIONBIO, &iMode ) != SOCKET_ERROR;
#else
	DWORD iMode=enable ? 1 : 0;
	bool result= ::ioctl( SOCK, FIONBIO, &iMode ) != SOCKET_ERROR;
#endif
	LOG_ERR;
	return result;
}

//	Aux
bool Socket::openSocket( type::type type, int protocol/*=0*/ ) {
#ifdef _WIN32
	_hSocket = (SOCKET)::WSASocket( AF_INET, type, protocol, 0, 0, WSA_FLAG_OVERLAPPED );
#else
	_hSocket = (SOCKET)::socket(AF_INET, type, protocol );
#endif
	return _hSocket != INVALID_SOCKET;
}

bool Socket::setOptions( int level, int opt, const void *optVal, int optLen ) {
	BOOST_ASSERT(isOpen());

	bool result=::setsockopt( SOCK, level, opt, (const char *)optVal, optLen ) != SOCKET_ERROR;
	LOG_ERR;
	return result;
}

bool Socket::getOptions( int level, int opt, void *optVal, int optLen ) {
	BOOST_ASSERT(isOpen());

	socklen_t len=optLen;
	bool result=::getsockopt( SOCK, level, opt, (char *)optVal, &len ) != SOCKET_ERROR && (socklen_t)optLen == len;
	LOG_ERR;
	return result;
}

}
}

