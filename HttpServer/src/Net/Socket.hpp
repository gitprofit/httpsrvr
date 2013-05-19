/*
 * Socket.hpp
 *
 *  Created on: May 16, 2013
 *      Author: michal
 */

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cstring>

#include "NetException.hpp"
#include "Connection.hpp"

namespace Net
{

class Socket
{
private:

	sockaddr_in sockAddr;
	int sockFD;

public:

	Socket(int port)
	{
		sockFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (sockFD == -1)
			throw NetException("Socket::Socket()", "socket() failed");

		memset(&sockAddr, 0, sizeof(sockAddr));
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(port);
		sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

		int bindResult = bind(sockFD, (const sockaddr*) &sockAddr,
				sizeof(sockAddr));

		if (bindResult == -1)
			throw NetException("Socket::Socket()", "bind() failed");

		// max 10 pending
		int listenResult = listen(sockFD, 10);

		if (listenResult == -1)
			throw NetException("Socket::Socket()", "listen() failed");
	}

	void close()
	{
		::close(sockFD);
	}

	virtual ~Socket()
	{
		::close(sockFD);
	}

	Connection accept()
	{
		int connFD = ::accept(sockFD, nullptr, nullptr);

		if (connFD < 0)
			throw NetException("Socket::accept()", "accept() failed");

		return Connection(connFD);
	}
};

}

#endif /* SOCKET_HPP_ */
