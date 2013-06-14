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

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "SocketIstream.hpp"

namespace Net
{

class Socket
{
	friend class ServerSocket;

private:

	int connFD;

	Socket(int connFD)
	{
		this->connFD = connFD;
	}

public:

	void close()
	{
		int shutdownResult = ::shutdown(connFD, SHUT_RDWR);

		if (shutdownResult == -1)
			throw NetException("Socket::close()", "shutdown() failed");
	}

	virtual ~Socket()
	{
		close();
	}

	HttpRequest read()
	{
		// request parameters
		std::list<std::string> rawRequest;
		std::string rawContent = "";
		int contentLength = 0;

		std::string line;
		SocketIstream socketIstream(connFD);

		std::string contentLengthHeader = "Content-Length: ";
		std::string contentLengthLine = "";

		for (;;)
		{
			std::getline(socketIstream, line);

			line.erase(line.end() - 1); // pop '\n'

			if (line == "")
				break;

			if(line.find(contentLengthHeader) != std::string::npos)
				contentLengthLine = line;

			rawRequest.push_back(line);
		}

		// request content
		if(contentLengthLine != "")
		{
			contentLength =
					::atoi(contentLengthLine.substr(contentLengthHeader.size()).c_str());

			rawContent.resize(contentLength);
			::read(connFD, &rawContent[0], contentLength);
		}

		return HttpRequest(rawRequest, rawContent);
	}

	void write(HttpResponse response)
	{
		std::string data = "HTTP/1.1 404 Not Found\r\nServer: Systemy Operacyjne 2013\r\nContent-Length: 0\r\nConnection: close\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
		::write(connFD, data.c_str(), data.size());
	}
};

}

#endif /* SOCKET_HPP_ */
