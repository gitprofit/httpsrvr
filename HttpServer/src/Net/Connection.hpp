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
		int shutdownResult = ::shutdown(connFD, SHUT_RDWR);

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
		std::list<std::string> rawRequest;
		std::string line;

		UnixIstreamAdapter socketIstream(connFD);

		for (;;)
		{
			std::getline(socketIstream, line);

			line.erase(line.end()-1); // pop '\n'

			if (line == "")
				break;

			rawRequest.push_back(line);
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
