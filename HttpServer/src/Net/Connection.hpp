/*
 * Connection.hpp
 *
 *  Created on: May 17, 2013
 *      Author: michal
 */

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

#include <sstream>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "../UnixIstreamAdapter.hpp"

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
		int shutdownResult = shutdown(connFD, SHUT_RDWR);

		if (shutdownResult == -1)
		{
			throw NetException("Connection::close()", "shutdown() failed");
		}
	}

	virtual ~Connection()
	{
		close();
	}

	HttpRequest read()
	{
		HttpRequest request;
		std::string line;

		UnixIstreamAdapter socketIstream(connFD);

		std::getline(socketIstream, line); // METHOD
		std::getline(socketIstream, line); // URI

		for (;;)
		{
			std::getline(socketIstream, line);
			line.pop_back(); // pop '\n'

			if (line == "")
				break;

			auto start = line.find(": ");

			std::string name = line.substr(0, start);
			std::string value = line.substr(start + 2);

			request.addHeader(name, value);
		}

		return request;
	}

	void write(HttpResponse response)
	{
		//::write(connFD, data.c_str(), data.size());
	}
};

}

#endif /* CONNECTION_HPP_ */
