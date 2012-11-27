#pragma once

#include "types.h"
#include "sockaddr.h"

namespace util {
namespace net {

#define MAX_CONN_QUEUE	5

class Socket {
public:
	Socket();
	virtual ~Socket();

	bool create( enum type::type type=type::stream, int protocol=0 );
	bool shutdown( sd::type how=sd::both );
	bool close();
	bool isOpen()const;
	bool bind( SockAddr &addr );
	bool listen( int maxConn=MAX_CONN_QUEUE );
	bool connect( SockAddr &addr );
	bool accept( Socket *sock );

	SSIZE_T send( const void *msg, size_t size );
	SSIZE_T sendto( const void *msg, size_t len, int flags, const SockAddr &to );
	SSIZE_T recv( void *buf, size_t size );
	SSIZE_T recvfrom( void *buf, size_t size );
	SSIZE_T recvfrom( void *buf, size_t size, SockAddr &from );

	bool local( SockAddr &addr );
	bool peer( SockAddr &addr );

	SOCKET fd() const;

	//	multicast
	//bool addMembership( const SockAddr &addr, DWORD addrIface=0 );
	//bool leaveMembership( const SockAddr &addr, DWORD addrIface=0 );

	//	options
	bool setRcvBuf( int size );
	bool getRcvBuf( int &size );
	
	bool setSndBuf( int size );
	bool getSndBuf( int &size );

	bool setSndTimeout( int timeout );
	bool getSndTimeout( int &timeout );

	bool setRcvTimeout( int timeout );
	bool getRcvTimeout( int &timeout );

	bool setTCPNoDelay( bool noDelay );
	bool getTCPNoDelay( bool &noDelay );

	bool setReuseAddr( bool reuse );
	bool getReuseAddr( bool &reuse );

	bool setAllowBroadcast( bool allowBroadcast );
	bool getAllowBroadcast( bool &allowBroadcast );

	bool setNonBlocking( bool enable );

protected:
	//	Initialization
	static bool static_startup();
	static void static_cleanup();

	//	Set socket option
	bool openSocket( type::type type, int protocol=0 );
	bool setOptions( int level, int opt, const void *optVal, int optLen );
	bool getOptions( int level, int opt, void *optVal, int optLen );

private:
	friend class SocketEvent;
	SOCKET _hSocket;
};

template<class T>
T *createServer( type::type type, SockAddr &addr ) {
	T *sock = new T();
	if (sock) {
		bool result=sock->create( type );
		if (result) {
			result=sock->bind( addr );
		}

		if (!result) {
			sock->close();
			delete sock;
			sock=NULL;
		}
	}
	return sock;
}

template<class T>
T *createTCPServer( SockAddr &addr, int queue=5 ) {
	T *sock=createServer<T>( type::stream, addr );
	if (sock && !sock->listen( queue )) {
		sock->close();
		delete sock;
		sock=NULL;
	}
	return sock;
}

}	//	net
}	//	util

