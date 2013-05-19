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

	std::string readRequestLine()
	{
		std::string result = "";

		for(;;)
		{
			char c = get();

			if(c == '\r')
			{
				// consume '\n'
				c = get();
				if(c != '\n')
					throw NetException("Connection::readRequestLine()", "invalid request format");
				else break;
			}
			else result.append(&c, 1);
		}

		return result;
	}

	char get()
	{
		char c;
		::read(connFD, &c, 1);
		return c;
	}

public:

	void close()
	{
		int shutdownResult = shutdown(connFD, SHUT_RDWR);

		if (shutdownResult == -1)
			throw NetException("Connection::close()", "shutdown() failed");
	}

	virtual ~Connection()
	{
		close();
	}

	HttpRequest read()
	{
		HttpRequest request;

		char buff[2048];
		::read(connFD, buff,2048);
		std::cout << std::string(buff, 2048);

		return request;

		std::string line = readRequestLine();

		// set method / URI

		while((line = readRequestLine()) != "")
		{
			auto start = line.find(": ");

			std::string name = line.substr(0, start);
			std::string value = line.substr(start+2);

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
