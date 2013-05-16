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
			throw NetException("Connection::close()", "shutdown()");
	}

	virtual ~Connection()
	{
		close();
	}

	HttpRequest read()
	{
		/*
		std::string result = "";
		char buff[1024];
		int size;

		while((size = read(connFD, buff, sizeof(buff))) > 0)
			result += std::string(buff, size);

		return result;
		*/
	}

	void write(HttpResponse response)
	{
		//::write(connFD, data.c_str(), data.size());
	}
};

}

#endif /* CONNECTION_HPP_ */
