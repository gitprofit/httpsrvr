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
			throw NetException("Socket::Socket()", "socket()");

		memset(&sockAddr, 0, sizeof(sockAddr));
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(port);
		sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

		int bindResult = bind(sockFD, (const sockaddr*) &sockAddr,
				sizeof(sockAddr));

		if (bindResult == -1)
			throw NetException("Socket::Socket()", "bind()");

		// max 10 pending
		int listenResult = listen(sockFD, 10);

		if (listenResult == -1)
			throw NetException("Socket::Socket()", "listen()");
	}

	void close()
	{
		::close(sockFD);
	}

	virtual ~Socket()
	{
		::close(sockFD);
	}

	std::string accept()
	{
		int connFD = ::accept(sockFD, nullptr, nullptr);

		if (connFD < 0)
			throw NetException("Socket::accept()", "accept()");

		char buff[1024];
		int size = read(connFD, buff, sizeof(buff));
		std::string result(buff, size);

		std::string msg = "<html><body><h1>Server works!</h1></body></html>";
		write(connFD, msg.c_str(), msg.size());

		int shutdownResult = shutdown(connFD, SHUT_RDWR);

		if (shutdownResult == -1)
			throw NetException("Socket::accept()", "shutdown()");

		return result;
	}
};

}

#endif /* SOCKET_HPP_ */
