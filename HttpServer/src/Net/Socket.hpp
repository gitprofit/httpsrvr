/*
 * Socket.hpp
 *
 *  Created on: May 17, 2013
 *      Author: michal
 */

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <string>
#include <list>
#include <algorithm>
#include <memory>

#include "HttpRequestFactory.hpp"

namespace Net
{

// references
class HttpRequest;
class HttpResponse;


class Socket
{
	friend class ServerSocket;

private:

	int sockFD;

	Socket(int sockFD)
	{
		this->sockFD = sockFD;
	}

public:

	void close()
	{
		int shutdownResult = ::shutdown(sockFD, SHUT_RDWR);

		if (shutdownResult == -1)
			throw NetException("Socket::close()", "shutdown() failed");
	}

	virtual ~Socket()
	{
		close();
	}

	std::shared_ptr<HttpRequest> read(std::shared_ptr<HttpRequestFactory> requestFactory)
	{
		return requestFactory->create(sockFD);
	}

	void write(std::shared_ptr<HttpResponse> response)
	{
		std::string data = "HTTP/1.1 404 Not Found\r\nServer: Systemy Operacyjne 2013\r\nContent-Length: 0\r\nConnection: close\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
		::write(sockFD, data.c_str(), data.size());
	}
};

}

#endif /* SOCKET_HPP_ */
