/*
 * Connection.hpp
 *
 *  Created on: May 17, 2013
 *      Author: michal
 */

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

#include <string>
#include <list>
#include <algorithm>
#include <memory>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "SocketIstream.hpp"

namespace Net
{

class Connection
{
	friend class Socket;

private:

	int connFD;

	Connection(int connFD)
	{
		this->connFD = connFD;
	}

public:

	void close()
	{
		int shutdownResult = ::shutdown(connFD, SHUT_RDWR);

		if (shutdownResult == -1)
			throw NetException("Connection::close()", "shutdown() failed");
	}

	virtual ~Connection()
	{
		close();
	}

	HttpRequest read()
	{
		std::list<std::string> rawRequest;
		std::string line;

		SocketIstream socketIstream(connFD);

		for (;;)
		{
			std::getline(socketIstream, line);

			line.erase(line.end() - 1); // pop '\n'

			if (line == "")
				break;

			rawRequest.push_back(line);
		}

		// Request contents

		std::string clHeader = "Content-Length: ";
		auto it = std::find_if(rawRequest.begin(), rawRequest.end(),
				[&](std::string& s) { return s.find(clHeader) != std::string::npos; });

		if(it != rawRequest.end())
		{
			std::string clStr = (*it).substr(clHeader.size());
			std::istringstream iss(clStr);
			int contentLength;
			iss >> contentLength;

			char* buff = new char[contentLength];
			int size = ::read(connFD, buff, contentLength);
			std::string content(buff, size);
		}

		return HttpRequest(rawRequest);
	}

	void write(HttpResponse response)
	{
		//::write(connFD, data.c_str(), data.size());
	}
};

}

#endif /* CONNECTION_HPP_ */
