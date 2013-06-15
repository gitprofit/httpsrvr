/*
 * HttpRequestFactory.hpp
 *
 *  Created on: Jun 15, 2013
 *      Author: michal
 */

#ifndef HTTPREQUESTFACTORY_HPP_
#define HTTPREQUESTFACTORY_HPP_

#include <cstdlib>

#include "SocketIstream.hpp"
#include "HttpRequest.hpp"

namespace Net
{

class HttpRequestFactory
{

public:

	HttpRequest create(int rawUglySocketFD)
	{
		HttpRequest request;

		std::string line;
		SocketIstream socketStream(rawUglySocketFD);

		std::getline(socketStream, line);
		std::istringstream iss(line);
		iss >> request.headers["Method"];
		iss >> request.headers["URI"];

		while(std::getline(socketStream, line))
		{
			auto start = line.find(": ");
			auto name = line.substr(0, start);
			auto value = line.substr(start + 2);
			request.headers[name] = value;
		}

		try
		{
			auto contentLength = request["Content-Length"]; // throws if not found
			std::string rawContent;

			int size = ::atoi(contentLength.c_str());
			rawContent.resize(size);
			::read(rawUglySocketFD, &rawContent[0], size);
		}
		catch(NetException& ex) { }

		return request;
	}
};

}

#endif /* HTTPREQUESTFACTORY_HPP_ */
